#include "PGAMessenger.hh"


namespace rad_shield {
	PGAMessenger::PGAMessenger(PrimaryGeneratorAction* PGA) {
		fPGA = PGA;

		fDirectory = new G4UIdirectory("/pga/");
		fDirectory->SetGuidance("Commands to give the primary particles' energies some distribution instead of just one value");

		fSetRightSkewCmd = new G4UIcmdWithADoubleAndUnit("/pga/setRightSkew", this);
		fSetRightSkewCmd->SetGuidance("Creates a right skewed distribution, with you specifying the mean.");
		fSetRightSkewCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

		fResetCmd = new G4UIcmdWithoutParameter("/pga/reset", this);
		fResetCmd->SetGuidance("Resets all energy modifications distributions");
		fResetCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	}

	PGAMessenger::~PGAMessenger() {
		// note: PGA get's deleted elsewhere

		delete fDirectory;
		delete fSetRightSkewCmd;
		delete fResetCmd;
	}

	void PGAMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
		if (command == fSetRightSkewCmd) {
			G4cout << "Setting right skew with mean of: " << newValue << G4endl;
		}
		if (command == fResetCmd) {
			G4cout << "Resetting..." << G4endl;
		}
	}
}