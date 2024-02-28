#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"


namespace rad_shield {
	DetectorConstruction::DetectorConstruction() {
		// nothing yet...
	}

	void DetectorConstruction::CreateShield(G4double thickness, G4String materialName) {
		// create an object and add it to the world
		G4ThreeVector shieldPos = G4ThreeVector();
		G4double maxThickness = 1.5 * m;
	}

	G4VPhysicalVolume* DetectorConstruction::Construct() {

		G4NistManager* nist = G4NistManager::Instance();

		// construct the world
		G4double worldWidth = 2.5 * m;
		G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

		G4Box* solidWorld = new G4Box(
			"solidWorld",
			worldWidth / 2,
			worldWidth / 2,
			worldWidth / 2
		);

		G4LogicalVolume* logicWorld = new G4LogicalVolume(
			solidWorld,
			vacuum,
			"logicWorld"
		);

		G4VPhysicalVolume* physWorld = new G4PVPlacement(
			nullptr,
			G4ThreeVector(),
			logicWorld,
			"physWorld",
			nullptr,
			false,
			0
		);


		// phantom
		G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

		G4Box* solidPhantom = new G4Box(
			"solidPhantom",
			15 * cm,
			15 * cm,
			15 * cm
		);

		G4ThreeVector phantomPos = G4ThreeVector(0, 0, 1 * m);

		G4LogicalVolume* logicPhantom = new G4LogicalVolume(
			solidPhantom,
			water,
			"logicPhantom"
		);

		new G4PVPlacement(
			nullptr,
			phantomPos,
			logicPhantom,
			"physPhantom",
			logicWorld,
			false,
			0
		);



		return physWorld;
	}
}