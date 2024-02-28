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

	void DetectorConstruction::RemoveShield() {
		if (fShield) {
			delete fShield;
		}
	}

	G4bool DetectorConstruction::ExistsShield() {
		if (fShield == nullptr) {
			return false;
		}
		return true;
	}

	G4bool DetectorConstruction::CreateShield(G4double thickness, G4String materialName) {
		// Returns true if the shield was created sucessfully

		// Make sure the desired thickness isn't over the max thickness
		if (thickness > fMaxShieldThickness) {
			G4cout
				<< "Attempted to create a shield "
				<< "that is too thick with a value of: "
				<< thickness
				<< G4endl;

			return false;
		}

		// Also make sure the material is in the nist database
		G4NistManager* nist = G4NistManager::Instance();

		auto shieldMaterial = nist->FindMaterial(materialName);

		if (shieldMaterial == nullptr) {
			G4cout
				<< "Attempted to create a shield "
				<< "With a material not found in the "
				<< "NIST material database. Attempted material: "
				<< materialName
				<< G4endl;

			return false;
		}

		// make sure world has been initialized
		if (fLogicWorld == nullptr) {
			G4cout
				<< "Attempted to create a shield "
				<< "before world object has been initialized. "
				<< "please wait till the detector construction "
				<< "has been initialized. "
				<< G4endl;
			return false;
		}

		// if we pass the test, create the shield and add to world

		G4ThreeVector shieldPos = G4ThreeVector();

		return true;
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

		fLogicWorld = new G4LogicalVolume(
			solidWorld,
			vacuum,
			"logicWorld"
		);

		G4VPhysicalVolume* physWorld = new G4PVPlacement(
			nullptr,
			G4ThreeVector(),
			fLogicWorld,
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
			fLogicWorld,
			false,
			0
		);



		return physWorld;
	}
}