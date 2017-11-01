// braggDumpv02
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

// Forward declaration of Event struct. Only a pointer to Event is used in the following
struct Event;

// Functions declarations:
// Function that reads a bunch of the file and stores data
const Event* read(ifstream& a_iFile);
// Function that prints on the screen the data for an event
void dump(const Event& a_ev);
// Function that deallocates all the memory dynamically allocated by the event (and the event itself)
void clear(const Event* a_p_ev);


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

	// Pointer to Event, in which we store data through the loop
	const Event* p_ev;

	// Read file and dump data
	while ( (p_ev = read(iFile )) )         // reads and stores an event, until EOF is reached
    {
        // Dumps read data on the screen
        dump(*p_ev);
        // Clear dynamic allocated memory
        clear(p_ev);
	}

	// Close input file
    iFile.close();

	return 0;
}
