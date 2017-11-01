// braggMean02
/* Implementation of BraggStatistic class.
    Here all of its methods are defined.
    Static members are also initialized once here (if any).
    Compile this file together with the main source file
    to use this class.
*/

#include "BraggStatistic.h"
#include "Event.h"  // Event class methods are used below
#include "constants.h" // g_Min_Points is used
#include <math.h>   // sqrt and pow is used
#include <iostream> // std::cout is used
#include <stdio.h>  // printf is used

// constructor
BraggStatistic::BraggStatistic(int a_minEnergy, int a_maxEnergy ):
    m_minEnergy(a_minEnergy),
    m_maxEnergy(a_maxEnergy),
    m_nValidEvents(0)
{
    using std::fill;    // fill used later

    // Allocates dynamic arrays
    m_energySums = new double[g_Min_Points];
    m_sqEnergySums= new double[g_Min_Points];
    m_energyMeans = new double[g_Min_Points];
    m_energyRMSs = new double[g_Min_Points];

    // Initializes the arrays to zeros
    fill(m_energySums,      m_energySums    + g_Min_Points, 0);
    fill(m_sqEnergySums,    m_sqEnergySums  + g_Min_Points, 0);
    fill(m_energyMeans,     m_energyMeans   + g_Min_Points, 0);
    fill(m_energyRMSs,      m_energyRMSs    + g_Min_Points, 0);
}

// destructor
BraggStatistic::~BraggStatistic() {
    delete[] m_energySums;
    delete[] m_sqEnergySums;
    delete[] m_energyMeans;
    delete[] m_energyRMSs;
}

// method that takes an event and updates the arrays with its energy values
void BraggStatistic::AddEventUpdateSums( const Event& a_ev )
{
    // Total energy of the event
    double totEn = 0;
    for(int i=0; i < g_Min_Points; i++)
    {
        totEn += a_ev.GetIthEnergy(i);
    }

    // If the event is in range, update sums and sums of squares, otherwise, exit
    if(totEn < m_minEnergy || totEn > m_maxEnergy){return;}

    // Loop over minimum number of points and update sums
    double en;
    for(int i=0; i < g_Min_Points ;i++)
    {
        en = a_ev.GetIthEnergy(i);
        m_energySums[i] += en;
        m_sqEnergySums[i] += en*en;
    }

    // Increase the counter of valid events
    m_nValidEvents++;

    return;
}

// Method that computes means and rmss for each point
void BraggStatistic::ComputeMeanRMS()
{
    double variance;
    for(int i=0; i<g_Min_Points; i++)
    {
        // Mean of energy for each of the 120 points
        m_energyMeans[i] = m_energySums[i]/m_nValidEvents;
        // RMS for each of the 120 points
        variance = m_sqEnergySums[i]/m_nValidEvents - pow(m_energyMeans[i],2);
        // Check if variance went a little under 0 due to truncation errors
        if(variance<0)
        {
            m_energyRMSs[i]=0;
        } else m_energyRMSs[i]=sqrt(variance);
    }
    return;
}

// Getter for the array of means
const double* BraggStatistic::GetMeans() const
{
    return m_energyMeans;
}

// Getter for the array of RMSs
const double* BraggStatistic::GetRMSs() const
{
    return m_energyRMSs;
}

// Method that prints statistical results on the screen
void BraggStatistic::PrintStatisticalResults() const
{
    using std::cout;
    using std::endl;

    cout << "Statistical results for range: [";
    cout << m_minEnergy << "-" << m_maxEnergy << "] ";

    switch (m_minEnergy)
    {
    case 3000 :
        cout << "(background)" << endl;
        break;
    case 6000 :
        cout << "(africium)" << endl;
        break;
    case 6500 :
        cout << "(asium)" << endl;
        break;
    case 6800 :
        cout << "(australium)" << endl;
        break;
    }

    cout << m_nValidEvents << " events were used." << endl;

	printf("%s \n","Point | Energy mean | Energy rms");
	for(int i=0; i < g_Min_Points; i++)
    {
        printf("%4i  |   %7g   |   %7g\n",
               i+1,
               m_energyMeans[i],
               m_energyRMSs[i]);
	}
}
