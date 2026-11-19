#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = nullptr;

    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    auto* runManager = new G4RunManager;

    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new ActionInitialization);

    runManager->Initialize();

    auto* visManager = new G4VisExecutive;
    visManager->Initialize();

    auto* UImanager = G4UImanager::GetUIpointer();

    if (ui)
    {
	UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    delete visManager;
    delete runManager;

    return 0;
}
