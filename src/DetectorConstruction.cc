
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "TargetSD.hh"
#include "CheckVolumeSD.hh"
#include "WindowSD.hh"
#include "G4SDManager.hh"
#include "HistoManager.hh"
#include "G4NistManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
  logicTarget = 0;
  logicCheck  = 0;
  logicWorld  = 0;
  logicWindow = 0;
  detectorMessenger = new DetectorMessenger(this);

  radius = 10.*CLHEP::cm;

  targetMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
  windowMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  // Prepare sensitive detectors
  checkSD = new CheckVolumeSD("checkSD");
  (G4SDManager::GetSDMpointer())->AddNewDetector( checkSD );
  targetSD = new TargetSD("targetSD");
  (G4SDManager::GetSDMpointer())->AddNewDetector( targetSD );
  windowSD = new WindowSD("windowSD");
  (G4SDManager::GetSDMpointer())->AddNewDetector( windowSD ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ 
  delete detectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Cleanup old geometry

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Sizes
  G4double thickwindow_r = HistoManager::GetPointer()->Thick_r();
  G4double thickwindow_z = HistoManager::GetPointer()->Thick_z();
  G4double checkR  = thickwindow_r + CLHEP::mm;
  G4double worldR  = thickwindow_r + CLHEP::cm;
  G4double targetZ = HistoManager::GetPointer()->Length()*0.5; 
  G4double checkZ  = thickwindow_z + CLHEP::mm;
  G4double worldZ  = thickwindow_z + CLHEP::cm;
  G4double windowZ  = thickwindow_z;
  G4double windowR  = thickwindow_r;

  G4int vol_type = HistoManager::GetPointer()->VolumeType();

  G4cout << "worldZ=" << worldZ << " checkZ=" << checkZ << " windowZ=" <<windowZ << " targetZ=" << targetZ << G4endl;;

  G4int nSlices    = HistoManager::GetPointer()->NumberOfSlices();
  G4double sliceZ  = targetZ/G4double(nSlices);
  if (vol_type == 1) {
    sliceZ = targetlz/ G4double(nSlices);
  }

  //
  // World
  //

  if (vol_type ==2 ) {
    G4Tubs* solidW = new G4Tubs("World",0.,worldR,worldZ,0.,CLHEP::twopi);
    logicWorld = new G4LogicalVolume( solidW,worldMaterial,"World");
  }
  else {
    G4Box* solidW = new G4Box("World",windowlx+CLHEP::cm,windowly+CLHEP::cm,windowlz+CLHEP::cm);
    logicWorld = new G4LogicalVolume( solidW,worldMaterial,"World");
  }
  G4VPhysicalVolume* world = new G4PVPlacement(0,G4ThreeVector(),
                                       logicWorld,"World",0,false,0);
  //
  // Check volume
  //

  if (vol_type ==2 ) {
    G4Tubs* solidC = new G4Tubs("Check",0.,checkR,checkZ,0.,CLHEP::twopi);
    logicCheck = new G4LogicalVolume( solidC,worldMaterial,"World");
  }
  else {
    G4Box* solidC = new G4Box("Check",windowlx+CLHEP::mm,windowly+CLHEP::mm,windowlz+CLHEP::mm);
    logicCheck = new G4LogicalVolume( solidC,worldMaterial,"World");
  }

  //  G4VPhysicalVolume* physC = 
  new G4PVPlacement(0,G4ThreeVector(),logicCheck,"World",logicWorld,false,0);
  logicCheck->SetSensitiveDetector(checkSD);

 //
  // Window volume
  //
  if (vol_type ==2 ) { 
    G4Tubs* solidWindow = new G4Tubs("Window",0.,windowR,windowZ,0.,CLHEP::twopi);
    logicWindow = new G4LogicalVolume( solidWindow,windowMaterial,"Window");
  }
  else { 
    G4Box* solidWindow = new G4Box("Window",windowlx,windowly,windowlz);
    logicWindow = new G4LogicalVolume( solidWindow,windowMaterial,"Window");
  }
  new G4PVPlacement(0,G4ThreeVector(),logicWindow,"Window",logicCheck,false,0);
  logicWindow->SetSensitiveDetector(windowSD);

  //
  // Target volume
  //
  if (vol_type ==2 ) { 
    G4Tubs* solidA = new G4Tubs("Target",0.,radius,targetZ,0.,CLHEP::twopi);
    logicTarget = new G4LogicalVolume( solidA,targetMaterial,"Target");
  }
  else { 
    G4Box* solidA = new G4Box("Target",targetlx,targetly,targetlz);
    logicTarget = new G4LogicalVolume( solidA,targetMaterial,"Target");
  }
  logicTarget->SetSensitiveDetector(targetSD);

  G4double z = sliceZ - targetZ;
  new G4PVPlacement(0,G4ThreeVector(),logicTarget,"Target",logicWindow,false,0);
  // for(G4int i=0; i<nSlices; i++) {
  //   // physC = 
  //   new G4PVPlacement(0,G4ThreeVector(0.0,0.0,z),logicTarget,"Target",logicWindow,false,i);
  //   z += 2.0*sliceZ;
  // }
  if (vol_type ==1) {
    G4cout << "window x= "<< windowlx/CLHEP::cm  << "cm" << G4endl;
    G4cout << "window y= "<< windowly/CLHEP::cm  << "cm" << G4endl;
    G4cout << "window z= "<< windowlz/CLHEP::cm  << "cm" << G4endl;
    G4cout << "target x= "<< targetlx/CLHEP::cm  << "cm" << G4endl;
    G4cout << "target y= "<< targetly/CLHEP::cm  << "cm" << G4endl;
    G4cout << "target z= "<< targetlz/CLHEP::cm  << "cm" << G4endl;
  }
      
  G4cout << "### Target consist of " << nSlices
         << " of " << targetMaterial->GetName() 
         << " disks with R(mm)= " << radius/CLHEP::mm
         << "  Width(mm)= " << 2.0*sliceZ/CLHEP::mm
         << "  Total Length(mm)= " << 2.0*targetZ/CLHEP::mm
         <<  "  ###" << G4endl;

  G4VisAttributes zero = G4VisAttributes::Invisible;
  logicWorld->SetVisAttributes(&zero);

  //  logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4VisAttributes regWcolor(G4Colour(0.3, 0.3, 0.3));
  logicCheck->SetVisAttributes(&regWcolor);

  G4VisAttributes regCcolor(G4Colour(0., 0.3, 0.7));
  logicTarget->SetVisAttributes(&regCcolor);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  return world;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetMaterial(const G4String& mat)
{
  G4double aa;
  G4int zz;
  G4int nn;
  G4int natoms;
  G4String name,symbol;
  G4double abundance;
  G4double density;
  G4double temp = 22.0*CLHEP::kelvin;
  G4double templh2 = 20.27*CLHEP::kelvin;
  // G4double press = 2.116*atmosphere;
  G4int nComponents;
  G4int nIso;
  D  = new G4Isotope("Deuteron", zz=1, nn=2, aa= 2.0141018*CLHEP::g/CLHEP::mole);
  elD = new G4Element("Deuterium",symbol="elD", nIso = 1);
  elD->AddIsotope(D, abundance=100.*CLHEP::perCent);
  LD2 = new G4Material("LiquidDeuterium", density= 0.169*CLHEP::g/CLHEP::cm3, nComponents=1, kStateLiquid, temp);
  //LD2 = new G4Material("LiquidDeuterium", zz=1, aa=2.0141018*g/mole, density= 0.169*g/cm3, kStateLiquid, temp);
  // LD2->AddElement(elD, fractionmass=100.0*perCent); //sum of frac. masses 2 is not 1?
  // LD2->AddElement(elD, fractionmass=100.0*perCent);

  LD2->AddElement(elD, natoms=2); //sum of frac. masses 2 is not 1?
  // LD2->AddElement(elD, natoms=1);

  //Constriction of LH2 cell
  elH  = new G4Element("Hydrogen",symbol="elH",  zz= 1, aa= 1.00794*CLHEP::g/CLHEP::mole);
  LH2 = new G4Material("H2Liquid",density= 0.0708*CLHEP::g/CLHEP::cm3 , nComponents=1,kStateLiquid, templh2 );
  LH2->AddElement(elH, natoms = 2);
  LH2fake = new G4Material("H2LiquidFake",density= 0.169*CLHEP::g/CLHEP::cm3 , nComponents=1,kStateLiquid, templh2 );
  LH2fake->AddElement(elH, natoms = 2);

  // Constructing He3 cell for SIDIS
 
  G4Element* He3 = new G4Element("Helium3",  "He3", zz=2,  aa=3.0160293*CLHEP::g/CLHEP::mole);
	


  G4Material* He3_10amg = new G4Material( "He3_10amg",  density = 10.*0.1345*CLHEP::mg/CLHEP::cm3, nComponents=1 );
  //0.1345=44.6(amg=mol/m3)*3.016(g/mol)
  He3_10amg->AddElement( He3, 100.0*CLHEP::perCent );
  
  elHe =  new G4Element("Helium",    "He", zz=2,  aa=4.0026*CLHEP::g/CLHEP::mole);
  LHe4 =  new G4Material( "LHe4",  density = 0.145*CLHEP::g/CLHEP::cm3,nComponents=1, kStateLiquid, temp);
  LHe4->AddElement( elHe, 100.0*CLHEP::perCent );


  // search the material by its name
  G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);
  HistoManager::GetPointer()->SetTargetMaterial(material);
  if (material && material != targetMaterial) {
    HistoManager::GetPointer()->SetTargetMaterial(material);
    targetMaterial = material;
    if(logicTarget) logicTarget->SetMaterial(targetMaterial);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetWorldMaterial(const G4String& mat)
{
  // search the material by its name
  G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);

  if (material && material != worldMaterial) {
    worldMaterial = material;
    if(logicWorld) logicWorld->SetMaterial(worldMaterial);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}

void DetectorConstruction::SetWindowMaterial(const G4String& mat)
{
  G4double aa;
  G4int zz;
  G4cout << "Setting window material to " << mat.data() << G4endl;
  G4double density;
  G4String name,symbol;
  G4double fractionmass;

  G4int nComponents;
  
  G4NistManager* matman = G4NistManager::Instance();
 //He3 cell glass
  G4Element* Ba  = new G4Element("Barium",    "Ba", zz=56, aa=  137.327*CLHEP::g/CLHEP::mole);
  G4Element* O   = new G4Element("Oxygen",    "O",  zz=8,  aa=    16.00*CLHEP::g/CLHEP::mole);
  G4Element* Sr  = new G4Element("Strontium", "Sr", zz=38, aa=    87.62*CLHEP::g/CLHEP::mole);
  
  G4Material *BariumOxide = new G4Material("BariumOxide", density=5.72*CLHEP::g/CLHEP::cm3, nComponents=2);
  BariumOxide->AddElement(Ba, 1);
  BariumOxide->AddElement(O,  1);
  
  G4Material *StrontiumOxide = new G4Material("StrontiumOxide", density=4.7*CLHEP::g/CLHEP::cm3, nComponents=2);
  StrontiumOxide->AddElement(Sr, 1);
  StrontiumOxide->AddElement(O,  1);
  
  G4Material *AluminiumOxide =  matman->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");  // Al2O3	3.97g/cm3
  G4Material *CalciumOxide =  matman->FindOrBuildMaterial("G4_CALCIUM_OXIDE");  // CaO	3.3g/cm3
  G4Material* SilicOxide  = matman->FindOrBuildMaterial("G4_SILICON_DIOXIDE");  // SiO2	2.32g/cm3

  
  G4Material *Glass_GE180 = new G4Material("Glass_GE180", density=2.76*CLHEP::g/CLHEP::cm3, nComponents=5);
  Glass_GE180->AddMaterial(SilicOxide, 60.8*CLHEP::perCent);   //add 0.5 to make total as 1
  Glass_GE180->AddMaterial(BariumOxide, 18.2*CLHEP::perCent);
  Glass_GE180->AddMaterial(AluminiumOxide, 14.3*CLHEP::perCent);
  Glass_GE180->AddMaterial(CalciumOxide, 6.5*CLHEP::perCent);
  Glass_GE180->AddMaterial(StrontiumOxide, 0.25*CLHEP::perCent);

  elC = new G4Element(name="Carbon",symbol="C",zz=6.,aa=12.01*CLHEP::g/CLHEP::mole);
  elO = new G4Element(name="Oxygen",symbol="O2",zz=8.,aa=16.*CLHEP::g/CLHEP::mole);
  elNa = new G4Element(name="Sodium",symbol="Na",zz=11.,aa=22.99*CLHEP::g/CLHEP::mole);
  elMg = new G4Element(name="Magnesium",symbol="Mg",zz=12.,aa=24.305*CLHEP::g/CLHEP::mole);
  elAl = new G4Element(name="Aluminum",symbol="Al",zz=13.,aa=26.98*CLHEP::g/CLHEP::mole);
  elSi = new G4Element(name="Silicon",symbol="Si",zz=14.,aa=28.085*CLHEP::g/CLHEP::mole);
  elK = new G4Element(name="Potassium",symbol="K",zz=19.,aa=39.0983*CLHEP::g/CLHEP::mole);
  elCa = new G4Element(name="Calcium",symbol="Ca",zz=20.,aa=40.08*CLHEP::g/CLHEP::mole);
  elFe = new G4Element(name="Iron",symbol="Fe",zz=26.,aa=55.850*CLHEP::g/CLHEP::mole);

  Portland = new G4Material("Portland",density = 2.3*CLHEP::g/CLHEP::cm3,nComponents=10 );
  Portland->AddElement(elH,fractionmass=0.01);
  Portland->AddElement(elC,fractionmass=0.001);
  Portland->AddElement(elO,fractionmass=0.529107);
  Portland->AddElement(elNa,fractionmass=0.016);
  Portland->AddElement(elMg,fractionmass=0.002);
  Portland->AddElement(elAl,fractionmass=0.033872);
  Portland->AddElement(elSi,fractionmass=0.337021);
  Portland->AddElement(elK,fractionmass=0.013);
  Portland->AddElement(elCa,fractionmass=0.044);
  Portland->AddElement(elFe,fractionmass=0.014);

  // search the material by its name
  G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);

  if (material && material != windowMaterial) {
    HistoManager::GetPointer()->SetWindowMaterial(material);
    windowMaterial = material;
    if(logicWindow) logicWindow->SetMaterial(windowMaterial);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetRadius(G4double val)  
{
  if(val > 0.0) {
    radius = val;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}
void DetectorConstruction::SetTargetLx(G4double val)  
{
  if(val > 0.0) {
    targetlx = val/2;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}
void DetectorConstruction::SetTargetLy(G4double val)  
{
  if(val > 0.0) {
    targetly = val/2;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}
void DetectorConstruction::SetTargetLz(G4double val)  
{
  if(val > 0.0) {
    targetlz = val/2;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}
void DetectorConstruction::SetWindowLx(G4double val)  
{
  if(val > 0.0) {
    windowlx = val/2;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}
void DetectorConstruction::SetWindowLy(G4double val)  
{
  if(val > 0.0) {
    windowly = val/2;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}
void DetectorConstruction::SetWindowLz(G4double val)  
{
  if(val > 0.0) {
    windowlz = val/2;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
