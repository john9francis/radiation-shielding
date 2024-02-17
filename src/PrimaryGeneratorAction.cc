#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

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

		fParticleGun->SetParticleEnergy(.511 * MeV);
	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
}