#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4AnalysisManager.hh"
#include "G4RandomDirection.hh"

#include <iostream>
#include <cmath>
#include <random>

namespace rad_shield {
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		// init our member vars
		fRightSkewedDist = new G4bool(false);
		fExponentialDecayDist = new G4bool(false);
		fSigma = new G4double(.5 * MeV);


		// init particle gun
		G4int nParticles = 1;
		fParticleGun = new G4ParticleGun(nParticles);

		// set gun position
		fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -1 * m));

		// set default particle
		G4String particleName = "gamma";
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle
			= particleTable->FindParticle(particleName);

		fParticleGun->SetParticleDefinition(particle);

		// set default energy
		fParticleGun->SetParticleEnergy(1 * MeV);

		
	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

		G4double energy = fParticleGun->GetParticleEnergy();

		// check if the user wants to skew the energy
		if (fRightSkewedDist) {
			energy = generateRightSkewed(energy, *fSigma);
		}
		else if (fExponentialDecayDist) {
			energy = generateExponentialDecay();
		}

		fParticleGun->SetParticleEnergy(energy);


		// make the energy spread out
		G4ThreeVector direction = G4RandomDirection(.99);

		fParticleGun->SetParticleMomentumDirection(direction);


		// make sure to add this particle to analysis
		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->FillH1(1, energy);

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}


	// my own functions to generate different energy distributions


	std::default_random_engine generator;

	G4double PrimaryGeneratorAction::generateRightSkewed(G4double mean, G4double sigma) {
		std::normal_distribution<G4double> normal(mean, sigma);


		// Introduce a scaling factor to control the strength of skewness
		G4double skewness_factor = 0.8;  // Adjust this parameter to control skewness

		// Apply a slightly less right-skewed transformation
		G4double x = normal(generator);

		x = 1.0 / std::pow(x, 2 * skewness_factor);

		if (x > 6 * MeV || x < 0) {
			return .511 * MeV;
		}
		else {
			return x;
		}
	}

	G4double PrimaryGeneratorAction::generateExponentialDecay(G4double paramA, G4double paramB) {
		std::uniform_real_distribution<G4double> uniform(0, 6);
		G4double x = 0;
		while (x < .511 * MeV) {
			x = uniform(generator);

			x = std::exp(paramA + paramB * x);
		}

		return x;
	}
}