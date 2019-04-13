// braggPlot06
/*
    INPUT OPTIONS: (you must include exactly one of these options)

        1) INPUT FROM FILE
        If the input is: execName input bragg_events.txt
        This program can read the file bragg_events.txt (give it as argument in command line)
        The file contains 1000 events, each of them is composed by an event ID,
        a number of measures, and the vector of the measures. Each event contains about 125 measures.
        The program dumps the read data on the screen, and does statistical analysis (also saving histograms).

        2) SIMULATED INPUT
        If the input is: execName sim numberOfEvents [seed]
        (the seed is optional)
        Then, it takes as input some simulated events (using a pseudo-random number generator).
        The random numbers are generated uniformly in the interval [0:99]. The interval can be
        changed in the constants.h file.

    RANGES OPTION: (you must include this)

        1) RANGES FROM FILE
        Write along the input options the option: "ranges energyRanges"
        This will tell the program to read the file "energyRanges", and to retrieve from it the labels
        and the ranges of total energy for the events. The ranges will be used as categories with
        which separate the read events.
        Each line of the energyRanges file has the format: "<label> <minimumOfRange> <maximumOfRange>".
        Multiple ranges stay on different lines.

    ANALYSIS OPTIONS: (you must include at least one option. You can also include both, in any order.)

        1) DUMP DATA
        You can add to the command line arguments the option "dump".
        For example, if the input is: execName input bragg_events.txt dump
                                  or: execname sim numberOfEvents [seed] dump
        then the program displays on the screen the list of all the read (from file or simulated) energies.

        2) STATISTICS AND HISTOGRAMS
        You can add to the command line arguments the option "dist token_name"
        For example, if the input is: execName input bragg_events.txt dist hist
                                  or: execname sim numberOfEvents [seed] dist hist
        then the program displays on the screen the mean energy distributions for events in
        background, africium, asium, and australium range. (Data simulated or from input).
        The program also save the distributions in several .root files, which names start with the token_name.
        (For example: histBackground.root, histAsium.root, etc.)
        A .root file is saved for each of the 4 ranges, and a unique file with all the histograms is also saved.

        3) BACKGROUND LEVEL
        You can add to the command line arguments the option "bgcalc".
        For example, if the input is: execName input bragg_events.txt bgcalc
                                  or: execname sim numberOfEvents [seed] bgcalc
        the the program will compute and display the background energy level (average level of Bragg curves' tails).
        The program will calculate the level (with error) and display it.
*/

// include directives
#include "AnalysisFactory.h"  // create static method is used
#include "EventSource.h"      // EventSource pointers and static method used
#include "SourceFactory.h"    // SourceFactory object that creates data sources
#include "AnalysisInfo.h"     // AnalysisInfo object created to manage input
#include "inc/Dispatcher.h"   // Dispatcher template class, used to make notifications
#include "AnalysisSteering.h" // Destructor called (polymorphically)

#include <string>             // std::string is used
#include <vector>             // std::vector is used
#include <iostream>           // cout and cin are used

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

    // Creates a vector of analyzers. The AnalysisFactory provides the
    // creation with a stati method.
    // An EventDump object (for printing data) is created if you prompted "dump" in the command line.
    // An EnergyDist object (for statistics and histograms) is created if you prompted "dist" in the cmd line.
    // The EnergyDist creates and saves .root files with the histograms if you prompted "hist <token_name>" too.
    // The token_name is a name you can choose with which the saved file names will begin.
    vector<AnalysisSteering*> AnaList = AnalysisFactory::create( info );

    // Initializes the analyzers
    // (all the analyzers are observers of AnalysisStatus type of enum variable.
    // When they are notified with the value "begin" of status, they do beginJob()).
    Dispatcher<AnalysisInfo::AnalysisStatus>::notify(AnalysisInfo::begin);

    // Reads file or simulation, updates sums and sqSums with events that have tot energy in
	// each of the 4 different ranges, and eventually dumps data
	data_source->Run();

    // Finalizes all analyzers
    // Means and RMSs are computed, histograms are saved, statistical data is displayed
    Dispatcher<AnalysisInfo::AnalysisStatus>::notify(AnalysisInfo::end);

    // Deallocates analyzers and analysisInfo and source
    delete data_source;
    vector<AnalysisSteering*>::iterator it;
    for( it = AnaList.begin(); it != AnaList.end(); ++it)
    {
        delete (*it);
    }
    delete info;

    // Exit
    cout << "Press Enter to terminate." << endl;
    cin.get();
	return 0;
}
