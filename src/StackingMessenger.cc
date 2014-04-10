
#include "StackingMessenger.hh"

#include "StackingAction.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingMessenger::StackingMessenger(StackingAction* stack)
:stackAction(stack)
{
  killCmd = new G4UIcmdWithABool("/testhadr/KillAllSecondaries",this);
  killCmd->SetGuidance("  Choice : true false");
  killCmd->SetParameterName("choice",true);
  killCmd->SetDefaultValue(false);

  kCmd = new G4UIcmdWithAString("/testhadr/Kill", this);
  kCmd->SetGuidance("Kill secondary particles of defined type");
  kCmd->SetParameterName("ch", true);
  kCmd->SetDefaultValue("none");
  kCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingMessenger::~StackingMessenger()
{
  delete killCmd;
  delete kCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{     
  if(command == killCmd)
    stackAction->SetKillStatus(killCmd->GetNewBoolValue(newValue));               

  if(command == kCmd)
    stackAction->SetKill(newValue);               
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
