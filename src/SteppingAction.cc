#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

namespace rad_shield {
	void SteppingAction::UserSteppingAction(const G4Step* aStep) {
		// Get our current volume.
		// The particle's current volume will dictate which graph we add data to.
		//
		auto currentPhysVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

		
		// if our particle is in the phantom, add to the PDD and HeatMap graphs
		if (currentPhysVolume->GetName() == "physPhantom") {

			G4ThreeVector pos =aStep->GetPreStepPoint()->GetPosition();
			G4double energy =aStep->GetTotalEnergyDeposit();

			auto analysisManager = G4AnalysisManager::Instance();

			// add to the PDD graph
			// the + 15 * cm converts position to depth.
			analysisManager->FillH1(fPDDH1ID, pos.getZ() + 15 * cm, energy);


		}
	}
}