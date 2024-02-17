#include "ActionInit.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

namespace rad_shield {
	void ActionInit::Build() const {
		SetUserAction(new PrimaryGeneratorAction());

		SetUserAction(new RunAction());

		SetUserAction(new SteppingAction());
	}

	void ActionInit::BuildForMaster() const {
		SetUserAction(new RunAction());
	}
}