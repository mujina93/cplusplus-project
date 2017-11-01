// braggDumpv02
/* This function prints on the screen the data of the given event
    It takes as input the Event (as const reference).
*/

#include<iostream>  // std::cout, std::endl used
#include "Event.h"  // Event struct used

using std::cout;
using std::endl;

void dump(const Event& a_ev)
{
	// Prints data event ID and number of measures for that event
    cout << "***** EVENT: " << a_ev.m_evID << " *****" << endl;
	cout << "***** number of points: " << a_ev.m_nMeasures << " *****" << endl;
	cout << "***** energy values for this event: ";

	// Prints the measures of that event
	for (int i = 0; i < a_ev.m_nMeasures; i++)
    {
		cout << a_ev.m_energies[i] << " | ";
	}
	cout << endl;

	return;
}
