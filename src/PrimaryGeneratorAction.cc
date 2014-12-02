
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"`
#include "HistoManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  particleGun  = new G4ParticleGun(1);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  histo = HistoManager::GetPointer();
  particleTable = G4ParticleTable::GetParticleTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(histo->DefaultBeamPosition()) {
    G4double zVertex = -(5.0*CLHEP::mm + histo->Length());
    particleGun->SetParticlePosition(G4ThreeVector(0.,0.,zVertex));
   
  }
  if(histo->DefaultInFile()) {
    histo->ReadInFileName();
    G4ParticleDefinition* particle
      = particleTable->FindParticle(histo->GetPDGEncoding());
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(histo->GetInDirectionX(),histo->GetInDirectionY(),histo->GetInDirectionZ()));
    ener_p=pow((pow(histo->GetInMomentum(),2)+pow(particle->GetPDGMass(),2)),0.5);
    particleGun->SetParticleEnergy(ener_p);
    particleGun->SetParticlePosition(G4ThreeVector(histo->GetInVertexX(),histo->GetInVertexY(),histo->GetInVertexZ()));
    //    G4cout << "Generate new event momentum set to" << histo->GetInMomentum() << " dz=" << histo->GetInDirectionZ() << G4endl;
  }
  particleGun->GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
