
#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PhysicsList;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsListMessenger: public G4UImessenger
{
public:
  
  PhysicsListMessenger(PhysicsList* p = 0);
  virtual ~PhysicsListMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  
  PhysicsList* pPhysicsList;
    
  G4UIcmdWithADoubleAndUnit* gammaCutCmd;
  G4UIcmdWithADoubleAndUnit* electCutCmd;
  G4UIcmdWithADoubleAndUnit* posCutCmd;
  G4UIcmdWithADoubleAndUnit* pCutCmd;
  G4UIcmdWithADoubleAndUnit* allCutCmd;
  G4UIcmdWithAString*        pListCmd;
  G4UIcmdWithoutParameter*   listCmd;  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

