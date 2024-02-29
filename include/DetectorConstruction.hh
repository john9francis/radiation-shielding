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
		G4bool UpdateShieldThickness(G4double newThickness);
		G4bool UpdateShieldMaterial(G4String newMaterialName);

		// For PDD Graph
		G4double GetPhantomEdgeZ() const { return fPhantomPos.getZ() - fPhantomSize.getZ() / 2; };

	private:
		G4LogicalVolume* fLogicWorld = nullptr;

		G4Box* fSolidShield = nullptr;
		G4LogicalVolume* fLogicShield = nullptr;
		G4VPhysicalVolume* fPhysShield = nullptr;

		G4double fMaxShieldThickness = 1.5 * m;

		G4ThreeVector fPhantomSize = G4ThreeVector(30 * cm, 30 * cm, 30 * cm);
		G4ThreeVector fPhantomPos = G4ThreeVector(0, 0, 1 * m);
	};
}

#endif // !rad_shield_DETECTOR_CONSTRUCTION_HH
