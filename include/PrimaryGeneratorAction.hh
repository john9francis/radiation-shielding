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


		// Getters and setters
		void SetSigma(G4double value) { *fSigma = value; }
		G4double GetSigma() { return *fSigma; }

		void SetRightSkewedFlag() { 
			ResetDistFlags();
			*fRightSkewedDist = true; 
			G4cout << "Particle energy distribution set to right skewed" << G4endl;

		}
		void SetExpDecayFlag() { 
			ResetDistFlags();
			*fExponentialDecayDist = true; 
			G4cout << "Particle energy distribution set to exponential" << G4endl;
		}
		void ResetDistFlags() {
			*fRightSkewedDist = false;
			*fExponentialDecayDist = false;
			G4cout << "Particle distributions reset" << G4endl;
		}

		G4ParticleGun* fParticleGun;
	private:
		G4double generateRightSkewed(G4double mean, G4double sigma=.5*MeV);
		G4double generateExponentialDecay(G4double paramA=0, G4double paramB=-1.12);

		G4double* fSigma;

		G4bool* fRightSkewedDist;
		G4bool* fExponentialDecayDist;
	};
}

#endif // !rad_shield_PRIMARY_GEN_ACTION_HH
