
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
  frand = new TF1("frand","sin(x)",0.0,CLHEP::pi);
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
    G4double  xdir,ydir,zdir;
    G4double theta,phi;
    G4int btype = histo->BeamType();
    if (btype == 1) {  // Pencil Beam shape
      while (pow(xvertex*xvertex+yvertex*yvertex,0.5)> histo->BeamSize()) {
	xvertex = histo->BeamSize() *(-1. + 2.*G4UniformRand());
	yvertex = histo->BeamSize() *(-1. + 2.*G4UniformRand());
      }
    }
    else if (btype == 2) { // Gaussian Beam Size
      xvertex = G4RandGauss::shoot(0.,xvertex);
      yvertex = G4RandGauss::shoot(0.,yvertex);
    }
    else if (btype == 3) { // Flat inside the volume (Cylinder)
      while (pow(xvertex*xvertex+yvertex*yvertex,0.5)> histo->BeamSize()) {
	xvertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
	yvertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
      }
      zVertex = histo->BeamLength()/2 *(-1.+2.*G4UniformRand());
      theta = frand->GetRandom(0.,CLHEP::pi);
      phi = 2* CLHEP::pi *G4UniformRand();
      xdir = sin(theta) * cos(phi);
      ydir = sin(theta) * sin(phi);
      zdir = cos(theta);
      // if (cos(theta)>0.0) zdir =pow(1.-pow(xdir,2)-pow(ydir,2),0.5);
      // else  zdir =- pow(1.-pow(xdir,2)-pow(ydir,2),0.5);
      //      G4cout << sin(theta) << " \t" << xvertex << " \t" << yvertex << " \t" << zVertex << " \t" << xdir << " \t" << ydir << " \t" << zdir << " \t" << cos(theta) << G4endl; 
      particleGun->SetParticleMomentumDirection(G4ThreeVector(xdir,ydir,zdir));
    }
    else if (btype == 4) { // Flat inside the volume (Box)
      xvertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
      yvertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
      zVertex = histo->BeamLength()/2 *(-1.+2.*G4UniformRand());
      theta = frand->GetRandom(0.,CLHEP::pi);
      phi = 2* CLHEP::pi *G4UniformRand();
      xdir = sin(theta) * cos(phi);
      ydir = sin(theta) * sin(phi);
      zdir = cos(theta);
      // if (cos(theta)>0.0) zdir =pow(1.-pow(xdir,2)-pow(ydir,2),0.5);
      // else  zdir =- pow(1.-pow(xdir,2)-pow(ydir,2),0.5);
      particleGun->SetParticleMomentumDirection(G4ThreeVector(xdir,ydir,zdir));

    }
    else if (btype == 5) { // Flat inside the volume (Sphere)
      while (pow(xvertex*xvertex+yvertex*yvertex+zVertex*zVertex,0.5)> histo->BeamSize()) {
	xvertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
	yvertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
	zVertex = histo->BeamSize() *(-1.+2.*G4UniformRand());
	theta = frand->GetRandom(0.,CLHEP::pi);
	phi = 2* CLHEP::pi *G4UniformRand();
	xdir = sin(theta) * cos(phi);
	ydir = sin(theta) * sin(phi);
	zdir = cos(theta);
	// if (cos(theta)>0.0) zdir =pow(1.-pow(xdir,2)-pow(ydir,2),0.5);
	// else  zdir =- pow(1.-pow(xdir,2)-pow(ydir,2),0.5);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(xdir,ydir,zdir));

      }
    }

    particleGun->SetParticlePosition(G4ThreeVector(xvertex,yvertex,zVertex));
   
  }
  if(histo->DefaultInFile()) {
    histo->ReadInFileName();
    G4ParticleDefinition* particle
      = particleTable->FindParticle(histo->GetPDGEncoding());
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(histo->GetInDirectionX(),histo->GetInDirectionY(),histo->GetInDirectionZ()));
    ener_p=pow((pow(histo->GetInMomentum()*CLHEP::MeV,2)+pow(particle->GetPDGMass()*CLHEP::MeV,2)),0.5);
    particleGun->SetParticleEnergy(ener_p*CLHEP::MeV);
    particleGun->SetParticlePosition(G4ThreeVector(histo->GetInVertexX(),histo->GetInVertexY(),histo->GetInVertexZ()));
    //    G4cout << "Generate new event momentum set to" << histo->GetInMomentum() << " dz=" << histo->GetInDirectionZ() << G4endl;
  }
  particleGun->GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
