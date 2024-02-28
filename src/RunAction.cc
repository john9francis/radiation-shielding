#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

namespace rad_shield {
	RunAction::RunAction() {
		// setup our output graphs

		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->SetDefaultFileType("root");
		analysisManager->SetVerboseLevel(0);
		analysisManager->SetFileName("EnergyGraph");

		// output PDD graph for the phantom
		analysisManager->CreateH1("PDD", "PDD Graph", 100, 0, 30 * cm);
		analysisManager->SetH1XAxisTitle(0, "Depth (cm)");
		analysisManager->SetH1YAxisTitle(0, "Energy deposited (MeV)");

		// graph of the original energies
		analysisManager->CreateH1("OriginalEnergies", "Original Particle Energies", 100, 0, 6 * MeV);
		analysisManager->SetH1XAxisTitle(1, "Energy (MeV)");
		analysisManager->SetH1YAxisTitle(1, "Number of Particles");

	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->OpenFile();
	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {
		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->Write();
		analysisManager->CloseFile();
	}
}