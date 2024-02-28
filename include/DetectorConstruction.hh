#ifndef rad_shield_DETECTOR_CONSTRUCTION_HH
#define rad_shield_DETECTOR_CONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

namespace rad_shield {
	class DetectorConstruction : public G4VUserDetectorConstruction {
	public:
		DetectorConstruction();
		~DetectorConstruction() = default;

		G4VPhysicalVolume* Construct() override;

		// For Detector Messenger
		G4bool CreateShield(G4double thickness, G4String materialName);
		void RemoveShield();
		G4bool ExistsShield();

		G4bool UpdateShieldThickness(G4double newThickness);
		G4bool UpdateShieldMaterial(G4String newMaterialName);

	private:
		G4LogicalVolume* fLogicWorld = nullptr;

		G4Box* fSolidShield = nullptr;
		G4LogicalVolume* fLogicShield = nullptr;
		G4VPhysicalVolume* fPhysShield = nullptr;

		G4double fMaxShieldThickness = 1.5 * m;
	};
}

#endif // !rad_shield_DETECTOR_CONSTRUCTION_HH
