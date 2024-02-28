#ifndef rad_shield_DETECTOR_MESSENGER
#define rad_shield_DETECTOR_MESSENGER 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"

namespace rad_shield {
	class DetectorMessenger : public G4UImessenger {
	public:
		DetectorMessenger(DetectorConstruction* detConstruction);
		~DetectorMessenger() = default;

		void SetNewValue(G4UIcommand* command, G4String newValues) override;

	private:
		// big classes
		DetectorConstruction* fDetConstruction;
		G4UIdirectory* fDirectory;

		// smaller things to keep track of
		G4double* shieldThickness = new G4double(5 * cm);
		G4String* materialName = new G4String("G4_W");

		// commands
		G4UIcmdWithoutParameter* fCreateShield;
		G4UIcmdWithoutParameter* fRemoveShield;

		G4UIcmdWithAString* fSetShieldMaterial;
		G4UIcmdWithADoubleAndUnit* fSetShieldThickness;
	};
}

#endif // !rad_shield_DETECTOR_MESSENGER
