#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4AnalysisManager.hh"

#include <iostream>
#include <cmath>
#include <random>

namespace rad_shield {
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		G4int nParticles = 1;
		fParticleGun = new G4ParticleGun(nParticles);

		// set gun position and direction
		fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -1 * m));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

		// set default particle and energy
		G4String particleName = "gamma";
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle
			= particleTable->FindParticle(particleName);

		fParticleGun->SetParticleDefinition(particle);

		
	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
		// generate energy from a right skewed distribution
		G4double meanEnergy = .511 * MeV;
		G4double skewedEnergy = generateRightSkewed(meanEnergy);

		fParticleGun->SetParticleEnergy(skewedEnergy);

		// make sure to add this particle to analysis
		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->FillH1(1, skewedEnergy);

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}


	// my own function to generate a right skewed distribution


	std::default_random_engine generator;

	G4double PrimaryGeneratorAction::generateRightSkewed(G4double mean, G4double sigma) {
		std::normal_distribution<G4double> normal(mean, sigma);

		G4double x = normal(generator);

		// Introduce a scaling factor to control the strength of skewness
		G4double skewness_factor = 0.8;  // Adjust this parameter to control skewness

		// Apply a slightly less right-skewed transformation
		x = 1.0 / std::pow(x, 2 * skewness_factor);

		// Ensure the value is within the desired range [0, 6]
		x = std::max(0.0, std::min(6.0, x));

		return x;
	}
}