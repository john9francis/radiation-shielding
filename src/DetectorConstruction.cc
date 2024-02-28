#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"


namespace rad_shield {
	DetectorConstruction::DetectorConstruction() {}

	void DetectorConstruction::RemoveShield() {
		if (fPhysShield != nullptr) {
			delete fPhysShield;
			fPhysShield = nullptr;
		}
	}

	G4bool DetectorConstruction::ExistsShield() {
		if (fPhysShield == nullptr) {
			return false;
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Trying a new approach where I simply update the material or the thickness //
	///////////////////////////////////////////////////////////////////////////////

	G4bool DetectorConstruction::UpdateShieldMaterial(G4String newMaterialName) {

		// first make sure the material exists
		auto nist = G4NistManager::Instance();
		auto newMaterial = nist->FindOrBuildMaterial(newMaterialName);
		if (newMaterial == nullptr) {
			return false;
		}

		fLogicShield->SetMaterial(newMaterial);

		return true;
	}

	G4bool DetectorConstruction::UpdateShieldThickness(G4double newThickness) {

		// first make sure it's not too thick
		if (newThickness > fMaxShieldThickness) {
			return false;
		}

		fSolidShield->SetZHalfLength(newThickness / 2);


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

		// if we pass the test, create the shield and add to world.

		// remove old shield
		RemoveShield();

		// create the new one

		G4ThreeVector shieldPos = G4ThreeVector();

		G4Material* shieldMat = nist->FindOrBuildMaterial(materialName);

		fSolidShield = new G4Box(
			"solidShield",
			1 * m,
			1 * m,
			thickness / 2
		);

		fLogicShield = new G4LogicalVolume(
			fSolidShield,
			shieldMat,
			"logicShield"
		);

		fPhysShield = new G4PVPlacement(
			nullptr,
			shieldPos,
			fLogicShield,
			"physShield",
			fLogicWorld,
			false,
			0
		);

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


		G4ThreeVector shieldPos = G4ThreeVector();

		G4Material* shieldMat = nist->FindOrBuildMaterial("G4_W");

		fSolidShield = new G4Box(
			"solidShield",
			1 * m,
			1 * m,
			5 * cm / 2
		);

		fLogicShield = new G4LogicalVolume(
			fSolidShield,
			shieldMat,
			"logicShield"
		);

		fPhysShield = new G4PVPlacement(
			nullptr,
			shieldPos,
			fLogicShield,
			"physShield",
			fLogicWorld,
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