
#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


class G4Track;
class G4Step;
class G4ParticleDefinition;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class HistoMessenger2;
class PrimaryGeneratorAction;

class HistoManager
{
public:

  static HistoManager* GetPointer();

private:

  HistoManager();
 

public: 

  ~HistoManager();

  void bookHisto();

  void BeginOfRun();
  void EndOfRun();
  void BeginOfEvent();
  void EndOfEvent();
  // void Fill(G4int id, G4double x, G4double w);

  void ScoreNewTrack(const G4Track*);
  void AddTargetStep(const G4Step*);
  void AddWindowStep(const G4Step*);
  void AddLeakingParticle(const G4Track*);

  void SetTargetLength(G4double val)            {length  = val;};
  void SetBeamSize(G4double val)                {beamsize  = val;};
  void SetBeamType(G4int val)                   {beamtype  = val;};
  void SetWindowThick_r(G4double val)           {thick_r  = val;};
  void SetWindowThick_z(G4double val)           {thick_z  = val;};
  void SetNumberOfSlices(G4int val)             {nSlices = val;};
  void SetNumberOfBinsE(G4int val)              {nBinsE  = val;};

  G4double Length()         const               {return length;};
  G4double BeamSize()         const             {return beamsize;};
  G4int    BeamType()         const             {return beamtype;};
  G4double Thick_r()         const              {return thick_r;};
  G4double Thick_z()         const              {return thick_z;};
  G4int    NumberOfSlices() const               {return nSlices;};

  void SetVerbose(G4int val);        
  G4int GetVerbose() const                      {return verbose;};

  void SetDefaultBeamPositionFlag(G4bool f)     {beamFlag = f;};        
  G4bool DefaultBeamPosition() const            {return beamFlag;};

  void SetTargetMaterial(const G4Material* mat);
  const G4Material* TargetMaterial() const      {return material;};
  void SetWindowMaterial(const G4Material* mat);
  const G4Material* WindowMaterial() const      {return windmaterial;};
  const G4Element* TargetElement() const        {return elm;};

  G4double CurrentKinEnergy()                   {return currentKinEnergy;};
  const G4ParticleDefinition* CurrentParticle() {return currentDef;};

  void SetMaxEnergyDeposit(G4double val)        {edepMax = val;};
  void SetFileName(const char* val2) ; 
  void SetInFileName(const char* val2) ; 
  G4bool DefaultInFile() const            {return InputFlag;};
  void ReadInFileName() ; 
  void SetInChainName(const char* val2); 
  void SetPartRec(G4String part_val);

  G4double GetInDirectionX();
  G4double GetInDirectionY();
  G4double GetInDirectionZ();
  G4double GetInVertexX() {return in_vx;};
  G4double GetInVertexY() {return in_vy;};
  G4double GetInVertexZ() {return in_vz;};
  G4int GetPDGEncoding() {return in_pdg;};
  G4double GetInMomentum();
  void SetInputFlag()        {InputFlag = true;};

private:

  static HistoManager* fManager;

  TFile *fOutfile;
  char fOutName[255];
  char defaultname[255];
  char fInName[255];
  G4bool InputFlag;
  char fInChainName[255];
  int atentry;
  G4int nh, pdg_id_rec[100];
  TTree *fTree; 
  // TTree *nTree;
  TTree *tTree;
  TChain input_source_chain;

  double in_px;
  double in_py;
  double in_pz;
  double in_vx;
  double in_vy;
  double in_vz;
  int in_pdg;
  
  PrimaryGeneratorAction* primGenAction;
  const G4ParticleDefinition* primaryDef;
  const G4ParticleDefinition* currentDef;
  const G4ParticleDefinition* neutron;
  const G4Material*           material;
  const G4Material*           windmaterial;
  const G4Element*                  elm;
  const G4Element*                  windelm;

  G4double edepMax;
  G4double edepEvt;
  G4double edepEM;
  G4double edepPI;
  G4double edepP;
  G4double edepSum;
  G4double edepSum2;
  G4double beamEnergy;
  G4double length;
  G4double beamsize;
  G4double radius;
  G4double thick_r;
  G4double thick_z;
  G4double absZ0;
  G4double full_r;
  G4double full_z;
  G4double primaryKineticEnergy;
  G4double currentKinEnergy;
 
  G4int verbose;
  G4int nBinsE;
  G4int nSlices;

  G4int beamtype;
  G4int n_evt;
  G4int n_elec;
  G4int n_posit;
  G4int n_gam;
  G4int n_prot_leak;
  G4int n_pion_leak;
  G4int n_cpions;
  G4int n_pi0;
  G4int n_kaons;
  G4int n_muons;
  G4int n_ions;
  G4int n_deut;
  G4int n_alpha;
  G4int n_neutron;
  G4int n_proton;
  G4int n_aproton;
  G4int n_neu_forw;
  G4int n_neu_leak;
  G4int n_neu_back;
  G4int n_step;
  G4int nHisto;

  G4bool beamFlag;


  int event_n; // number of events
  int track_id; // primary, secondary, etc.
  int part_id;
  double enedep_tg;
  double zdep_tg;
  double ener ;
  double ener_vert;
  double theta;
  double mom_x;
  double mom_y;
  double mom_z;
  double vert_x;
  double vert_y;
  double vert_z;
  double leak_x;
  double leak_y;
  double leak_z;
  double mass;
  double neutron_ener;
  double neutron_theta;
  double en_sideleak_neut; //16
  double en_forwleak_neut; //17
  double en_backleak_neut; //18
  double en_leak_prot; //19
  double en_leak_chargpion; //20
  double en_deptg_beam; //23
  double en_EMdeptg_beam; //24
  double en_pideptg_beam; //25
  double en_protdeptg_beam; //26
  double en_depwd_beam; //27
  double en_EMdepwd_beam; //28
  double en_pidepwd_beam; //29
  double en_protdepwd_beam; //30
  TH1F * H1_Edep;
  TH1F * H1_Egamma;
  TH1F * H1_Eelectron;
  TH1F * H1_Epositron;
  TH1F * H1_Eneutron;
  TH1F * H1_Eproton;
  TH1F * H1_Eantiproton;
  TH1F * H1_Epiplus;
  TH1F * H1_Epiminus;
  TH1F * H1_Epi0;
  TH1F * H1_Ekaons;
  TH1F * H1_Emuons;
  TH1F * H1_Edeuterons;
  TH1F * H1_Etriton;
  TH1F * H1_EHe3;
  TH1F * H1_Ealpha;
  TH1F * H1_Efwdneutron;
  TH1F * H1_Ebwdneutron;

  // This part from HistoMessenger2.hh

  HistoMessenger2* histoMessenger2;
  G4UIcmdWithAString*     particleCmd;
  G4UIcmdWithAString*     fileCmd;
  G4UIcmdWithAString*     infileCmd;
  G4UIcmdWithAString*     inchainCmd;

 
};

#endif
