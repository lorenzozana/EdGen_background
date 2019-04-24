
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"
#include "globals.hh"


#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsListMessenger.hh"

#include "RunAction.hh"
#include "EventAction.hh"
#include "StackingAction.hh"

#include "TRandom2.h"

// #ifdef G4VIS_USE
// #include "G4VisExecutive.hh"
// #endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  //choose the Random engine
  
  //  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);

  // modify the seed
  TRandom2 *makeseed = new TRandom2(0);
  G4int modifiedseed;
  modifiedseed = makeseed->Integer(10000000);
  
  CLHEP::HepRandom::setTheSeed(modifiedseed);
  long startSeed = CLHEP::HepRandom::getTheSeed(); 
  G4cout << "Modified Seed =" << modifiedseed << "  Seed= " << startSeed << G4endl;
  
  //Construct the default run manager
  G4RunManager * runManager = new G4RunManager();

  //set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction());

  G4PhysListFactory factory;
  G4VModularPhysicsList* phys = 0;
  PhysicsListMessenger* mess = 0;
  G4String physName = "";
 
  // Physics List name defined via environment variable
  char* path = getenv("PHYSLIST");
  if (path) { physName = G4String(path); }

  // Physics List name defined via 2nd argument
  if (argc==3) { physName = argv[2]; }

  // reference PhysicsList via its name
  if(factory.IsReferencePhysList(physName)) {
    phys = factory.GetReferencePhysList(physName);
    mess = new PhysicsListMessenger();
  } 

  // local Physics List
  if(!phys) { phys = new PhysicsList(); }

  // define physics
  runManager->SetUserInitialization(phys);
  runManager->SetUserAction(new PrimaryGeneratorAction());

  //set user action classes
  runManager->SetUserAction(new RunAction());
  runManager->SetUserAction(new EventAction());
  runManager->SetUserAction(new StackingAction());

  //get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  // G4VisManager* visManager = 0;

  if (argc==1)   // Define UI terminal for interactive mode
    {
// #ifdef G4VIS_USE
//       //visualization manager
//       visManager = new G4VisExecutive;
//       visManager->Initialize();
// #endif
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
      ui->SessionStart();
      delete ui;
#endif
    }
  else           // Batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }

 startSeed = CLHEP::HepRandom::getTheSeed(); 
  G4cout << "Modified Seed =" << modifiedseed << "  Seed= " << startSeed << G4endl;
  //job termination
  // delete visManager;
  delete runManager;
  delete mess;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
