#ifndef rad_shield_ACTION_INIT_HH
#define rad_shield_ACTION_INIT_HH 1

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"

namespace rad_shield {
	class ActionInit : public G4VUserActionInitialization {
	public:
		ActionInit();
		~ActionInit() = default;

		void Build() const override;
		void BuildForMaster() const override;
		
	};
}

#endif // !rad_shield_ACTION_INIT_HH
