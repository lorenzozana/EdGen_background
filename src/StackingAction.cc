
#include "StackingAction.hh"

#include "HistoManager.hh"
#include "StackingMessenger.hh"

#include "G4Track.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction()
{
  stackMessenger = new StackingMessenger(this);
  histoManager   = HistoManager::GetPointer();
  killSecondary  = false;
  pname          = ""; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{
  delete stackMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
  G4ClassificationOfNewTrack status = fUrgent;

  if (aTrack->GetTrackStatus() == fAlive) 
    histoManager->ScoreNewTrack(aTrack);

  const G4String name = aTrack->GetDefinition()->GetParticleName();

  if(histoManager->GetVerbose() > 1 ) {
    G4cout << "Track #"
	   << aTrack->GetTrackID() << " of " << name
	   << " E(MeV)= " << aTrack->GetKineticEnergy()/MeV
	   << " produced by " 
	   << histoManager->CurrentParticle()->GetParticleName()
	   << " ID= " << aTrack->GetParentID()
	   << " with E(MeV)= " << histoManager->CurrentKinEnergy()/MeV
	   << G4endl;
  }
  if(aTrack->GetTrackID() == 1) return status;

  //stack or delete secondaries
  if (killSecondary)      status = fKill;
  else if(pname == name)  status = fKill; 

  return status;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
