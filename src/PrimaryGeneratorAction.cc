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

	G4double PrimaryGeneratorAction::generateRightSkewed(G4double mean) {
		std::uniform_real_distribution<G4double> uniform(0.0, 1.0);

		// generate random uniform number
		G4double u = uniform(generator);

		// make it right skewed
		G4double x = -log(u) * mean;

		return x;
	}
}