#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class EventAction : public G4UserEventAction
{
public:

    EventAction();
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void AddEdep(G4int sliceID, G4double edep);

    const G4double* GetEdep() const;

private:

    G4double fEdep[100];
};

#endif
