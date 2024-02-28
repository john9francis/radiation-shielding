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

		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

		// make sure to add this particle to analysis
		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->FillH1(1, energy);

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}

}