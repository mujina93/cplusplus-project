// braggDumpv01
// This function prints on the screen the data of the given event
// It takes as input the event ID, the number of measures of that event,
// and the array of measures for that event

#include<iostream>  // std::cout, std::endl used

using std::cout;
using std::endl;

void dump(const int a_evID, const int a_nMeasures, const int*const a_energies)
{
    // Prints data event ID and number of measures for that event
    cout << "***** EVENT: " << a_evID << " *****" << endl;
	cout << "***** number of points: " << a_nMeasures << " *****" << endl;
	cout << "***** energy values for this event: ";

	// Prints the measures of that event
	for (int i = 0; i < a_nMeasures; i++)
    {
		cout << a_energies[i] << " | ";
	}
	cout << endl;

	return;
}
