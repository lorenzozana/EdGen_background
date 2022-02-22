#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"
#include "HistoMessenger2.hh"
#include "G4UnitsTable.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4PionZero.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4KaonZeroShort.hh"
#include "G4KaonZeroLong.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "Histo.hh"
#include "globals.hh"
#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager* HistoManager::fManager = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager* HistoManager::GetPointer()
{
  if(!fManager) {
    static HistoManager manager;
    fManager = &manager;
  }
  return fManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager::HistoManager()
{
  atentry = 0;
  verbose=  0;
  nSlices   = 300;
  nBinsE    = 100;
  nHisto    = 25;
  length    = 300.*CLHEP::mm;
  radius    = 1.*CLHEP::cm;
  edepMax   = 1.0*CLHEP::GeV;
  beamFlag  = true;
  material  = 0;
  elm       = 0;
  windmaterial = 0;
  windelm   = 0;
  sprintf(defaultname,"output");
  fTree = new TTree("T", "Geant4 Monte Carlo");
  // nTree = new TTree("N", "Neutron Geant4 Monte Carlo");
  tTree = new TTree("Full", "Full leaking Geant4 Monte Carlo");
  neutron   = G4Neutron::Neutron();
  histoMessenger2 = new HistoMessenger2(this);
  InputFlag = false;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager::~HistoManager()
{
  delete fTree;
  //  delete nTree;
  delete tTree;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::bookHisto()
{
  // G4ParticleGun*   partGun = primGenAction::GetPointer()->GetParticleGun();
  // G4double partGunEner = partGun->GetParticleEnergy();
  G4double partGunEner = 1000.;
  H1_Edep = new TH1F("H1_Edep","H1_Edep",1000,0.,partGunEner);
  H1_Egamma = new TH1F("H1_Egamma","H1_Egamma",1000,0.,partGunEner);
  H1_Eelectron = new TH1F("H1_Eelectron","H1_Eelectron",1000,0.,partGunEner);
  H1_Epositron = new TH1F("H1_Epositron","H1_Epositron",1000,0.,partGunEner);
  H1_Eneutron = new TH1F("H1_Eneutron","H1_Eneutron",1000,0.,partGunEner);
  H1_Eproton = new TH1F("H1_Eproton","H1_Eproton",1000,0.,partGunEner);
  H1_Eantiproton = new TH1F("H1_Eantiproton","H1_Eantiproton",1000,0.,partGunEner);
  H1_Epiplus = new TH1F("H1_Epiplus","H1_Epiplus",1000,0.,partGunEner);
  H1_Epiminus = new TH1F("H1_Epiminus","H1_Epiminus",1000,0.,partGunEner);
  H1_Epi0 = new TH1F("H1_Epi0","H1_Epi0",1000,0.,partGunEner);
  H1_Ekaons = new TH1F("H1_Ekaons","H1_Ekaons",1000,0.,partGunEner);
  H1_Emuons = new TH1F("H1_Emuons","H1_Emuons",1000,0.,partGunEner);
  H1_Edeuterons = new TH1F("H1_Edeuterons","H1_Edeuterons",1000,0.,partGunEner);
  H1_Etriton = new TH1F("H1_Etriton","H1_Etriton",1000,0.,partGunEner);
  H1_EHe3 = new TH1F("H1_EHe3","H1_EHe3",1000,0.,partGunEner);
  H1_Ealpha = new TH1F("H1_Ealpha","H1_Ealpha",1000,0.,partGunEner);
  H1_Efwdneutron = new TH1F("H1_Efwdneutron","H1_Efwdneutron",1000,0.,partGunEner);
  H1_Ebwdneutron = new TH1F("H1_Ebwdneutron","H1_Ebwdneutron",1000,0.,partGunEner);
  
  fTree->Branch("event_n", &event_n, "event_n/I") ;
  fTree->Branch("track_id", &track_id, "track_id/I") ;
  fTree->Branch("part_id", &part_id, "part_id/I") ;  
  fTree->Branch("enedep_tg", &enedep_tg, "enedep_tg/D") ; //"1","Energy deposition (MeV/mm/event) in the target",	nSlices,0.0,length/mm,MeV/mm);
  fTree->Branch("zdep_tg", &zdep_tg , "zdep_tg/D");
  fTree->Branch("ener", &ener , "ener/D") ;
  fTree->Branch("mom_x", &mom_x, "mom_x/D");
  fTree->Branch("mom_y", &mom_y, "mom_y/D");
  fTree->Branch("mom_z", &mom_z, "mom_z/D");
  fTree->Branch("vert_x", &vert_x , "vert_x/D");
  fTree->Branch("vert_y", &vert_y, "vert_y/D");
  fTree->Branch("vert_z", &vert_z, "vert_z/D");
  fTree->Branch("mass", &mass, "mass/D");





  fTree->Branch("en_sideleak_neut", &en_sideleak_neut, "en_sideleak_neut/D") ; //"15","log10 Energy (MeV) of side-leaked neutrons",nBinsE,-5.,5.,1.0);
  fTree->Branch("en_forwleak_neut", &en_forwleak_neut, "en_forwleak_neut/D") ; //16","log10 Energy (MeV) of forward-leaked neutrons",nBinsE,-5.,5.,1.0);
  fTree->Branch("en_backleak_neut", &en_backleak_neut, "en_backleak_neut/D") ; //17","log10 Energy (MeV) of backward-leaked neutrons",nBinsE,-5.,5.,1.0);
  fTree->Branch("en_leak_prot", &en_leak_prot, "en_leak_prot/D") ; //"18","log10 Energy (MeV) of leaking protons",nBinsE,-4.,6.,1.0);
  fTree->Branch("en_leak_chargpion", &en_leak_chargpion, "en_leak_chargpion/D") ; //"19","log10 Energy (MeV) of leaking charged pions",nBinsE,-4.,6.,1.0);
  fTree->Branch("en_deptg_beam", &en_deptg_beam, "en_deptg_beam/D") ; //"22","Energy deposition in the target normalized to beam energy",	      110,0.0,1.1,1.0);
fTree->Branch("en_EMdeptg_beam", &en_EMdeptg_beam, "en_EMdeptg_beam/D") ; //23","EM energy deposition in the target normalized to beam energy",	    110,0.0,1.1,1.0);
fTree->Branch("en_pideptg_beam", &en_pideptg_beam, "en_pideptg_beam/D") ; //24","Pion energy deposition in the target normalized to beam energy",	       110,0.0,1.1,1.0);
fTree->Branch("en_protdeptg_beam", &en_protdeptg_beam, "en_protdeptg_beam/D") ; //25","Proton energy deposition in the target normalized to beam energy",	       110,0.0,1.1,1.0);
 fTree->Branch("en_depwd_beam", &en_depwd_beam, "en_depwd_beam/D") ; //"22","Energy deposition in the window normalized to beam energy",	      110,0.0,1.1,1.0);
fTree->Branch("en_EMdepwd_beam", &en_EMdepwd_beam, "en_EMdepwd_beam/D") ; //23","EM energy deposition in the window normalized to beam energy",	    110,0.0,1.1,1.0);
fTree->Branch("en_pidepwd_beam", &en_pidepwd_beam, "en_pidepwd_beam/D") ; //24","Pion energy deposition in the window normalized to beam energy",	       110,0.0,1.1,1.0);
fTree->Branch("en_protdepwd_beam", &en_protdepwd_beam, "en_protdepwd_beam/D") ; //25","Proton energy deposition in the window normalized to beam energy",	       110,0.0,1.1,1.0);
 fTree->Branch("H1_Edep","TH1F",&H1_Edep,32000,0);
 fTree->Branch("H1_Egamma","TH1F",&H1_Egamma,32000,0);
 fTree->Branch("H1_Eelectron","TH1F",&H1_Eelectron,32000,0);
 fTree->Branch("H1_Epositron","TH1F",&H1_Epositron,32000,0);
 fTree->Branch("H1_Eneutron","TH1F",&H1_Eneutron,32000,0);
 fTree->Branch("H1_Eproton","TH1F",&H1_Eproton,32000,0);
 fTree->Branch("H1_Eantiproton","TH1F",&H1_Eantiproton,32000,0);
 fTree->Branch("H1_Epiplus","TH1F",&H1_Epiplus,32000,0);
 fTree->Branch("H1_Epiminus","TH1F",&H1_Epiminus,32000,0);
 fTree->Branch("H1_Epi0","TH1F",&H1_Epi0,32000,0);
 fTree->Branch("H1_Ekaons","TH1F",&H1_Ekaons,32000,0);
 fTree->Branch("H1_Emuons","TH1F",&H1_Emuons,32000,0);
 fTree->Branch("H1_Edeuterons","TH1F",&H1_Edeuterons,32000,0);
 fTree->Branch("H1_Etriton","TH1F",&H1_Etriton,32000,0);
 fTree->Branch("H1_EHe3","TH1F",&H1_EHe3,32000,0);
 fTree->Branch("H1_Ealpha","TH1F",&H1_Ealpha,32000,0);
 fTree->Branch("H1_Efwdneutron","TH1F",&H1_Efwdneutron,32000,0);
 fTree->Branch("H1_Ebwdneutron","TH1F",&H1_Ebwdneutron,32000,0);




 // nTree->Branch("event_n", &event_n, "event_n/I") ;
 // nTree->Branch("neutron_ener", &neutron_ener, "neutron_ener/D");
 // nTree->Branch("neutron_theta", &neutron_theta, "neutron_theta/D");
 // nTree->Branch("vert_x", &vert_x , "vert_x/D");
 // nTree->Branch("vert_y", &vert_y, "vert_y/D");
 // nTree->Branch("vert_z", &vert_z, "vert_z/D");
 // nTree->Branch("mom_x", &mom_x, "mom_x/D");
 // nTree->Branch("mom_y", &mom_y, "mom_y/D");
 // nTree->Branch("mom_z", &mom_z, "mom_z/D");
 // nTree->Branch("part_id", &part_id, "part_id/I") ; 
 

 tTree->Branch("event_n", &event_n, "event_n/I") ;
 tTree->Branch("ener", &ener, "ener/D");
 tTree->Branch("ener_vert", &ener_vert, "ener_vert/D");
 tTree->Branch("theta", &theta, "theta/D");
 tTree->Branch("vert_x", &vert_x , "vert_x/D");
 tTree->Branch("vert_y", &vert_y, "vert_y/D");
 tTree->Branch("vert_z", &vert_z, "vert_z/D");
 tTree->Branch("mom_x", &mom_x, "mom_x/D");
 tTree->Branch("mom_y", &mom_y, "mom_y/D");
 tTree->Branch("mom_z", &mom_z, "mom_z/D");
 tTree->Branch("leak_x", &leak_x , "leak_x/D");
 tTree->Branch("leak_y", &leak_y, "leak_y/D");
 tTree->Branch("leak_z", &leak_z, "leak_z/D");
 tTree->Branch("part_id", &part_id, "part_id/I") ;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::BeginOfRun()
{
  full_r      = radius + thick_r;
  full_z      = 0.5*length + thick_z;
  absZ0       = -0.5*length;
  n_evt       = 0;
  n_elec      = 0;
  n_posit     = 0;
  n_gam       = 0;
  n_step      = 0;
  n_prot_leak = 0;
  n_pion_leak = 0;
  n_ions      = 0;
  n_deut      = 0;
  n_alpha     = 0;
  n_kaons     = 0;
  n_muons     = 0;
  n_cpions    = 0;
  n_pi0       = 0;
  n_neutron   = 0;
  n_proton    = 0;
  n_aproton   = 0;
  n_neu_forw  = 0;
  n_neu_leak  = 0;
  n_neu_back  = 0;

  edepSum     = 0.0;
  edepSum2    = 0.0;

  

  bookHisto();
  //  histo->book();

  if(verbose > 0) 
    G4cout << "HistoManager: Histograms are booked and run has been started"
           <<G4endl<<"  BeginOfRun (After histo->book)"<< G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::EndOfRun()
{

  G4cout << "HistoManager: End of run actions are started" << G4endl;

  // Average values
  G4cout<<"========================================================"<<G4endl;

  G4double x = (G4double)n_evt;
  if(n_evt > 0) x = 1.0/x;

  G4double xe = x*(G4double)n_elec;
  G4double xg = x*(G4double)n_gam;
  G4double xp = x*(G4double)n_posit;
  G4double xs = x*(G4double)n_step;
  G4double xn = x*(G4double)n_neutron;
  G4double xpn = x*(G4double)n_proton;
  G4double xap = x*(G4double)n_aproton;
  G4double xnf = x*(G4double)n_neu_forw;
  G4double xnbw = x*(G4double)n_neu_leak;
  G4double xnb = x*(G4double)n_neu_back;
  G4double xpl = x*(G4double)n_prot_leak;
  G4double xal = x*(G4double)n_pion_leak;
  G4double xpc = x*(G4double)n_cpions;
  G4double xp0 = x*(G4double)n_pi0;
  G4double xpk = x*(G4double)n_kaons;
  G4double xpm = x*(G4double)n_muons;
  G4double xid = x*(G4double)n_deut;
  G4double xia = x*(G4double)n_alpha;
  G4double xio = x*(G4double)n_ions;

  edepSum  *= x;
  edepSum2 *= x;
  edepSum2 -= edepSum*edepSum;
  if(edepSum2 > 0.0) edepSum2 = std::sqrt(edepSum2);
  else               edepSum2 = 0.0;

  G4cout                         << "Beam particle                        "
				 << primaryDef->GetParticleName() <<G4endl;
  G4cout                         << "Beam Energy(MeV)                     " 
				 << primaryKineticEnergy/CLHEP::MeV <<G4endl;
  G4cout                         << "Number of events                     " << n_evt <<G4endl;
  G4cout << std::setprecision(4) << "Average energy deposit (MeV)         " << edepSum/CLHEP::MeV 
	 << "   RMS(MeV) " << edepSum2/CLHEP::MeV << G4endl;
  G4cout << std::setprecision(4) << "Average number of steps              " << xs << G4endl;
  G4cout << std::setprecision(4) << "Average number of gamma              " << xg << G4endl;
  G4cout << std::setprecision(4) << "Average number of e-                 " << xe << G4endl;
  G4cout << std::setprecision(4) << "Average number of e+                 " << xp << G4endl;
  G4cout << std::setprecision(4) << "Average number of neutrons           " << xn << G4endl;
  G4cout << std::setprecision(4) << "Average number of protons            " << xpn << G4endl;
  G4cout << std::setprecision(4) << "Average number of antiprotons        " << xap << G4endl;
  G4cout << std::setprecision(4) << "Average number of pi+ & pi-          " << xpc << G4endl;
  G4cout << std::setprecision(4) << "Average number of pi0                " << xp0 << G4endl;
  G4cout << std::setprecision(4) << "Average number of kaons              " << xpk << G4endl;
  G4cout << std::setprecision(4) << "Average number of muons              " << xpm << G4endl;
  G4cout << std::setprecision(4) << "Average number of deuterons+tritons  " << xid << G4endl;
  G4cout << std::setprecision(4) << "Average number of He3+alpha          " << xia << G4endl;
  G4cout << std::setprecision(4) << "Average number of ions               " << xio << G4endl;
  G4cout << std::setprecision(4) << "Average number of forward neutrons   " << xnf << G4endl;
  G4cout << std::setprecision(4) << "Average number of reflected neutrons " << xnb << G4endl;
  G4cout << std::setprecision(4) << "Average number of side neutrons      " << xnbw << G4endl;
  G4cout << std::setprecision(4) << "Average number of proton leak        " << xpl << G4endl;
  G4cout << std::setprecision(4) << "Average number of pion leak          " << xal << G4endl;
  G4cout<<"========================================================"<<G4endl;
  G4cout<<G4endl;

  // // normalise histograms
  // for(G4int i=0; i<nHisto; i++) { 
  //   histo->scale(i,x);
  // }

  // if(verbose > 1) histo->print(0);
  //  histo->save();
  fTree->Fill(); // Fill the main Tree, so I can have the information on the beam, and the event number
    // Secondary track
  fTree->Write();
  // nTree->Write();
  tTree->Write();
  fOutfile->Close();
  delete fOutfile;

  return;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::BeginOfEvent()
{
  edepEvt = 0.0;
  edepEM  = 0.0;
  edepPI  = 0.0;
  edepP   = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::EndOfEvent()
{
  edepSum  += edepEvt;
  edepSum2 += edepEvt*edepEvt;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::ScoreNewTrack(const G4Track* track)
{
  const G4ParticleDefinition* pd = track->GetDefinition();
  G4String name = pd->GetParticleName();
  G4double e = track->GetKineticEnergy();
  
  G4ThreeVector vertex = track->GetPosition();
  G4ThreeVector momentum = track->GetMomentum();

  track_id = track->GetParentID();
  ener = e/CLHEP::MeV; // MeV
  
  mom_x = momentum.x()/CLHEP::MeV;
  mom_y = momentum.y()/CLHEP::MeV;
  mom_z = momentum.z()/CLHEP::MeV;
  vert_x = vertex.x()/CLHEP::cm;
  vert_y = vertex.y()/CLHEP::cm;
  vert_z = vertex.z()/CLHEP::cm;
  mass = pd->GetPDGMass()/CLHEP::MeV ; // mass in MeV
  // G4cout << "Event n" << n_evt << "  Track id=" << track_id << G4endl;
  
 

  // Primary track
  if(0 == track->GetParentID()) {

    n_evt++;
    event_n = n_evt;
    primaryKineticEnergy = e;
    primaryDef = pd;
    G4ThreeVector dir = track->GetMomentumDirection();
    if(1 < verbose) 
      G4cout << "### Primary " << name 
	     << " kinE(MeV)= " << e/CLHEP::MeV
	     << "; m(MeV)= " << pd->GetPDGMass()/CLHEP::MeV
	     << "; pos(mm)= " << track->GetPosition()/CLHEP::mm 
	     << ";  dir= " << track->GetMomentumDirection() 
	     << G4endl;
    //   fTree->Fill(); // Fill the main Tree, so I can have the information on the beam, and the event number
    // Secondary track
  } else {
    if(1 < verbose) 
      G4cout << "=== Secondary " << name 
	     << " kinE(MeV)= " << e/CLHEP::MeV
	     << "; m(MeV)= " << pd->GetPDGMass()/CLHEP::MeV
	     << "; pos(mm)= " << track->GetPosition()/CLHEP::mm 
	     << ";  dir= " << track->GetMomentumDirection() 
	     << G4endl;
    e = std::log10(e/CLHEP::MeV);
    if(pd == G4Gamma::Gamma()) {
      n_gam++;
      part_id = 22;
 
    } else if ( pd == G4Electron::Electron()) {
      part_id = 11;
      n_elec++;
 
    } else if ( pd == G4Positron::Positron()) {
      n_posit++;
      part_id = -11;
    } else if ( pd == G4Proton::Proton()) {
      n_proton++;
      part_id = 2212;

    } else if ( pd == neutron) {
      n_neutron++;
      part_id = 2112;
      neutron_theta = momentum.theta();
      neutron_ener = ener;
      //      nTree->Fill(); // Here all track

    } else if ( pd == G4AntiProton::AntiProton()) {
      n_aproton++;
      part_id = -2212;
    } else if ( pd == G4PionPlus::PionPlus() ) {
      n_cpions++;
      part_id = 211;
      
    } else if ( pd == G4PionMinus::PionMinus()) {
      n_cpions++;
      part_id = -211;
      
    } else if ( pd == G4PionZero::PionZero()) {
      n_pi0++;
      part_id = 111;
      
    } else if ( pd == G4KaonPlus::KaonPlus() ) {
      n_kaons++;
      part_id = 321;

    } else if ( pd == G4KaonMinus::KaonMinus()) {
     n_kaons++;
      part_id = -321;

    }  else if ( pd == G4KaonZeroShort::KaonZeroShort() ) {
      n_kaons++;
      part_id =310;
    } else if ( pd == G4KaonZeroLong::KaonZeroLong()) {
      n_kaons++;
      part_id = 130;
    } else if ( pd == G4Deuteron::Deuteron() ) {
      n_deut++;
      part_id = 95;
    } else if ( pd == G4Triton::Triton()) {
      n_deut++;
      part_id = 96;
    } else if ( pd == G4He3::He3() ) {
      n_alpha++;
      part_id = 98;
    } else if ( pd == G4Alpha::Alpha()) {
      n_alpha++;
      part_id = 97;
    } else if ( pd->GetParticleType() == "nucleus") {
      n_ions++;
  
    } else if ( pd == G4MuonPlus::MuonPlus() ) {
      n_muons++ ;
      part_id = -13;
    } else if ( pd == G4MuonMinus::MuonMinus()) {
      n_muons++;
      part_id = 13;    
    }
  }
  // Here fill the main Tree
  //  fTree->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::AddTargetStep(const G4Step* step)
{
  n_step++;
  G4double edep = step->GetTotalEnergyDeposit();
  if(edep >= DBL_MIN) { 
    const G4Track* track = step->GetTrack();
    currentDef = track->GetDefinition(); 
    currentKinEnergy = track->GetKineticEnergy();

    G4ThreeVector pos = 
      (step->GetPreStepPoint()->GetPosition() +
       step->GetPostStepPoint()->GetPosition())*0.5;

    G4double z = pos.z() - absZ0;

    // scoring
    edepEvt += edep;
    enedep_tg = edep;
    en_deptg_beam = edep;
    zdep_tg = z;
    //    histo->fill(0,z,edep);
    const G4ParticleDefinition* pd = currentDef;

    if(pd == G4Gamma::Gamma() || pd == G4Electron::Electron() 
       || pd == G4Positron::Positron()) {
      edepEM += edep;
      en_EMdeptg_beam = edep;
    } else if ( pd == G4PionPlus::PionPlus() || pd == G4PionMinus::PionMinus()) {
      edepPI += edep;
      en_pideptg_beam = edep;
    } else if ( pd == G4Proton::Proton() || pd == G4AntiProton::AntiProton()) {
      edepP  += edep;
      en_protdeptg_beam = edep;
    }

    if(1 < verbose) 
      G4cout << "HistoManager::AddEnergy: e(keV)= " << edep/CLHEP::keV
	     << "; z(mm)= " << z/CLHEP::mm
	     << "; step(mm)= " << step->GetStepLength()/CLHEP::mm
	     << " by " << currentDef->GetParticleName()
	     << " E(MeV)= " << currentKinEnergy/CLHEP::MeV
	     << G4endl;
  }
}

void HistoManager::AddWindowStep(const G4Step* step)
{
  n_step++;
  G4double edep = step->GetTotalEnergyDeposit();
  if(edep >= DBL_MIN) { 
    const G4Track* track = step->GetTrack();
    currentDef = track->GetDefinition(); 
    currentKinEnergy = track->GetKineticEnergy();

    G4ThreeVector pos = 
      (step->GetPreStepPoint()->GetPosition() +
       step->GetPostStepPoint()->GetPosition())*0.5;

    G4double z = pos.z() - absZ0;

    // scoring
    edepEvt += edep;
    enedep_tg = edep;
    en_depwd_beam = edep;
 
    //    histo->fill(0,z,edep);
    const G4ParticleDefinition* pd = currentDef;

    if(pd == G4Gamma::Gamma() || pd == G4Electron::Electron() 
       || pd == G4Positron::Positron()) {
      edepEM += edep;
      en_EMdepwd_beam = edep;
    } else if ( pd == G4PionPlus::PionPlus() || pd == G4PionMinus::PionMinus()) {
      edepPI += edep;
      en_pidepwd_beam = edep;
    } else if ( pd == G4Proton::Proton() || pd == G4AntiProton::AntiProton()) {
      edepP  += edep;
      en_protdepwd_beam = edep;
    }

    if(1 < verbose) 
      G4cout << "HistoManager::AddEnergy: e(keV)= " << edep/CLHEP::keV
	     << "; z(mm)= " << z/CLHEP::mm
	     << "; step(mm)= " << step->GetStepLength()/CLHEP::mm
	     << " by " << currentDef->GetParticleName()
	     << " E(MeV)= " << currentKinEnergy/CLHEP::MeV
	     << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::AddLeakingParticle(const G4Track* track)
{
  const G4ParticleDefinition* pd = track->GetDefinition(); 
  G4double e = std::log10(track->GetKineticEnergy()/CLHEP::MeV);

  G4ThreeVector pos = track->GetPosition();
  G4ThreeVector dir = track->GetMomentumDirection();
  G4double x = pos.x();
  G4double y = pos.y();
  G4double z = pos.z();
  G4double posrad = pow( (pow(x,2) + pow(y,2) ),0.5) ;

  G4ThreeVector vertex = track->GetVertexPosition();
  G4ThreeVector momentum = track->GetMomentum();

  track_id = track->GetParentID();
  ener = track->GetKineticEnergy()/CLHEP::MeV; // MeV
  ener_vert = track->GetVertexKineticEnergy()/CLHEP::MeV; // MeV
  mom_x = momentum.x()/CLHEP::MeV;
  mom_y = momentum.y()/CLHEP::MeV;
  mom_z = momentum.z()/CLHEP::MeV;
  vert_x = vertex.x()/CLHEP::cm;
  vert_y = vertex.y()/CLHEP::cm;
  vert_z = vertex.z()/CLHEP::cm;
  leak_x = x/CLHEP::cm;
  leak_y = y/CLHEP::cm;
  leak_z = z/CLHEP::cm;
  part_id=pd->GetPDGEncoding();
  theta = momentum.theta();
  G4bool isLeaking = false;

  // Forward 
  if(z > full_z && dir.z() > 0.0) {
    isLeaking = true;
    if(pd == neutron) {
      ++n_neu_forw;
      en_forwleak_neut = e; 
      H1_Eneutron->Fill(e);
      // neutron_theta = momentum.theta();
      // neutron_ener = ener;
      // nTree->Fill();
    } else isLeaking = true;

    // Backward
  } else if (z < -full_z && dir.z() < 0.0) {
    isLeaking = true;
    if(pd == neutron) {
      ++n_neu_back;
      en_backleak_neut = e;
      H1_Eneutron->Fill(e);
      // neutron_theta = momentum.theta();
      // neutron_ener = ener;
      // nTree->Fill();
    } else isLeaking = true;

    // Side
  } else if (std::abs(z) <= full_z &&posrad > full_r  && x*dir.x() + y*dir.y() > 0.0) {
    isLeaking = true;
    if(pd == neutron) {
      ++n_neu_leak;
      en_sideleak_neut = e;
      H1_Eneutron->Fill(e);
      // neutron_theta = momentum.theta();
      // neutron_ener = ener;
      // nTree->Fill();
    } else isLeaking = true;
  }

  // protons and pions
  if(isLeaking) {
    if(pd == G4Proton::Proton()) {
      en_leak_prot = e;
      ++n_prot_leak;
    } else if (pd == G4PionPlus::PionPlus() || pd == G4PionMinus::PionMinus()) {
      en_leak_chargpion = e;
      ++n_pion_leak;
    }
    for (int k=0; k<nh; k++) {
      if (part_id == pdg_id_rec[k]) tTree->Fill();
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::SetVerbose(G4int val)        
{
  verbose = val; 
  //  histo->setVerbose(val);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::SetTargetMaterial(const G4Material* mat)         
{
  if(mat) {
    material = mat;
    elm = (*(material->GetElementVector()))[0];
  }
}

void HistoManager::SetWindowMaterial(const G4Material* mat)         
{
  if(mat) {
    windmaterial = mat;
    windelm = (*(windmaterial->GetElementVector()))[0];
  }
}
void HistoManager::SetFileName(const char* val2)        
{
  sprintf(defaultname,"%s",val2); 
  G4int startSeed = CLHEP::HepRandom::getTheSeed(); 
  sprintf(defaultname,"%s_%i.root",defaultname,startSeed);
  strcpy(fOutName, defaultname);
  printf("output file set as %s\n", fOutName);
  fOutfile = new TFile(fOutName, "RECREATE");

  
}

void HistoManager::SetInChainName(const char* val2)
{
  sprintf(fInChainName,"%s",val2);
  printf("Input Chain set to %s\n", fInChainName);
}
void HistoManager::SetInFileName(const char* val2)        
{
  sprintf(defaultname,"%s",val2); 
  strcpy(fInName, defaultname);
  TString comp(val2);
  printf("Input file set as %s\n", fInName);
  if (comp.CompareTo("none") !=0) {
    SetInputFlag();
    input_source_chain.SetName(fInChainName);
    input_source_chain.Add(fInName);
    input_source_chain.SetBranchAddress("in_px",&in_px);
    input_source_chain.SetBranchAddress("in_py",&in_py);
    input_source_chain.SetBranchAddress("in_pz",&in_pz);
    input_source_chain.SetBranchAddress("in_vx",&in_vx);
    input_source_chain.SetBranchAddress("in_vy",&in_vy);
    input_source_chain.SetBranchAddress("in_vz",&in_vz);
    input_source_chain.SetBranchAddress("in_pdg",&in_pdg);
    
  }
  
}

void HistoManager::ReadInFileName()
{
  input_source_chain.GetEntry(atentry);
  //  G4cout << "at entry=" << atentry << " in_px=" << in_px << " in_py=" << in_py << " in_pz=" << in_pz << G4endl;

  //  in_pz = 8000;
  //  G4cout << " in_px=" << in_px << " in_py=" << in_py << " in_pz=" << in_pz << G4endl;

  atentry++;

}

G4double HistoManager::GetInDirectionX()
{
  double dx;
  double mom = pow((pow(in_px,2)+pow(in_py,2)+pow(in_pz,2)),0.5);
  if (mom>0) {
    dx = in_px/mom;
    
  }
  else {
    dx = 0;
  }
  return dx;
}

G4double HistoManager::GetInDirectionY()
{
  double dy;
  double mom = pow((pow(in_px,2)+pow(in_py,2)+pow(in_pz,2)),0.5);
  if (mom>0) {
    dy = in_py/mom;
    
  }
  else {
    dy = 0;
  }
  return dy;
}

G4double HistoManager::GetInDirectionZ()
{
  double dz;
  double mom = pow((pow(in_px,2)+pow(in_py,2)+pow(in_pz,2)),0.5);
  if (mom>0) {
    dz = in_pz/mom;
    
  }
  else {
    dz = 0;
  }
  return dz;
}


G4double HistoManager::GetInMomentum()
{
  G4ThreeVector pmom(in_px*CLHEP::MeV, in_py*CLHEP::MeV, in_pz*CLHEP::MeV);
  G4double mom = pmom.mag();
  // double mom = pow((pow(in_px,2)+pow(in_py,2)+pow(in_pz,2)),0.5);
  //  G4cout << "Momentum =" << mom << " in_px=" << in_px << " in_py=" << in_py << " in_pz=" << in_pz << G4endl;
  return mom;
} 



void HistoManager::SetPartRec(G4String part_val)
{
  std::istringstream is(part_val);
  is >> nh;
  for (int i=0; i<nh; i++) {
    is >> pdg_id_rec[i];
    G4cout << "Set to record in Full TTree particle id: " << pdg_id_rec[i] << G4endl;
  }


}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....



