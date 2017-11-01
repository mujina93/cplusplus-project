// braggDumpv01
// This function reads an event, stores the measures in the given array,
// and returns the event ID.

#include<fstream>   // std::ifstream used

using std::ifstream;

int read(ifstream& a_iFile, int*const a_energies)
{
	// Reads and stores the number of measures
	int numMeasures;
	a_iFile >> numMeasures;

	// Reads and stores the measures
	for (int i = 0; i < numMeasures; i++)
    {
		a_iFile >> a_energies[i];
	}

    // Returns the number of measures
	return numMeasures;
}
