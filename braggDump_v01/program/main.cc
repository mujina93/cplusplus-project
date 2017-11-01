// braggDumpv01
/*  This program reads the file bragg_events.txt (give it as argument in command line)
    It reads it (the file contains 1000 events, each of them is composed by an event ID,
    a number of measures, and the array of the measures). Each event contains about 125 measures.
    And then it dumps the read data on the screen.
*/

// include directives
#include <cstring>  // strdup is used
#include <fstream>  // std::ifstream is used

// using declarations
using std::ifstream;
using std::ios;

// This function reads an event, stores the measures in the given array,
// and returns the event ID.
int read(ifstream& a_iFile, int*const a_energies);

// This function prints on the screen the data of the given event
// It takes as input the event ID, the number of measures of that event,
// and the array of measures for that event
void dump(const int a_evID, const int a_nMeasures, const int*const a_energies);


int main(int argc, char* argv[])
{
    // File name
    char* file_name = argv[1];
    if (file_name == NULL)
    {
        file_name = strdup("bragg_events.txt"); // default name, if you forgot
    }
    // Open file
	ifstream iFile;
	iFile.open(file_name, ios::in);

	// Variables
	int evID; // ID of the event
	int* energies = new int[130]; // Array for the energies - no event has more than 130 measures
    int nMeasures; // # of measures in the event.

    // Read file and dump data
	while (iFile >> evID)         // reads the event ID (first number of the line)
    {
        // reads the number of measures for this event
        // returns the number of measures, and fill the 'energies' array with the read measures
		nMeasures = read(iFile, energies);
		dump(evID, nMeasures, energies);
	}

	// Closes file and deallocates dynamic memory
    iFile.close();
    delete[] energies;

	return 0;
}
