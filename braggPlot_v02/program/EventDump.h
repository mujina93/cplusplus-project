// braggPlot02
/* EventDump class definition.
    Class for dumping events' data.
*/

#ifndef EVENTDUMP_H
#define EVENTDUMP_H

#include "AnalysisSteering.h"   // Inherits from AnalysisSteering

class Event;    // Event& used as argument

class EventDump: public AnalysisSteering
{
    public:
        // Default onstructor
        EventDump();
        // Implemented (ex-virtual) destructor
        ~EventDump();

        // Implemented (ex-virtual) function to be called at execution start
        void beginJob();
        // Implemented (ex-virtual) function to be called at execution end
        void endJob();
        // Implemented (ex-virtual) function that dumps event's data
        void process( const Event& a_ev );

    private:
        // Prevent shallow copy/assignment
        EventDump           ( const EventDump& x );
        EventDump& operator=( const EventDump& x );
};

#endif // EVENTDUMP_H
