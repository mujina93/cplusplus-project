// braggMean01
/* This function computes the means and the rmss for the set
    of energy values of each point.
    The arrays have all size = a_nPoints (= 120)
    and each sum of energies or squares of energy is done
    over a number of values = a_nValidEvents (approx 1000).
*/

#include <math.h> // sqrt and pow used


void stat(int a_nValidEvents,
          int a_nPoints,
          double* a_energySums,
          double* a_sqEnergySums,
          double* a_energyMeans,
          double* a_energyRMSs)
{
    // Compute the means and the RMSs
    double variance;
    for(int i=0; i<a_nPoints; i++)
    {
        // Mean of energy for each of the 120 points
        a_energyMeans[i] = a_energySums[i]/a_nValidEvents;
        // RMS for each of the 120 points
        variance = a_sqEnergySums[i]/a_nValidEvents - pow(a_energyMeans[i],2);
        // Check if variance went a little under 0 for truncation errors
        if(variance<0)
        {
            a_energyRMSs[i]=0;
        } else a_energyRMSs[i]=sqrt(variance);
    }

    return;
}
