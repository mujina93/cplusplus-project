// braggPlot02
/* SourceFactory class implementation. This class is a factory.
    It understands what to create from the AnalysisInfo given as input.
    It can create a source for the events to read:
    an EventReadFromFile object (-> read events from the txt file)
    or an EventSim object (-> simulate events).
*/

#include "SourceFactory.h"      // SourceFactory implementation
#include "AnalysisInfo.h"       // AnalysisInfo methods used
#include "EventReadFromFile.h"  // EventReadFromFile object created
#include "EventSim.h"           // EventSim object created

#include <sstream>      // stringstream used

class EventSource;      // pointer to base class EventSource used


// Constructor
SourceFactory::SourceFactory()
{}

// Destructor
SourceFactory::~SourceFactory()
{}

// Creates event source
EventSource* SourceFactory::create( const AnalysisInfo* a_info )
{
    using std::stringstream;

    // If "input" was typed, creates an EventReadFromFile as source for the events
    // (the program will read events from the given input file)
    if ( a_info->contains( "input" ) )
    {
        return new EventReadFromFile( a_info->value( "input" ) );
    } // end if-input


    // If "sim" was typed in execution line instead, use an EventSim as source
    // for the events. The input events will come from a pseudo-random simulation.
    if ( a_info->contains( "sim"   ) )
    {
        stringstream sstr;
        // Get number of events to generate
        // (the number in input that follows 'sim' is the maximum number of events to generate)
        sstr.str( a_info->value( "sim" ) );
        unsigned int nevt;
        sstr >> nevt;

        // Set seed if available
        // (the number in input that follows 'seed', if any, is the seed number)
        unsigned int seed = 1;
        if ( a_info->contains( "seed" ) )
        {
            sstr.clear();
            sstr.str( a_info->value( "seed" ) );
            sstr >> seed;
        }

        // Creates and return an EventSim, with all the
        // options given in input.
        return new EventSim( nevt, seed );
    } // end if-sim

    return 0;
}

