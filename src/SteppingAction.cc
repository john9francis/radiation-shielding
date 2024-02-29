#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "DetectorConstruction.hh"

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
			// Note: first, we have to find the detector construction and get 
			// the phantom pos
			auto runManager = G4RunManager::GetRunManager();
			const DetectorConstruction* detConst = static_cast<const DetectorConstruction*>(runManager->GetUserDetectorConstruction());
			const G4double phantomEdgePos = detConst->GetPhantomEdgeZ();

			analysisManager->FillH1(fPDDH1ID, pos.getZ() - phantomEdgePos, energy);


		}
	}
}