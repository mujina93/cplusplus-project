// braggMean01
/* This function reads an event from file, stores event data (ID, number of measures,
                                                              and measures dynamic array)
   in a dynamic Event, and then returns the pointer to that Event.
   If this function fails to read the file, it returns a NULL pointer.
*/

#include<fstream>   // std::ifstream used
#include "Event.h"  // Event struct used

using std::ifstream;

const Event* read(ifstream& a_iFile)
{
    // Pointer to event
	Event* p_ev;
	// Event ID
	int readID;

	// Reads and stores the data
	if( a_iFile >> readID )
    {
        // If it manages to read the ID, it creates a new dynamic Event
        p_ev = new Event;
        // Stores the id
        p_ev->m_evID = readID;
	} else return 0; //if it couldn't read (=END OF FILE), it returns 0 (NULL ptr)

    // Reads and stores the number of measures
    int readN;
	a_iFile >> readN;
	p_ev->m_nMeasures = readN;

	// Allocates a dynamic array for the energies
	p_ev->m_energies = new int[readN];

	// Reads and stores the energies
	for (int i = 0; i < readN; i++)
    {
		a_iFile >> (*p_ev).m_energies[i];
	}

    // Returns the pointer to the filled Event
	return p_ev;
}
