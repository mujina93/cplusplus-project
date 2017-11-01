// braggMean02
/* This function prints on the screen the data of the given event
    It takes as input the Event (as const reference).
*/

#include <iostream>  // std::cout, std::endl used
#include "Event.h"  // Event class used

using std::cout;
using std::endl;

void dump(const Event& a_ev)
{
	// Prints data event ID and number of measures for that event
    cout << "***** EVENT: " << a_ev.GetEventID() << " *****" << endl;
	int nMeasures = a_ev.GetDataSize();
	cout << "***** number of points: " << nMeasures << " *****" << endl;
	cout << "***** energy values for this event: ";

	// Prints the measures of that event
	for (int i = 0; i < nMeasures; i++)
    {
		cout << a_ev.GetIthEnergy(i) << " | ";
	}
	cout << endl;

	return;
}
