// braggPlot05
/* EventSource abstract class implementation.
    Interface class, blueprint for event getter classes.
*/

#include "EventSource.h"    // implementation of
#include "inc/Dispatcher.h" // Events used as Dispatchers to send notifications
#include "Event.h"          // Event destructor invoked via pointer

// Constructor
EventSource::EventSource()
{}

// Virtual destructor
EventSource::~EventSource()
{}

// Run method that loops over events.
// The events notify the observers.
void EventSource::Run()
{
    // Reads file or simulation, updates sums and sqSums with events that have tot energy in
	// each of the 4 different ranges, and eventually dumps data
	const Event* p_ev;
    while ( (p_ev = GetEventPtr()) ) // reads and stores an event, until EOF
    {
        // Make the event notify all its observers.
        // The observers will know what to do with the information provided.
        // The observers will use their update() method
        Dispatcher<Event>::notify(*p_ev);

        // Deallocates dynamic object before p_ev points to another object
        delete p_ev;
    }
}
