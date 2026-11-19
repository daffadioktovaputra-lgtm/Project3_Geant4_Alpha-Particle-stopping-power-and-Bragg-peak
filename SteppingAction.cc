#include "SteppingAction.hh"

#include "EventAction.hh"

#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
    : fEventAction(eventAction)
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep <= 0.0)
    {
        return;
    }

    auto* preStepPoint = step->GetPreStepPoint();

    auto* volume =
        preStepPoint->GetTouchableHandle()
            ->GetVolume();

    if (volume == nullptr)
    {
        return;
    }

    G4String volumeName = volume->GetName();

    if (volumeName != "Slice")
    {
        return;
    }

    G4int sliceID =
        preStepPoint->GetTouchableHandle()
            ->GetCopyNumber();

    fEventAction->AddEdep(sliceID, edep);
}
