// braggMean02
/* Implementation of Event class.
    Here all of its methods are defined.
    Static members are also initialized once here.
    Compile this file together with the main source file
    to use this class.
*/

#include "Event.h"
#include "constants.h" // g_Min_Points and g_Max_Points are used

// Set the min (120) and max (128) number of points for a Bragg curve
// Initialization of static members
int Event::m_nMeasMin = g_Min_Points;
int Event::m_nMeasMax = g_Max_Points;

// constructor
Event::Event(int a_evID) :
    m_evID(a_evID),
    m_nMeasures(0)
{
    // Dynamic empty array for the energies
    m_energies = new int[m_nMeasMax];
    for(int i=0; i<m_nMeasMax; i++)
        m_energies[i] = 0;
}

// copy constructor for deep copy
Event::Event(const Event& a_ev){
    // shallow copy for non-pointer members
    m_evID = a_ev.m_evID;
    m_nMeasures = a_ev.m_nMeasures;
    // deep copy for pointers (if the pointer of 'a_ev' is not null)
    if(a_ev.m_energies){
        m_energies = new int[m_nMeasMax];
        for(int i=0; i<m_nMeasMax; i++){
            m_energies[i] = a_ev.m_energies[i];
        }
    } else m_energies = 0;
}

// deep assignment operator
Event& Event::operator=(const Event& a_ev){
    // check to avoid auto-assignment
    if(this == &a_ev) return *this;

    // shallow copy for non-pointer members
    m_evID = a_ev.m_evID;
    m_nMeasures = a_ev.m_nMeasures;
    // deep copy for pointers (if the pointer of 'a_ev' is not null)
    if(a_ev.m_energies){
        m_energies = new int[m_nMeasMax];
        for(int i=0; i<m_nMeasMax; i++){
            m_energies[i] = a_ev.m_energies[i];
        }
    } else m_energies = 0;

    return *this;
}

// destructor
Event::~Event()
{
    delete[] m_energies;
}

// method that adds an energy to the array of measures
void Event::AddEnergy(const int& a_energy)
{
  // if array of energies is full -> do nothing
  if(m_nMeasures >= m_nMeasMax){return;}
  // otherwise add the value
  m_energies[m_nMeasures++] = a_energy;

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
    return m_nMeasures;
}
// get the i-th stored energy
int Event::GetIthEnergy(const int& a_id) const
{
    if( a_id > m_nMeasures )
        {return -1;}
    else
        {return m_energies[a_id];}
}

// get static max size
int Event::GetMaxSize() const
{
    return m_nMeasMax;
}
// get static min size
int Event::GetMinSize() const
{
    return m_nMeasMin;
}
