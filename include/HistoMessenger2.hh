
#ifndef HistoMessenger2_h
#define HistoMessenger2_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class HistoManager;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoMessenger2: public G4UImessenger
{
public:

  HistoMessenger2(HistoManager*);
  virtual ~HistoMessenger2();

  void SetNewValue(G4UIcommand* ,G4String );

private:

  HistoManager* Hmanager;

  G4UIdirectory*             testDir;
  G4UIcmdWithAString*     particleCmd;
  G4UIcmdWithAString*     fileCmd;
  G4UIcmdWithAString*     infileCmd;
  G4UIcmdWithAString*     inchainCmd;
 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
