#include "Analysis.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4ParticleDefinition.hh"

#include "HistoManager.hh"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

#include "G4Event.hh"
#include "G4ThreeVector.hh"

#include "PhotonHit.hh"

#include "HistoManager.hh"
Analysis* Analysis::singleton = 0;

/**
 * Analysis
 *
 * Creates an Analysis object 
 */
Analysis::Analysis(){
}
/**
 * Initilize the analysis manager
 *
 * Creates a new HistoManager
 */
void Analysis::Initilize(){
  fHistoManager = new HistoManager();
}
/**
 * Cleaning up the analysis manager
 *
 * Deleting the HistoManager
 */
void Analysis::CleanUp(){
   delete fHistoManager;
}
Analysis::~Analysis(){
}

/**
 * PrepareNewRun
 *
 * @brief - called before each run.
 * There is no need to update the geometry because the geometry
 * is fixed during a run.
 */
void Analysis::PrepareNewRun(const G4Run* aRun){
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }   
}

/**
 * PrepareNewEvent
 *
 * @brief - Called before each event. Sets the energy deposited per event to be
 * zero, as well as the number of optical photons that are created and detected
 */
void Analysis::PrepareNewEvent(const G4Event*){
  eDepEvent = 0.0;
  nOPAbsEvent = 0;
  nOPPMTEvent = 0;
}


/**
 * EndOfEvent
 *
 * @param G4Event* event
 */
void Analysis::EndOfEvent(const G4Event* event){

  /**
   * Getting the hit collections. 
   * The PMT SD has a single hit collection associated with it, while the
   * absorber SD has two hit collections assciated with it.
   */
  G4SDManager* fSDM = G4SDManager::GetSDMpointer();
  G4int pmtHCID = fSDM->GetCollectionID("DetectorSD");
  G4HCofThisEvent* HCofEvent = event->GetHCofThisEvent();
 
  PhotonHitsCollection* pmtHC = (PhotonHitsCollection*) (HCofEvent->GetHC(pmtHCID));

  // The Number of Optical Photons Detected on the PMT
  if(pmtHC != NULL)
    nOPPMTEvent += pmtHC->GetSize();
  else
    G4cout<<"WARNING: Absorber::EndOfEvent - pmtHC is NULL"<<G4endl;
  
  // Filling the histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if (eDepEvent > 0.0){
    analysisManager->FillH1(1,nOPAbsEvent);
    analysisManager->FillH1(2,nOPPMTEvent);
  }
}

/**
 * EndOfRun
 *
 * Called at the end of a run, which summerizes the run
 */
void Analysis::EndOfRun(const G4Run* ){
  // Print out some run statistics
  
  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }    
}
/**
 * Sets the number of optical photons generated
 */
void Analysis::SetNumOpticalPhotonsGenerated(G4int numPhotons){
  nOPAbsEvent = numPhotons;
}

