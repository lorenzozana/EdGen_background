
#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys)
:pPhysicsList(pPhys)
{   
  gammaCutCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/CutGamma",this);  
  gammaCutCmd->SetGuidance("Set gamma cut.");
  gammaCutCmd->SetParameterName("Gcut",false);
  gammaCutCmd->SetUnitCategory("Length");
  gammaCutCmd->SetRange("Gcut>=0.0");
  gammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  electCutCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/CutEl",this);  
  electCutCmd->SetGuidance("Set electron cut.");
  electCutCmd->SetParameterName("Ecut",false);
  electCutCmd->SetUnitCategory("Length");
  electCutCmd->SetRange("Ecut>=0.0");
  electCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  posCutCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/CutPos",this);
  posCutCmd->SetGuidance("Set positron cut.");
  posCutCmd->SetParameterName("Pcut",false);
  posCutCmd->SetUnitCategory("Length");
  posCutCmd->SetRange("Pcut>=0.0");
  posCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  pCutCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/CutProt",this);
  pCutCmd->SetGuidance("Set proton cut.");
  pCutCmd->SetParameterName("ProtCut",false);
  pCutCmd->SetUnitCategory("Length");
  pCutCmd->SetRange("ProtCut>=0.0");
  pCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  allCutCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/CutsAll",this);
  allCutCmd->SetGuidance("Set cut for all.");
  allCutCmd->SetParameterName("cut",false);
  allCutCmd->SetUnitCategory("Length");
  allCutCmd->SetRange("cut>=0.0");
  allCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  pListCmd = new G4UIcmdWithAString("/testhadr/Physics",this);
  pListCmd->SetGuidance("Add modula physics list.");
  pListCmd->SetParameterName("PList",false);
  pListCmd->AvailableForStates(G4State_PreInit);

  listCmd = new G4UIcmdWithoutParameter("/testhadr/ListPhysics",this);
  listCmd->SetGuidance("Available Physics Lists");
  listCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete gammaCutCmd;
  delete electCutCmd;
  delete posCutCmd;
  delete pCutCmd;
  delete allCutCmd;
  delete pListCmd;
  delete listCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  G4UImanager* UI = G4UImanager::GetUIpointer();
  if( command == gammaCutCmd ) {
    if(pPhysicsList) {
      pPhysicsList->SetCutForGamma(gammaCutCmd->GetNewDoubleValue(newValue));
    } else {
      UI->ApplyCommand("/run/setCutForAGivenParticle gamma " + newValue);
    }

  } else if( command == electCutCmd ) {
    if(pPhysicsList) {
      pPhysicsList->SetCutForElectron(electCutCmd->GetNewDoubleValue(newValue));
    } else {
      UI->ApplyCommand("/run/setCutForAGivenParticle e- " + newValue);
    }

  } else if( command == posCutCmd ) {
    if(pPhysicsList) {
      pPhysicsList->SetCutForPositron(posCutCmd->GetNewDoubleValue(newValue));
    } else {
      UI->ApplyCommand("/run/setCutForAGivenParticle e+ " + newValue);
    }

  } else if( command == pCutCmd ) {
    if(pPhysicsList) {
      pPhysicsList->SetCutForProton(pCutCmd->GetNewDoubleValue(newValue));
    } else {
      UI->ApplyCommand("/run/setCutForAGivenParticle proton " + newValue);
    }

  } else if( command == allCutCmd ) {

    if(pPhysicsList) {
      G4double cut = allCutCmd->GetNewDoubleValue(newValue);
      pPhysicsList->SetCutForGamma(cut);
      pPhysicsList->SetCutForElectron(cut);
      pPhysicsList->SetCutForPositron(cut);
      pPhysicsList->SetCutForProton(cut);
    } else {
      UI->ApplyCommand("/run/setCut " + newValue);
    }

  } else if( command == pListCmd ) {
    if(pPhysicsList) {
      G4String name = newValue;
      if(name == "PHYSLIST") {
	char* path = getenv(name);
	if (path) name = G4String(path);
	else {
	  G4cout << "### PhysicsListMessenger WARNING: "
		 << " environment variable PHYSLIST is not defined"
		 << G4endl;
	  return; 
	}
      }
      pPhysicsList->AddPhysicsList(name);
    } else {
      G4cout << "### PhysicsListMessenger WARNING: "
	     << " /testhadr/Physics UI command is not available "
	     << "for reference Physics List" << G4endl;
    }

  } else if( command == listCmd ) {
    if(pPhysicsList) {
      pPhysicsList->List();
    } else { 
      G4cout << "### PhysicsListMessenger WARNING: "
	     << " /testhadr/ListPhysics UI command is not available "
	     << "for reference Physics List" << G4endl;
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
