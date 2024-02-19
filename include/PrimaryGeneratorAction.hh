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
	private:
		G4double generateRightSkewed(G4double mean, G4double sigma=.5*MeV);
		G4double generateExponentialDecay(G4double paramA=0, G4double paramB=-1.12);

		G4bool* rightSkewedDist;

		G4bool* exponentialDecayDist;
	};
}

#endif // !rad_shield_PRIMARY_GEN_ACTION_HH
