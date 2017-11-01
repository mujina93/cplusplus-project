// braggMean04
/* EventReadFromFile class definition
*/

#ifndef EVENTREADFROMFILE_H
#define EVENTREADFROMFILE_H

#include "EventSource.h"    // Inherits from EventSource class

#include <fstream>  // ifstream used
#include <string>   // string used

class Event;        // Event* used as function parameter

using std::string;
using std::ifstream;

class EventReadFromFile: public EventSource
{
    public:
        // Constructor (input file name as argument)
        EventReadFromFile( const string& a_name );
        // Default constructor (if you forgot the input)
        EventReadFromFile();

        // Implemented (ex-virtual) destructor
        ~EventReadFromFile();
        // Implemented (ex-virtual) method for getting an event
        const Event* GetEventPtr();

    private:
        // Pointer to stream (from which it's taking the input)
        ifstream* m_pFile;

        // Internal method for reading files
        const Event* ReadFile();

        // Prevent shallow copy/assignment
        EventReadFromFile( const EventReadFromFile& x );
        EventReadFromFile& operator=( const EventReadFromFile& x );
};

#endif // EVENTREADFROMFILE_H

