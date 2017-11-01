// braggPlot04
/* TotalEnergy class implementation.
    This class is a singleton, and it is a lazy observer
    of Events. (updates only when checked with data coming
    from events' notifications).
*/

#include "TotalEnergy.h"       // Implementation of
#include "constants.h"         // g_Min_Points used
#include "Event.h"             // Event method used

// Const
TotalEnergy::TotalEnergy():
    m_RawSum(0)
{}

// Dest
TotalEnergy::~TotalEnergy()
{}

// Observer method:
// Function to be called when a new event arrives
void TotalEnergy::update( const Event& a_ev )
{
    // Resets sum at 0
    m_RawSum = 0;

    // Loop over minimum number of points and update sums
    for(int i=0; i < g_Min_Points; i++)
    {
        m_RawSum += a_ev.GetIthEnergy(i);
    }

    return;
}


// Sum of measurements, no background subtraction
double TotalEnergy::GetRawSum()
{
    // Checks if there is a pending event.
    // If any, update TotalEnergy. Then, set the flag UpToDate = true.
    check();

    // Once updated, get m_RawSum
    return m_RawSum;
}

