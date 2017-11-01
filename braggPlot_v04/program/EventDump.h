// braggPlot04
/* EventDump class definition.
    Class for dumping events' data.
    This class is also an active observer for Events.
*/

#ifndef EVENTDUMP_H
#define EVENTDUMP_H

#include "AnalysisSteering.h"   // Inherits from AnalysisSteering
#include "inc/ActiveObserver.h" // Inherits from ActiveObserver template

class Event;                    // Event& used as argument
class AnalysisInfo;             // pointer used

class EventDump: public AnalysisSteering,
                 public ActiveObserver<Event>
{
    public:
        // Constructor that takes infos as argument
        EventDump(const AnalysisInfo* a_info);
        // Implemented (ex-virtual) destructor
        ~EventDump();

        // Implemented (ex-virtual) function to be called at execution start
        void beginJob();
        // Implemented (ex-virtual) function to be called at execution end
        void endJob();

        // Implemented (ex-abstract) observer method that dumps event's data
        void update( const Event& a_ev );

    private:
        // Prevent shallow copy/assignment
        EventDump           ( const EventDump& x );
        EventDump& operator=( const EventDump& x );
};

#endif // EVENTDUMP_H

