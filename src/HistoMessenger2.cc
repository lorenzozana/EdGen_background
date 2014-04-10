
#include "HistoMessenger2.hh"
#include "HistoManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoMessenger2::HistoMessenger2(HistoManager * Hman)
  :Hmanager(Hman)
{
  testDir = new G4UIdirectory("/outputrec/");
  testDir->SetGuidance(" Hadronic Extended Example.");

  particleCmd = new G4UIcmdWithAString("/outputrec/Particle",this);
  particleCmd->SetGuidance("set id of the particles to record in Full tree, separated by a space example 11 22 2112");
 
  infileCmd = new G4UIcmdWithAString("/testhadr/Infile",this);
  infileCmd->SetGuidance("Set input file source");
  infileCmd->SetDefaultValue("none");

  inchainCmd = new G4UIcmdWithAString("/testhadr/InChain",this);
  inchainCmd->SetGuidance("Set input file source TChain");
  inchainCmd->SetDefaultValue("Source");

  fileCmd = new G4UIcmdWithAString("/outputrec/FileName",this);
  fileCmd->SetGuidance("set filename to structure output (if not, default, output, will be used");


  //

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoMessenger2::~HistoMessenger2()
{
  delete fileCmd;
  delete particleCmd;
  delete infileCmd;
  delete inchainCmd;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoMessenger2::SetNewValue(G4UIcommand* command,G4String newValues)
{
 
  if (command == fileCmd)
    Hmanager->SetFileName(newValues.data());

   if (command == particleCmd) { 
     Hmanager->SetPartRec(newValues);
  }

   if (command == infileCmd)
     Hmanager->SetInFileName(newValues);
   
   if (command == inchainCmd)
     Hmanager->SetInChainName(newValues);


       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
