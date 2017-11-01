// braggPlot04

#ifndef EVENTSIM_H
#define EVENTSIM_H

#include "EventSource.h"    // inherits from

class Event;        // pointer used


class EventSim: public EventSource
{
    public:

        // Simulates n events with random seed s
        EventSim( unsigned int a_n, unsigned int a_seed );
        virtual ~EventSim();

    private:

        // Id for the event
        int m_evId;

        // Maximum number of events that can be simulated
        int m_nMax;

        // Implemented (ex-virtual) getter
        const Event* GetEventPtr();

        // Method that generates a random event
        const Event* generate();

        // Prevents shallow copy and assignment
        EventSim           ( const EventSim& x );
        EventSim& operator=( const EventSim& x );
};

#endif // EVENTSIM_H

