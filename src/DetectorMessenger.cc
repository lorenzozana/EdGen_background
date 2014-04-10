
#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:Detector(Det)
{
  testDir = new G4UIdirectory("/testhadr/");
  testDir->SetGuidance(" Hadronic Extended Example.");

  matCmd = new G4UIcmdWithAString("/testhadr/TargetMat",this);
  matCmd->SetGuidance("Select Material for the target");
  matCmd->SetParameterName("tMaterial",false);
  matCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  mat1Cmd = new G4UIcmdWithAString("/testhadr/WorldMat",this);
  mat1Cmd->SetGuidance("Select Material for world");
  mat1Cmd->SetParameterName("wMaterial",false);
  mat1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  mat2Cmd = new G4UIcmdWithAString("/testhadr/WindowMat",this);
  mat2Cmd->SetGuidance("Select Material for the window");
  mat2Cmd->SetParameterName("windMaterial",false);
  mat2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/TargetRadius",this);
  rCmd->SetGuidance("Set radius of the target");
  rCmd->SetParameterName("radius",false);
  rCmd->SetUnitCategory("Length");
  rCmd->SetRange("radius>0");
  rCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/TargetLength",this);
  lCmd->SetGuidance("Set length of the target");
  lCmd->SetParameterName("length",false);
  lCmd->SetUnitCategory("Length");
  lCmd->SetRange("length>0");
  lCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rCmd2 = new G4UIcmdWithADoubleAndUnit("/testhadr/WindowThick_r",this);
  rCmd2->SetGuidance("Set thickness in radius of the window");
  rCmd2->SetParameterName("wradius",false);
  rCmd2->SetUnitCategory("Length");
  rCmd2->SetRange("wradius>0");
  rCmd2->AvailableForStates(G4State_PreInit,G4State_Idle);

  lCmd2 = new G4UIcmdWithADoubleAndUnit("/testhadr/WindowThick_z",this);
  lCmd2->SetGuidance("Set thickness in z of the window (1 side)");
  lCmd2->SetParameterName("wthick",false);
  lCmd2->SetUnitCategory("Length");
  lCmd2->SetRange("wthick>0");
  lCmd2->AvailableForStates(G4State_PreInit,G4State_Idle);

  binCmd = new G4UIcmdWithAnInteger("/testhadr/NumberOfBinsE",this);
  binCmd->SetGuidance("Set number of bins for Energy");
  binCmd->SetParameterName("NEbins",false);
  binCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  nOfAbsCmd = new G4UIcmdWithAnInteger("/testhadr/NumberDivZ",this);
  nOfAbsCmd->SetGuidance("Set number of slices");
  nOfAbsCmd->SetParameterName("NZ",false);
  nOfAbsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  edepCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/MaxEdep",this);
  edepCmd->SetGuidance("Set max energy in histogram");
  edepCmd->SetParameterName("edep",false);
  edepCmd->SetUnitCategory("Energy");
  edepCmd->SetRange("edep>0");
  edepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  updateCmd = new G4UIcmdWithoutParameter("/testhadr/Update",this);
  updateCmd->SetGuidance("Update geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s)");
  updateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  beamCmd = new G4UIcmdWithABool("/testhadr/DefaultBeamPosition",this);
  beamCmd->SetGuidance("show inelastic and elastic cross sections");

  verbCmd = new G4UIcmdWithAnInteger("/testhadr/Verbose",this);
  verbCmd->SetGuidance("Set verbose for ");
  verbCmd->SetParameterName("verb",false);
  verbCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete matCmd;
  delete mat1Cmd;
  delete mat2Cmd;
  delete rCmd;
  delete lCmd;
  delete rCmd2;
  delete lCmd2;
  delete nOfAbsCmd;
  delete updateCmd;
  delete testDir;
  delete beamCmd;
  delete verbCmd;
  delete edepCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  HistoManager* h = HistoManager::GetPointer();
  if( command == matCmd )
    Detector->SetTargetMaterial(newValue);
  else if( command == mat1Cmd )
    Detector->SetWorldMaterial(newValue);
  else if( command == mat2Cmd )
    Detector->SetWindowMaterial(newValue);
  else if( command == rCmd ) 
    Detector->SetTargetRadius(rCmd->GetNewDoubleValue(newValue));
  else if( command == lCmd ) 
    h->SetTargetLength(lCmd->GetNewDoubleValue(newValue));
  else if( command == rCmd2 ) 
    h->SetWindowThick_r(rCmd2->GetNewDoubleValue(newValue));
  else if( command == lCmd2 ) 
    h->SetWindowThick_z(lCmd2->GetNewDoubleValue(newValue));
  else if( command == nOfAbsCmd ) 
    h->SetNumberOfSlices(nOfAbsCmd->GetNewIntValue(newValue));
  else if( command == binCmd ) 
    h->SetNumberOfBinsE(binCmd->GetNewIntValue(newValue));
  else if( command == verbCmd )
    h->SetVerbose(verbCmd->GetNewIntValue(newValue));
  else if (command == beamCmd)
    h->SetDefaultBeamPositionFlag(beamCmd->GetNewBoolValue(newValue));
  else if (command == edepCmd)
    h->SetMaxEnergyDeposit(edepCmd->GetNewDoubleValue(newValue));
  else if( command == updateCmd )
    Detector->UpdateGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

