// braggMean02
/*  This program reads the file bragg_events.txt (give it as argument in command line)
    The file contains 1000 events, each of them is composed by an event ID,
    a number of measures, and the array of the measures. Each event contains about 125 measures.
    The program dumps the read data on the screen, and does statistical analysis.
*/

// include directive
#include <cstring>          // strdup is used
#include <fstream>          // std::ifstream is used
#include <iostream>         // cout and cin are used
#include "BraggStatistic.h" // BraggStatistic class used
#include "constants.h"      // g_Min_Points is used
#include "Event.h"          // Complete class type needed for calling delete on an Event object

// using declarations
using std::ifstream;
using std::ios;
using std::cout;
using std::cin;
using std::endl;

// Global functions declarations
// Function that reads a bunch of the file and stores data
const Event* read(ifstream& a_iFile);
// Function that prints on the screen the data for an event
void dump(const Event& a_ev);


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

    //objects for statistics
    BraggStatistic backgroundAnalyzer(3000,5000);
    BraggStatistic africiumAnalyzer(6000,6499);
    BraggStatistic asiumAnalyzer(6500,6799);
    BraggStatistic australiumAnalyzer(6800,7200);

    // Wanna display data?
    char chose = 'n';
    cout << "Do you want to display the events data? (y/n)\n";
    cout << "(Otherwise, skip to statistical data)" << endl;
    cin.get(chose);
    cin.ignore();

    // Pointer to Event, in which we store data through the loop
	const Event* p_ev;

	// Reads file, updates sums and sqSums with events that have tot energy in
	// each of the 4 different ranges, and dumps data
	while ( (p_ev = read(iFile )) )         // reads and stores an event, until EOF is reached
    {
        // If a valid event is found, updates the data stored in
        // the statistical objects using the event's energies
        backgroundAnalyzer.AddEventUpdateSums(*p_ev);
        africiumAnalyzer.AddEventUpdateSums(*p_ev);
        asiumAnalyzer.AddEventUpdateSums(*p_ev);
        australiumAnalyzer.AddEventUpdateSums(*p_ev);

        // Dumps read data on the screen
        if (chose == 'y')
            dump(*p_ev);

        // Deallocate dynamic object before p_ev points to another object
        delete p_ev;
	}

    // Closes input file
    iFile.close();

    // Computes statistical results
    backgroundAnalyzer.ComputeMeanRMS();
    africiumAnalyzer.ComputeMeanRMS();
    asiumAnalyzer.ComputeMeanRMS();
    australiumAnalyzer.ComputeMeanRMS();

    // Prints statistical results
    cout << "Press Enter to display more output" << endl;
    cin.get();
    backgroundAnalyzer.PrintStatisticalResults();
    cout << "Press Enter to display more output" << endl;
    cin.get();
    africiumAnalyzer.PrintStatisticalResults();
    cout << "Press Enter to display more output" << endl;
    cin.get();
    asiumAnalyzer.PrintStatisticalResults();
    cout << "Press Enter to display more output" << endl;
    cin.get();
    australiumAnalyzer.PrintStatisticalResults();

    cout << "Press Enter to terminate." << endl;
    cin.get();
	return 0;
}
