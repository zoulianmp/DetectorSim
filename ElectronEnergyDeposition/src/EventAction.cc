#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"

/**
 * Creates an event hook for each event.
 *
 * The default print is set to every 100,000 events along without drawing 
 * and using the default EventActionMessenger.
 */
EventAction::EventAction(RunAction* run)
:fRunAction(run),fDrawFlag("none"),fPrintModulo(100000)
{
 
}
/**
 * Deconstructor by deleting the event messenger
 */
EventAction::~EventAction()
{

}
/**
 * Initilizes the energy deposition of the event and prints the event
 * if the event is the modulus of the fPrintModulo
 *
 * @param evt - the event
 */
void EventAction::BeginOfEventAction(const G4Event*){

 //additional initializations            
 fTotalEnergyDeposit = 0.;
}
/**
 * Fills the energy deposition at the end of the event. The histogram is filled
 * using the G4AnalysisManagerInstance, as setup in RunAction.
 *
 * @param evt - the event
 */
void EventAction::EndOfEventAction(const G4Event*)
{
    fRunAction->AddEdep(fTotalEnergyDeposit);
}