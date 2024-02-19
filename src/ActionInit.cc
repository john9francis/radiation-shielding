#include "ActionInit.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

namespace rad_shield {
	ActionInit::ActionInit(PrimaryGeneratorAction* pga) {
		fPGA = pga;
	}


	void ActionInit::Build() const {
		SetUserAction(fPGA);

		SetUserAction(new RunAction());

		SetUserAction(new SteppingAction());
	}

	void ActionInit::BuildForMaster() const {
		SetUserAction(new RunAction());
	}
}