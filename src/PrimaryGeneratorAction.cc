#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"

namespace rad_shield {
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		G4int nParticles = 1;
		fParticleGun = new G4ParticleGun(nParticles);
	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

		// set gun position and direction
		fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -1 * m));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
}