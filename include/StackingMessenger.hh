
#ifndef StackingMessenger_h
#define StackingMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class StackingAction;
class G4UIcmdWithABool;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingMessenger: public G4UImessenger
{
public:

  StackingMessenger(StackingAction*);
  virtual ~StackingMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
    
  StackingAction*     stackAction;
    
  G4UIcmdWithABool*   killCmd;
  G4UIcmdWithAString* kCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
