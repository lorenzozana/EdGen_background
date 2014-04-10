
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"

class CheckVolumeSD;
class TargetSD;
class WindowSD;
class G4LogicalVolume;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();
  virtual ~DetectorConstruction();

public:

  G4VPhysicalVolume* Construct();

  void SetWorldMaterial(const G4String&);
  void SetTargetMaterial(const G4String&);
  void SetWindowMaterial(const G4String&);

  void SetTargetRadius(G4double val);

  void UpdateGeometry();

private:

  DetectorConstruction & operator=(const DetectorConstruction &right);
  DetectorConstruction(const DetectorConstruction&);

  G4double radius;

  G4Material*  targetMaterial;
  G4Material*  worldMaterial;
  G4Material*  windowMaterial;

  CheckVolumeSD*   checkSD;
  TargetSD*        targetSD;
  WindowSD*        windowSD;

  G4LogicalVolume* logicTarget;
  G4LogicalVolume* logicCheck;
  G4LogicalVolume* logicWindow;
  G4LogicalVolume* logicWorld;

  DetectorMessenger* detectorMessenger;

  G4Isotope* D;
  G4Element* elD;
  G4Material* LD2;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#endif

