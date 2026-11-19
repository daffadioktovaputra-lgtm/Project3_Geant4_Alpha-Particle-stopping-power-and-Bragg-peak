#include "EventAction.hh"

#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction()
{
    for (G4int i = 0; i < 100; i++)
    {
        fEdep[i] = 0.0;
    }
}

void EventAction::BeginOfEventAction(const G4Event*)
{
    for (G4int i = 0; i < 100; i++)
    {
        fEdep[i] = 0.0;
    }
}

void EventAction::AddEdep(G4int sliceID, G4double edep)
{
    if (sliceID >= 0 && sliceID < 100)
    {
        fEdep[sliceID] += edep;
    }
}

const G4double* EventAction::GetEdep() const
{
    return fEdep;
}

void EventAction::EndOfEventAction(const G4Event*)
{
    auto* runAction =
        const_cast<RunAction*>(
            static_cast<const RunAction*>(
                G4RunManager::GetRunManager()
                    ->GetUserRunAction()
            )
        );

    for (G4int i = 0; i < 100; i++)
    {
        runAction->AddEdep(i, fEdep[i]);
    }
}
