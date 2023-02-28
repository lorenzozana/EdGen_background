
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "HistoManager.hh"
#include "Randomize.hh"

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
    G4double xvertex = histo->BeamSize();
    G4double yvertex = histo->BeamSize();
    G4int btype = histo->BeamType();
    if (btype == 1) {  // Pencil Beam shape
      while (pow(xvertex*xvertex+yvertex*yvertex,0.5)> histo->BeamSize()) {
	xvertex = histo->BeamSize() *G4UniformRand();
	yvertex = histo->BeamSize() *G4UniformRand();
      }
    }
    else { // Gaussian Beam Size
      xvertex = G4RandGauss::shoot(0.,xvertex);
      yvertex = G4RandGauss::shoot(0.,yvertex);
    }
    particleGun->SetParticlePosition(G4ThreeVector(xvertex,yvertex,zVertex));
   
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
