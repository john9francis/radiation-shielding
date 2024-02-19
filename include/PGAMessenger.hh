#ifndef rad_shield_PGA_MESSENGER_HH
#define rad_shield_PGA_MESSENGER_HH 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "PrimaryGeneratorAction.hh"

namespace rad_shield {
	class PGAMessenger : public G4UImessenger {
	public:
		PGAMessenger(PrimaryGeneratorAction* PGA);
		~PGAMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues) override;


	private:
		PrimaryGeneratorAction* fPGA;

		G4UIdirectory* fDirectory;

		G4UIcmdWithADoubleAndUnit* fSetRightSkewCmd;
		G4UIcmdWithoutParameter* fResetCmd;


	};
}

#endif // !rad_shield_PGA_MESSENGER_HH 1
