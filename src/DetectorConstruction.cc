#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"


namespace rad_shield {
	DetectorConstruction::DetectorConstruction() {}


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
			fPhantomSize.getX() / 2,
			fPhantomSize.getY() / 2,
			fPhantomSize.getZ() / 2
		);


		G4LogicalVolume* logicPhantom = new G4LogicalVolume(
			solidPhantom,
			water,
			"logicPhantom"
		);

		new G4PVPlacement(
			nullptr,
			fPhantomPos,
			logicPhantom,
			"physPhantom",
			fLogicWorld,
			false,
			0
		);



		return physWorld;
	}
}