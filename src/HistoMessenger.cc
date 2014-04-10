
#include "HistoMessenger.hh"

#include "Histo.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoMessenger::HistoMessenger(Histo* man) : histo (man)
{

  factoryCmd = new G4UIcmdWithAString("/testhadr/HistoName",this);
  factoryCmd->SetGuidance("set name for the histograms file");

  fileCmd = new G4UIcmdWithAString("/testhadr/HistoType",this);
  fileCmd->SetGuidance("set type (hbook, root, aida) for the histograms file");
  fileCmd->SetCandidates("hbook root aida");

  optCmd = new G4UIcmdWithAString("/testhadr/HistoOption",this);
  optCmd->SetGuidance("set AIDA option for the histograms file");
   
  printCmd = new G4UIcmdWithAnInteger("/testhadr/HistoPrint",this);
  printCmd->SetGuidance("Print histogram by ID, if ID=0 - all.");
  printCmd->SetParameterName("pr",false);
  printCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  histoCmd = new G4UIcommand("/testhadr/SetHisto",this);
  histoCmd->SetGuidance("Set bining of the histo number ih :");
  histoCmd->SetGuidance("  nbBins; valMin; valMax; unit (of vmin and vmax)");
  //
  G4UIparameter* ih = new G4UIparameter("ih",'i',false);
  ih->SetGuidance("histo number : from 1 to MaxHisto");
  ih->SetParameterRange("ih>0");
  histoCmd->SetParameter(ih);
  //
  G4UIparameter* nbBins = new G4UIparameter("nbBins",'i',false);
  nbBins->SetGuidance("number of bins");
  nbBins->SetParameterRange("nbBins>0");
  histoCmd->SetParameter(nbBins);  
  //    
  G4UIparameter* valMin = new G4UIparameter("valMin",'d',false);
  valMin->SetGuidance("valMin, expressed in unit");
  histoCmd->SetParameter(valMin);  
  //    
  G4UIparameter* valMax = new G4UIparameter("valMax",'d',false);
  valMax->SetGuidance("valMax, expressed in unit");
  histoCmd->SetParameter(valMax);
  //    
  G4UIparameter* unit = new G4UIparameter("unit",'s',true);
  unit->SetGuidance("if omitted, vmin and vmax are assumed dimensionless");
  unit->SetDefaultValue("none");
  histoCmd->SetParameter(unit);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoMessenger::~HistoMessenger()
{
  delete fileCmd;
  delete histoCmd;
  delete factoryCmd;
  delete optCmd;
  delete printCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{
  if (command == factoryCmd)
    histo->setFileName(newValues);

  if (command == fileCmd)
    histo->setFileType(newValues);

  if (command == optCmd)
    histo->setFileOption(newValues);

  if (command == printCmd)
    histo->print(printCmd->GetNewIntValue(newValues));
    
  if (command == histoCmd) { 
    G4int ih, nbBins;
    G4double vmin,vmax; 
    G4String unit;
    std::istringstream is(newValues);
    is >> ih >> nbBins >> vmin >> vmax >> unit;
    G4double vUnit = 1. ;
    if (unit != "none" && unit != "") vUnit = G4UIcommand::ValueOf(unit);
    histo->setHisto1D(ih,nbBins,vmin,vmax,vUnit);
  }      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
