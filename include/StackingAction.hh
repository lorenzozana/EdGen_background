
#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

class HistoManager;
class StackingMessenger;
class G4Track;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingAction : public G4UserStackingAction
{
public:

  StackingAction();
  virtual ~StackingAction();
   
  void SetKillStatus(G4bool value)    {killSecondary = value;};
  void SetKill(const G4String& name)  {pname = name;};
     
  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
    
private:

  HistoManager*       histoManager;    
  StackingMessenger*  stackMessenger;

  G4String            pname;
  G4bool              killSecondary;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

