#include "DetectorMessenger.hh"

#include "G4UImanager.hh"

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
		fSetShieldMaterial->SetParameterName("New material name", false);
		fSetShieldMaterial->AvailableForStates(G4State_PreInit, G4State_Idle);

		fSetShieldThickness = new G4UIcmdWithADoubleAndUnit("/shield/setThickness", this);
		fSetShieldThickness->SetGuidance("Changes the thickness of the shield");
		fSetShieldThickness->SetParameterName("New thickness", false);
		fSetShieldThickness->SetDefaultUnit("cm");
		fSetShieldThickness->AvailableForStates(G4State_PreInit, G4State_Idle);
	}

	void DetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String newValues) {
		if (cmd == fCreateShield) {
			fDetConstruction->CreateShield(*fShieldThickness, *fMaterialName);
		}
		if (cmd == fRemoveShield) {
			fDetConstruction->RemoveShield();
			// bug: when you change the shield's size or material,
			// then remove it, then try to run beam on, it crashes.
		}
		if (cmd == fSetShieldMaterial) {
			if (fDetConstruction->CreateShield(*fShieldThickness, newValues)) {
				*fMaterialName = newValues;
			}
		}
		if (cmd == fSetShieldThickness) {
			G4double newThickness = fSetShieldThickness->GetNewDoubleValue(newValues);

			if (fDetConstruction->CreateShield(newThickness, *fMaterialName)) {
				*fShieldThickness = newThickness;
			}
		}

		G4UImanager* UI = G4UImanager::GetUIpointer();

		UI->ApplyCommand("/run/beamOn 0");
		UI->ApplyCommand("/vis/viewer/rebuild");
	}
}