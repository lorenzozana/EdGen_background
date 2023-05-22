
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

  gdmlfileCmd = new G4UIcmdWithAString("/testhadr/GdmlFile",this);
  gdmlfileCmd->SetGuidance("Select Gdml file");
  gdmlfileCmd->SetParameterName("gdmlfile",false);
  gdmlfileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

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

  lxtgCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/Length_tg_x",this);
  lxtgCmd->SetGuidance("Set thickness in x of the target (1 side)");
  lxtgCmd->SetParameterName("lxtg",false);
  lxtgCmd->SetUnitCategory("Length");
  lxtgCmd->SetRange("lxtg>0");
  lxtgCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lytgCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/Length_tg_y",this);
  lytgCmd->SetGuidance("Set thickness in y of the target (1 side)");
  lytgCmd->SetParameterName("lytg",false);
  lytgCmd->SetUnitCategory("Length");
  lytgCmd->SetRange("lytg>0");
  lytgCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lztgCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/Length_tg_z",this);
  lztgCmd->SetGuidance("Set thickness in z of the target (1 side)");
  lztgCmd->SetParameterName("lztg",false);
  lztgCmd->SetUnitCategory("Length");
  lztgCmd->SetRange("lztg>0");
  lztgCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lxwdCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/Length_wd_x",this);
  lxwdCmd->SetGuidance("Set thickness in x of the target (1 side)");
  lxwdCmd->SetParameterName("lxwd",false);
  lxwdCmd->SetUnitCategory("Length");
  lxwdCmd->SetRange("lxwd>0");
  lxwdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lywdCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/Length_wd_y",this);
  lywdCmd->SetGuidance("Set thickness in y of the target (1 side)");
  lywdCmd->SetParameterName("lywd",false);
  lywdCmd->SetUnitCategory("Length");
  lywdCmd->SetRange("lywd>0");
  lywdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lzwdCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/Length_wd_z",this);
  lzwdCmd->SetGuidance("Set thickness in z of the target (1 side)");
  lzwdCmd->SetParameterName("lzwd",false);
  lzwdCmd->SetUnitCategory("Length");
  lzwdCmd->SetRange("lzwd>0");
  lzwdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  bsizeCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/BeamSize",this);
  bsizeCmd->SetGuidance("Set Beam Size");
  bsizeCmd->SetParameterName("bsize",false);
  bsizeCmd->SetUnitCategory("Length");
  bsizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  blengthCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/BeamLength",this);
  blengthCmd->SetGuidance("Set Beam Length");
  blengthCmd->SetParameterName("blength",false);
  blengthCmd->SetUnitCategory("Length");
  blengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  vtypeCmd = new G4UIcmdWithAnInteger("/testhadr/VolumeType",this);
  vtypeCmd->SetGuidance("Set Volume Type: 1 box; 2 tube");
  vtypeCmd->SetParameterName("btype",false);
  vtypeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  btypeCmd = new G4UIcmdWithAnInteger("/testhadr/BeamType",this);
  btypeCmd->SetGuidance("Set Beam Type: 1 pencil; 2 gauss; 3 flat in volume");
  btypeCmd->SetParameterName("btype",false);
  btypeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

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
  delete gdmlfileCmd;
  delete rCmd;
  delete lCmd;
  delete rCmd2;
  delete lCmd2;
  delete lxtgCmd;
  delete lytgCmd;
  delete lztgCmd;
  delete lxwdCmd;
  delete lywdCmd;
  delete lzwdCmd;
  delete bsizeCmd;
  delete blengthCmd;
  delete btypeCmd;
  delete vtypeCmd;
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
  else if( command == gdmlfileCmd )
    Detector->SetWindowMaterial(newValue);
  else if( command == rCmd ) 
    Detector->SetTargetRadius(rCmd->GetNewDoubleValue(newValue));
  else if( command == lCmd ) 
    h->SetTargetLength(lCmd->GetNewDoubleValue(newValue));
  else if( command == rCmd2 ) 
    h->SetWindowThick_r(rCmd2->GetNewDoubleValue(newValue));
  else if( command == lCmd2 ) 
    h->SetWindowThick_z(lCmd2->GetNewDoubleValue(newValue));
  else if( command == lxtgCmd ) 
    Detector->SetTargetLx(lxtgCmd->GetNewDoubleValue(newValue));
  else if( command == lytgCmd ) 
    Detector->SetTargetLy(lytgCmd->GetNewDoubleValue(newValue));
  else if( command == lztgCmd ) 
    Detector->SetTargetLz(lztgCmd->GetNewDoubleValue(newValue));
  else if( command == lxwdCmd ) 
    Detector->SetWindowLx(lxwdCmd->GetNewDoubleValue(newValue));
  else if( command == lywdCmd ) 
    Detector->SetWindowLy(lywdCmd->GetNewDoubleValue(newValue));
  else if( command == lzwdCmd ) 
    Detector->SetWindowLz(lzwdCmd->GetNewDoubleValue(newValue));
  else if( command == bsizeCmd ) 
    h->SetBeamSize(bsizeCmd->GetNewDoubleValue(newValue));
  else if( command == blengthCmd ) 
    h->SetBeamLength(blengthCmd->GetNewDoubleValue(newValue));
  else if( command == btypeCmd ) 
    h->SetBeamType(btypeCmd->GetNewIntValue(newValue));
  else if( command == vtypeCmd ) 
    h->SetVolumeType(btypeCmd->GetNewIntValue(newValue));
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

