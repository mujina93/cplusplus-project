// braggPlot03
/* EventSource abstract class definition.
    Interface class, blueprint for event getter classes.
*/

#ifndef EVENTSOURCE_H
#define EVENTSOURCE_H

class Event;


class EventSource
{
    public:
        // Constructor & destructor
        EventSource(){}
        virtual ~EventSource(){}

        // Abstract method for getting events
        virtual const Event* GetEventPtr() = 0;

    private:
        // Private copy constructor and operator =, prevent shallow copy
        EventSource(const EventSource& x);
        EventSource& operator=(const EventSource& x);
};

#endif // EVENTSOURCE_H

