#ifndef rad_shield_DETECTOR_CONSTRUCTION_HH
#define rad_shield_DETECTOR_CONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh"

namespace rad_shield {
	class DetectorConstruction : public G4VUserDetectorConstruction {
	public:
		DetectorConstruction();
		~DetectorConstruction() = default;

		G4VPhysicalVolume* Construct() override;
	};
}

#endif // !rad_shield_DETECTOR_CONSTRUCTION_HH
