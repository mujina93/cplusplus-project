// braggPlot05
/* EventSim implementation. This class provides the code
    necessary to simulate random Bragg events, and to return
    them.
*/

#include "EventSim.h"   // implementation of
#include "Event.h"      // Event object instantiated
#include "constants.h"  // g_RandomFrom and g_RandomTo used

#include <stdlib.h>     // rand and srand used
#include <math.h>       // sqrt, round used


// Creates an EventSim and initialize the seed for the rng
EventSim::EventSim( unsigned int a_n, unsigned int a_seed ):
    m_evId( 0 ),
    m_nMax( a_n )
{
    // Initializes the seed
    srand( a_seed );
}

// Default destructor
EventSim::~EventSim()
{}


// Gets one random event (if you didn't reach the maximum)
const Event* EventSim::GetEventPtr()
{
    if ( m_evId < m_nMax ) return generate();
    return 0;
}


// Generates a random event (seed set on construction)
const Event* EventSim::generate()
{
    // Creates a new event
    Event* p_ev = new Event( ++m_evId );

    // Simulates a number of points
    int nMin = Event::GetMinSize();
    int nMax = Event::GetMaxSize();
    int n = nMin + round( ( nMax - nMin ) * ( rand() * 1.0 / RAND_MAX ) );

    // Simulates energy loss
    int i;
    for ( i = 0; i < n; ++i ) p_ev->AddEnergy( round( g_RandomFrom + rand() * (g_RandomTo * 1.0) / RAND_MAX ) );

    return p_ev;

}

