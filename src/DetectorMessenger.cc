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
			// TODO: basically show it visually and set it to the previous material
			fDetConstruction->UpdateShieldMaterial(*fMaterialName);

			fDetConstruction->CreateShield(*fShieldThickness, *fMaterialName);

			// show the shield to the viewport
			G4UImanager* ui = G4UImanager::GetUIpointer();
			ui->ApplyCommand("/vis/geometry/set/visibility logicShield 0 true");
		}
		if (cmd == fRemoveShield) {
			// make the shield vacuum
			// note: in the future, set it to the world material
			// instead of hardcoding it.
			fDetConstruction->UpdateShieldMaterial("G4_Galactic");

			// hide shield from viewport
			// note: again, ideally, we would get the name of the logicShield
			// instead of hardcoding it, but it's fine for now.
			G4UImanager* ui = G4UImanager::GetUIpointer();
			ui->ApplyCommand("/vis/geometry/set/visibility logicShield 0 false");

		}
		if (cmd == fSetShieldMaterial) {
			if (fDetConstruction->UpdateShieldMaterial(newValues)) {
				*fMaterialName = newValues;
			}
		}
		if (cmd == fSetShieldThickness) {
			G4double newThickness = fSetShieldThickness->GetNewDoubleValue(newValues);

			if (fDetConstruction->UpdateShieldThickness(newThickness)) {
				*fShieldThickness = newThickness;
			}
		}

		G4UImanager* UI = G4UImanager::GetUIpointer();

		UI->ApplyCommand("/run/beamOn 0");
		UI->ApplyCommand("/vis/viewer/rebuild");
	}
}