#ifndef rad_shield_PRIMARY_GEN_ACTION_HH
#define rad_shield_PRIMARY_GEN_ACTION_HH 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"

namespace rad_shield {
	class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
	public:
		PrimaryGeneratorAction();
		~PrimaryGeneratorAction();

		void GeneratePrimaries(G4Event*) override;

		G4ParticleGun* fParticleGun;

	};
}

#endif // !rad_shield_PRIMARY_GEN_ACTION_HH
