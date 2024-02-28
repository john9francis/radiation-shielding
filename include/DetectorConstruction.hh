#ifndef rad_shield_DETECTOR_CONSTRUCTION_HH
#define rad_shield_DETECTOR_CONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

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

	private:
		G4LogicalVolume* fLogicWorld = nullptr;
		G4LogicalVolume* fShield = nullptr;

		G4double fMaxShieldThickness = 1.5 * m;
	};
}

#endif // !rad_shield_DETECTOR_CONSTRUCTION_HH
