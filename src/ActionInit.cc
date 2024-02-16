#include "ActionInit.hh"

#include "PrimaryGeneratorAction.hh"

namespace rad_shield {
	void ActionInit::Build() const {
		SetUserAction(new PrimaryGeneratorAction());
	}
}