
#include "EventAction.hh"
#include "G4Event.hh"
#include "HistoManager.hh"
#include "EventActionMessenger.hh"

#include "G4UImanager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EventAction::EventAction():
  printModulo(100),
  nSelected(0),
  drawFlag("all"),
  debugStarted(false)
{
  eventMessenger = new EventActionMessenger(this);
  UI = G4UImanager::GetUIpointer();
  selectedEvents.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EventAction::~EventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  // New event
  G4int nEvt = evt->GetEventID();

  if(nSelected>0) {
    for(G4int i=0; i<nSelected; i++) {
      if(nEvt == selectedEvents[i]) {
        UI->ApplyCommand("/random/saveThisEvent");
        UI->ApplyCommand("/tracking/verbose  2");
        debugStarted = true;
        break;
      }
    }
  }

  // Initialize user actions
  HistoManager* man = HistoManager::GetPointer();
  man->BeginOfEvent(); 
  if(man->GetVerbose() > 0 || G4int(nEvt/printModulo)*printModulo == nEvt) 
    G4cout << "EventAction: Event # "
           << nEvt << " started" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EventAction::EndOfEventAction(const G4Event*)
{
  if(debugStarted) {
    UI->ApplyCommand("/tracking/verbose  0");
    debugStarted = false;
  }

  HistoManager* man = HistoManager::GetPointer();
  man->EndOfEvent(); 
  if(man->GetVerbose() > 1) 
    G4cout << "EventAction: Event ended" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
