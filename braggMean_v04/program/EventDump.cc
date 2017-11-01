// braggMean04
/* EventDump class implementation. Inherits from AnalysisSteering
    Class for dumping events' data.
*/

#include "EventDump.h"  // Implementaion of EventDump
#include "Event.h"      // Event class used
#include <iostream>  // std::cout, std::endl used

using std::cout;
using std::endl;


// Constructor
EventDump::EventDump()
{}

// Destructor
EventDump::~EventDump()
{}

// Execution start method
void EventDump::beginJob()
{
    return;
}

// Execution end method
void EventDump::endJob()
{
    return;
}

// Function that prints data on the screen for the given event
void EventDump::process( const Event& a_ev )
{
    // Prints data event ID and number of measures for that event
    cout << "***** EVENT: " << a_ev.GetEventID() << " *****" << endl;
	int nMeasures = a_ev.GetDataSize();
	cout << "***** number of points: " << nMeasures << " *****" << endl;
	cout << "***** energy values for this event: ";

	// Prints the measures of that event
	for (int i = 0; i < nMeasures; i++)
    {
		cout << a_ev.GetIthEnergy(i) << " | ";
	}
	cout << endl;

	return;
}
