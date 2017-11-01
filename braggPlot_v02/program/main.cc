// braggPlot02
/*
    INPUT FROM FILE
    If the input is: execName input bragg_events.txt
    This program can read the file bragg_events.txt (give it as argument in command line)
    The file contains 1000 events, each of them is composed by an event ID,
    a number of measures, and the vector of the measures. Each event contains about 125 measures.
    The program dumps the read data on the screen, and does statistical analysis (also saving histograms).

    SIMULATED INPUT
    If the input is: execName sim numberOfEvents [seed]
    (the seed is optional)
    Then, it takes as input some simulated events (using a pseudo-random number generator).
    The random numbers are generated uniformly in the interval [0:99]. The interval can be
    changed in the EventSim class implementation file (EventSim.cc).
*/

// include directives
#include "EventReadFromFile.h"// EventReadFromFile object created
#include "AnalysisSteering.h" // AnalysisSteering* in vector
#include "EnergyDist.h"     // EnergyDist object created
#include "EventDump.h"      // EventDump object created
#include "Event.h"          // Complete class type needed for calling delete on an Event object
#include "AnalysisInfo.h"   // AnalysisInfo object created to manage input
#include "SourceFactory.h"  // SourceFactory object that creates data sources

#include <string>           // std::string is used
#include <vector>           // std::vector is used
#include <iostream>         // cout and cin are used

// using declarations
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


int main(int argc, char* argv[])
{
    // Stores command line parameters
    AnalysisInfo* info = new AnalysisInfo( argc, argv );

    // Creates data source by input
    // The SourceFactory factory provides the creation with a static method
    EventSource* data_source = SourceFactory::create( info );

    // Creates a vector of 2 analyzers. 1 for dumping data, 1 for computing the statistics
    vector<AnalysisSteering*> AnaList;
    AnaList.push_back( new EnergyDist() );
    AnaList.push_back( new EventDump() );
    vector<AnalysisSteering*>::iterator it;

    // Initializes the analyzers
    for( it = AnaList.begin(); it != AnaList.end(); ++it)
    {
        (*it)->beginJob();
    }

    // Wanna display data?
    char chose = 'n';
    cout << "Do you want to display the events data? (y/n)\n";
    cout << "(Otherwise, skip to statistical data)" << endl;
    cin.get(chose);
    cin.ignore();

    // Reads file, updates sums and sqSums with events that have tot energy in
	// each of the 4 different ranges, and dumps data
	const Event* p_ev;
    while ( (p_ev = data_source->GetEventPtr()) ) // reads and stores an event, until EOF is reached
    {
        // If a valid event is found, updates the data stored in
        // the statistical objects using the event's energies.
        AnaList.at(0)->process(*p_ev);

        // And dumps data of the event on the screen.
        if (chose == 'y')
            AnaList.at(1)->process(*p_ev);

        // Deallocates dynamic object before p_ev points to another object
        delete p_ev;
    }

    // Closes input file
    delete data_source;

    // Finalizes all analyzers (means and RMSs are computed)
    for( it = AnaList.begin(); it != AnaList.end(); ++it)
    {
        (*it)->endJob();
    }


    // Deallocates analyzers
    for( it = AnaList.begin(); it != AnaList.end(); ++it)
    {
        delete (*it);
    }

    // Exit
    cout << "Press Enter to terminate." << endl;
    cin.get();
	return 0;
}
