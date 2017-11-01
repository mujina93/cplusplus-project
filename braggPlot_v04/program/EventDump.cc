// braggPlot04
/* EventDump class implementation. Inherits from AnalysisSteering
    Class for dumping events' data.

    This file contains also the definiton and the implementation
    for the EventDumpBuilder class. This is a concrete class that
    inherits from and implements the abstract nested
    AnalysisFactory::Builder class.
    The class EventDumpBuilder is responsible for actually building
    an EventDump object, and for registering its creation to the
    AnalysisFactory (factory that creates all the analyzers with the
    call to the static method create()).
*/

#include "EventDump.h"  // Implementaion of EventDump
#include "Event.h"      // Event class used
#include <iostream>     // std::cout, std::endl used
#include "AnalysisSteering.h" // constructor called
#include "AnalysisFactory.h"  // concrete implementation of nested Builder class

class AnalysisInfo;     // pointer used

using std::cout;
using std::endl;

// Intermediate builder class to create an EventDump analyzer
// This class implements the abstract nested Builder class
// that is defined inside AnalysisFactory
class EventDumpBuilder: public AnalysisFactory::Builder
{
    public:
        // Creates the builder object, assign "dump" as
        // name for this analyzer and builder
        EventDumpBuilder():
            AnalysisFactory::Builder( "dump" )
        {}

        // The AnalysisFactory will make the builder use
        // this method when it wants an EventDump to be created.
        virtual AnalysisSteering* build( const AnalysisInfo* a_info )
        {
            // Dynamically creates an EventDump object, if the infos require it
            return new EventDump( a_info );
        }
};

// Create a global EventDumpBuilder, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpBuilder will be available with name "dump".
static EventDumpBuilder EvDuBuilder;


// Constructor (it calls the base constructor with the info parameters)
EventDump::EventDump(const AnalysisInfo* a_info):
    AnalysisSteering( a_info )
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

// Observer update method:
// Function that prints data on the screen for the given event
void EventDump::update( const Event& a_ev )
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
