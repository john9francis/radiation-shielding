// radiation-shielding.cc : Defines the entry point for the application.

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4RunManagerFactory.hh"
#include "G4VisExecutive.hh"

#include "PhysicsList.hh"
#include "ActionInit.hh"
#include "DetectorConstruction.hh"

using namespace rad_shield;

int main(int argc, char** argv)
{
	// Start (or don't) a UI
	G4UIExecutive* ui = nullptr;
	if (argc == 1) {
		ui = new G4UIExecutive(argc, argv);
	}

	// ==============================================================
	// Register our required classes
	// ==============================================================
	
	// create default runmanager
	auto runManager =
		G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new ActionInit());

	// init vis manager
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// get pointer to UI manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Run macro or start UI
	if (!ui) {
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	else {
		// run visualization script
		UImanager->ApplyCommand("/control/execute _vis.mac");
		// use UI
		ui->SessionStart();
		delete ui;
	}

	return 0;
}
