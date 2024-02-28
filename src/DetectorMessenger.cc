#include "DetectorMessenger.hh"

namespace rad_shield {

	DetectorMessenger::DetectorMessenger(DetectorConstruction* detCons)
		: G4UImessenger(), fDetConstruction(detCons) {

		// create the directory for the commands
		fDirectory = new G4UIdirectory("/shield/");
		fDirectory->SetGuidance("Commands to create or adjust a radiation shield.");

		// Create commands
		fCreateShield = new G4UIcmdWithoutParameter("/shield/create", this);
		fCreateShield->SetGuidance("Adds the shield to the world");
		fCreateShield->AvailableForStates(G4State_PreInit, G4State_Idle);

		fRemoveShield = new G4UIcmdWithoutParameter("/shield/remove", this);
		fRemoveShield->SetGuidance("Removes the shield from the world");
		fRemoveShield->AvailableForStates(G4State_PreInit, G4State_Idle);

		fSetShieldMaterial = new G4UIcmdWithAString("/shield/setMaterial", this);
		fSetShieldMaterial->SetGuidance("Sets the material of the shield");
		fSetShieldMaterial->AvailableForStates(G4State_PreInit, G4State_Idle);

		fSetShieldThickness = new G4UIcmdWithADoubleAndUnit("/shield/setThickness", this);
		fSetShieldThickness->SetGuidance("Changes the thickness of the shield");
		fSetShieldThickness->AvailableForStates(G4State_PreInit, G4State_Idle);
	}

	void DetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String newValues) {
		if (cmd == fCreateShield) {
			
		}
	}
}