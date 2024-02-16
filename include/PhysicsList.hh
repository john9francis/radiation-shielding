#ifndef rad_shield_PHYSICS_LIST_HH
#define rad_shield_PHYSICS_LIST_HH 1

#include "G4VModularPhysicsList.hh"

#include "G4EmStandardPhysics.hh"	


namespace rad_shield {
	class PhysicsList : public G4VModularPhysicsList {
	public:
		PhysicsList() : G4VModularPhysicsList() {
			RegisterPhysics(new G4EmStandardPhysics());
		}
		~PhysicsList() = default;
	};
}

#endif