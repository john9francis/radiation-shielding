#ifndef rad_shield_STEPPING_ACTION_HH
#define rad_shield_STEPPING_ACTION_HH 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

namespace rad_shield {
	class SteppingAction : public G4UserSteppingAction {
	public:
		SteppingAction() = default;
		~SteppingAction() = default;

		void UserSteppingAction(const G4Step*) override;

	private:
		// Graph ID's
		G4double fPDDH1ID = 0;


	};
}

#endif // !rad_shield_STEPPING_ACTION_HH
