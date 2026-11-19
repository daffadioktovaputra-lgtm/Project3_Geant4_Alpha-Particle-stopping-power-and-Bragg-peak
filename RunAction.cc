#include "RunAction.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include <fstream>

RunAction::RunAction()
{
    for (G4int i = 0; i < 100; i++)
    {
        fEdep[i] = 0.0;
    }
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    for (G4int i = 0; i < 100; i++)
    {
        fEdep[i] = 0.0;
    }
}

void RunAction::AddEdep(G4int sliceID, G4double edep)
{
    if (sliceID >= 0 && sliceID < 100)
    {
        fEdep[sliceID] += edep;
    }
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4int numberOfEvents = run->GetNumberOfEvent();

    if (numberOfEvents == 0)
    {
        return;
    }

    std::ofstream output("alpha_profile.csv");

    output << "slice,depth_mm,edep_MeV,dEdx_MeV_per_mm\n";

    G4int lastSliceWithEnergy = -1;

    for (G4int i = 0; i < 100; i++)
    {
        G4double depth =
            (i + 0.5) * 1.0;

        G4double edepMeV =
	fEdep[i] / MeV / numberOfEvents;

        G4double dEdx =
            edepMeV / 1.0;

        output
            << i << ","
            << depth << ","
            << edepMeV << ","
            << dEdx << "\n";

        if (edepMeV > 0.0)
        {
            lastSliceWithEnergy = i;
        }
    }

    output.close();

    G4double stoppingRange =
        (lastSliceWithEnergy + 1.0) * mm;

    G4cout << G4endl;
    G4cout << "============================================"
           << G4endl;

    G4cout << "Project 3 - Alpha Particle"
           << G4endl;

    G4cout << "Number of events = "
           << numberOfEvents
           << G4endl;

    G4cout << "Energy = 5 MeV"
           << G4endl;

    G4cout << "Scoring slices = 100"
           << G4endl;

    G4cout << "Slice thickness = 1 mm"
           << G4endl;

    G4cout << "Stopping range = "
           << stoppingRange / mm
           << " mm"
           << G4endl;

    G4cout << "Output file = alpha_profile.csv"
           << G4endl;

    G4cout << "============================================"
           << G4endl;
}
