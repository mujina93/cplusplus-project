// braggMean01
/*  This program reads the file bragg_events.txt (give it as argument in command line)
    The file contains 1000 events, each of them is composed by an event ID,
    a number of measures, and the array of the measures. Each event contains about 125 measures.
    The program dumps the read data on the screen, and does statistical analysis.
*/

// Object macros
#define MIN_TOT_ENERGY 6000
#define MAX_TOT_ENERGY 7500

// include directive
#include <cstring>  // strdup is used
#include <fstream>  // std::ifstream is used

// using declarations
using std::ifstream;
using std::ios;
using std::fill;

// Global (static & external linkage) constant variable - Defining declaration
extern const int Min_Points = 120; // max dimension for the array of measures.

// Forward declaration of Event struct. Only a pointer to Event is used in the following
struct Event;

// Global functions declarations
// Function that reads a bunch of the file and stores data
const Event* read(ifstream& a_iFile);
// Function that prints on the screen the data for an event
void dump(const Event& a_ev);
// Function that deallocates all the memory dynamically allocated by the event (and the event itself)
void clear(const Event* a_p_ev);
// Function that compute the means and the RMSs for each point of the Bragg curve
void stat(int a_nValidEvents,
          int a_nPoints,
          double* a_energySums,
          double* a_sqEnergySums,
          double* a_energyMeans,
          double* a_energyRMSs);
// Function that check if an event is in range or not, and updates the energy sums and sqEnergy sums
bool add(const Event& a_ev,
         double* a_energySums,
         double* a_sqEnergySums,
         int a_minEnergy,
         int a_maxEnergy);


int main(int argc, char* argv[])
{
    // File name
    char* file_name = argv[1];
    if (file_name == NULL)
    {
        file_name = strdup("bragg_events.txt"); // default name, if you forgot
    }
    // Opens file
	ifstream iFile;
	iFile.open(file_name, ios::in);

    // Arrays for sum of energies, sum of energy squares, energy means, and energy RMSs - for each event
    double* energySums = new double[Min_Points];
    double* sqEnergySums= new double[Min_Points];
    double* energyMeans = new double[Min_Points];
    double* energyRMSs = new double[Min_Points];

    // Initializes the arrays to zeros
    fill(energySums, energySums + Min_Points, 0);
    fill(sqEnergySums, sqEnergySums + Min_Points, 0);
    fill(energyMeans, energyMeans + Min_Points, 0);
    fill(energyRMSs, energyRMSs + Min_Points, 0);

	// Pointer to Event, in which we store data through the loop
	const Event* p_ev;
	// Number of valid events
    int nValidEvents = 0;

	// Reads file, updates sums and sqSums with events that have tot energy in [6000,7500], and dumps data
	while ( (p_ev = read(iFile )) )         // reads and stores an event, until EOF is reached
    {
        // If a valid event is found, updates the arrays Sums, sqSums, and the counter
        nValidEvents += add(*p_ev,
                           energySums,
                           sqEnergySums,
                           MIN_TOT_ENERGY,
                           MAX_TOT_ENERGY);
        // Dumps read data on the screen
        dump(*p_ev);
        // Clears dynamic allocated memory
        clear(p_ev);
	}

	// Closes input file
    iFile.close();

	// Computes means and RMSs for each of the 120 points of the Bragg curve
    stat(nValidEvents,
          Min_Points,
          energySums,
          sqEnergySums,
          energyMeans,
          energyRMSs);

	// Prints statistical results
	printf("\nSTATISTICAL DATA \n");
	printf("\nNumber of valid events (events with total energy from 6000 to 7500): %i \n", nValidEvents);
	printf("\n%s \n","Point | Energy mean | Energy rms");
	for(int i=0; i<Min_Points; i++)
    {
        printf("%4i  |   %3.2f     |   %3.2f\n", i+1, energyMeans[i], energyRMSs[i]);
	}

	// Deallocates dynamic memory
	delete[] energySums;
	delete[] sqEnergySums;
	delete[] energyMeans;
	delete[] energyRMSs;

	return 0;
}
