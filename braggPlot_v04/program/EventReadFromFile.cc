// braggPlot04
/* Implementation of EventReadFromFile clss
*/

#include "EventReadFromFile.h" // implementing EventReadFromFile

#include "Event.h"  // Event object created
#include <fstream>  // ifstream used
#include <string>   // string used

using std::string;
using std::ifstream;
using std::ios;

// Constructor that open the file with the given file name
EventReadFromFile::EventReadFromFile( const string& a_name )
{
    m_pFile = new ifstream( a_name.c_str(), ios::in );
}

// Default constructor with default file name, if you forgot the input
EventReadFromFile::EventReadFromFile()
{
    string file_name = "bragg_events.txt";
    m_pFile = new ifstream( file_name.c_str(), ios::in );
}

// Destructor. Closes the file and deallocates the ifstream object.
EventReadFromFile::~EventReadFromFile()
{
    delete m_pFile;
}

// Gets the next event from file (return the pointer to the event)
const Event* EventReadFromFile::GetEventPtr()
{
    return ReadFile();
}

// Reads a bunch of the file and returns an event pointer
const Event* EventReadFromFile::ReadFile()
{
    // Pointer to event
	Event* p_ev;
	// Event ID
	int readID;
	// ifstream reference for the open file
	ifstream& iFile = *m_pFile;

	// Reads and stores the data
	if( iFile >> readID )
    {
        // If it manages to read the ID, it creates a new dynamic empty Event
        p_ev = new Event(readID);
	} else return 0; // if it couldn't read (=END OF FILE), it returns 0 (NULL ptr)

    // Reads the number of measures
    int readN;
	iFile >> readN;

	// Reads and stores the energies
	int en;
	for (int i = 0; i < readN; i++)
    {
		iFile >> en;
		(*p_ev).AddEnergy(en);
	}

    // Returns the pointer to the filled Event
	return p_ev;
}

