#ifndef Materials_h
#define Materials_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

/**
 * Constructor for the Optical Materials
 *
 * The optical materials are implemented as a static class
 */
class Materials{

  public:
    ~Materials();
    static Materials* GetInstance();
    G4Material* GetMaterial(const G4String);

  private:
    // Methods
    Materials();
    void CreateMaterials();
    void SetOpticalPropertiesTeflon();
  void SetOpticalPropertiesPS();
  void SetOpticalPropertiesEJ200();
    void SetOpticalPropertiesGS20();
    void SetOpticalPropertiesBK7();
    void SetOpticalPropertiesSilicone();
    void SetOpticalPropertiesAir();
    void SetOpticalPropertiesPMMA();
    void SetOpticalPropertiesEJ426();

    // Fields
    static Materials* instance;   /* Materials Instance         */
    G4NistManager* nistMan;  /* NIST Material Manager           */
    G4Material* Teflon;      /* Teflon Tape                     */
    G4Material* GS20;        /* GS20 Detector                   */
    G4Material* BK7;         /* PMT Window Glass (Boroscilate)  */
    G4Material* Silicone;    /* Optical Grease                  */
    G4Material* Air;         /* Air                             */
    G4Material* PMMA;        /* PMMA (Plexiglass)               */
    G4Material* EJ426;       /* EJ426 (LiF:ZnS(Ag))             */
		G4Material* EJ200;			 /* EJ200 (PVT Scintillator)				*/
		G4Material* psDet;			 /* Polystyrene based detector 		  */
};

#endif
