#ifndef rad_shield_RUN_ACTION_HH
#define rad_shield_RUN_ACTION_HH 1

#include "G4UserRunAction.hh"

namespace rad_shield {
	class RunAction : public G4UserRunAction {
	public:
		RunAction();
		~RunAction()=default;

		void BeginOfRunAction(const G4Run* aRun) override;
		void EndOfRunAction(const G4Run* aRun) override;

	};
}


#endif // !rad_shield_RUN_ACTION_HH
