
#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger
{
public:

  DetectorMessenger(DetectorConstruction* );
  virtual ~DetectorMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:

  DetectorConstruction* Detector;

  G4UIdirectory*             testDir;
  G4UIcmdWithAString*        matCmd;
  G4UIcmdWithAString*        mat1Cmd;
  G4UIcmdWithAString*        mat2Cmd;
  G4UIcmdWithAString*        gdmlfileCmd;
  G4UIcmdWithADoubleAndUnit* rCmd;
  G4UIcmdWithADoubleAndUnit* lCmd;
  G4UIcmdWithADoubleAndUnit* rCmd2;
  G4UIcmdWithADoubleAndUnit* lCmd2;
  G4UIcmdWithADoubleAndUnit* bsizeCmd;
  G4UIcmdWithAnInteger*      btypeCmd;
  G4UIcmdWithADoubleAndUnit* edepCmd;
  G4UIcmdWithAnInteger*      binCmd;
  G4UIcmdWithAnInteger*      nOfAbsCmd;
  G4UIcmdWithAnInteger*      verbCmd;
  G4UIcmdWithABool*          beamCmd;
  G4UIcmdWithoutParameter*   updateCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

