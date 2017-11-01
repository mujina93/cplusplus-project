// braggPlot04
/* Implementation of Event class.
    Here all of its methods are defined.
    Static members are also initialized once here.
    Compile this file together with the main source file
    to use this class.
*/

#include "Event.h"
#include "constants.h" // g_Min_Points and g_Max_Points are used
#include <vector>

// Set the min (120) and max (128) number of points for a Bragg curve
// Initialization of static members
int Event::m_nMeasMin = g_Min_Points;
int Event::m_nMeasMax = g_Max_Points;

// constructor
Event::Event(int a_evID) :
    m_evID(a_evID)
{
    // Vector for the energies (empty). Allocate max number of positions
    m_energies.reserve(m_nMeasMax);
}

// destructor
Event::~Event()
{}

// method that adds an energy to the array of measures
void Event::AddEnergy(const int& a_energy)
{
  // if array of energies is full -> do nothing
  if( (int)m_energies.size() >= m_nMeasMax){return;}
  // otherwise add the value
  m_energies.push_back(a_energy);

  return;
}

// event ID getter
int Event::GetEventID() const
{
    return m_evID;
}
// getter for the number of measures
int Event::GetDataSize() const
{
    return m_energies.size();
}
// get the i-th stored energy
int Event::GetIthEnergy(const int& a_id) const
{
    if( a_id > (int)m_energies.size() )
        {return -1;}
    else
        {return m_energies.at(a_id);}
}

// get static max size
int Event::GetMaxSize()
{
    return m_nMeasMax;
}
// get static min size
int Event::GetMinSize()
{
    return m_nMeasMin;
}
