// braggMean01
/* This function takes an event and 2 arrays, and an interval of energy.
    If the total of the energies of the event is out from the interval,
    the event is not used.
    Otherwise, it updates the 2 given arrays (sum of energies and sum of
    squares of energies) by adding the i-th energy of the event to sumenergies[i],
    and the square of the i-th energy to sumsqenergies[i].
*/

#include <math.h>   // pow is used
#include "Event.h"  // Event struct is used

// Global (static & external linkage) constant variable
// - Referencing declaration (variable defined in main.cc)
extern const int Min_Points; // min dimension for the array of measures.


bool add(const Event& a_ev,
         double* a_energySums,
         double* a_sqEnergySums,
         int a_minEnergy,
         int a_maxEnergy)
{
    // Variable that says wether the event has a total acceptable energy or not
    bool evIsInRange = false; //default value

    // Computes total energy of the event
    double totEnergy = 0;
    for(int i=0; i<Min_Points; i++)
    {
            totEnergy += a_ev.m_energies[i];
    }

    // If the total energy is in the accepted range (the event is acceptable),
    // updates the sum of energies and the sum of the squares.
    if((totEnergy > a_minEnergy) && (totEnergy < a_maxEnergy))
    {
            evIsInRange = true;
            for(int i=0; i<Min_Points; i++)
            {
                a_energySums[i] += a_ev.m_energies[i];
                a_sqEnergySums[i] += pow( a_ev.m_energies[i], 2);
            }
    }

    // Returns 1 if the event was in range and was used to update the sumEnergies and sumSqEnergies
    return evIsInRange;
}
