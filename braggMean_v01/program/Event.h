// braggMean01
/* Definition of Event struct.
    an Event containts the event ID, the number of measures
    for that event, and the (dynamic) array of the actual measures.
*/

// Include guards
#ifndef Event_h
#define Event_h

struct Event {
  int m_evID; // event ID
  int m_nMeasures; // # of measures
  int* m_energies; // array of doubles (to store energy losses values)
};

#endif
