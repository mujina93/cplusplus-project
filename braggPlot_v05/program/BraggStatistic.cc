// braggPlot05
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
#include "TotalEnergy.h" // TotalEnergy static method used
#include "bkgconstants.h"   // background level used

// constructor
BraggStatistic::BraggStatistic(int a_minEnergy, int a_maxEnergy ):
    m_minEnergy(a_minEnergy),
    m_maxEnergy(a_maxEnergy),
    m_nValidEvents(0),
    m_energySums(g_Min_Points,0.),
    m_sqEnergySums(g_Min_Points,0.),
    m_energyMeans(g_Min_Points,0.),
    m_energyRMSs(g_Min_Points,0.)
{}

// destructor
BraggStatistic::~BraggStatistic()
{}

// method that takes an event and updates the arrays with its energy values
void BraggStatistic::AddEventUpdateSums( const Event& a_ev )
{
    // Total energy of the event:

    // Call the static instance() function of TotalEnergy.
    // By calling this function, the singleton static instance of TotalEnergy
    // is created (the function instance() creates the object).
    // A pointer to the singleton is returned.
    TotalEnergy* p_TE = TotalEnergy::instance();
    // Get now total energy from the TotalEnergy object
    // (since TotalEnergy is a lazy object, it will update its
    // state now, and compute the total now, for the first time)
    // (Here we get the total energy with background level subtracted)
    int totEn = p_TE->GetEnergySum();


    // If the event is in range, update sums and sums of squares, otherwise, exit
    if(totEn < m_minEnergy || totEn > m_maxEnergy){return;}

    // Loop over minimum number of points and update sums
    double en;
    for(int i=0; i < g_Min_Points;i++)
    {
        en = a_ev.GetIthEnergy(i);
        m_energySums.at(i) += en;
        m_sqEnergySums.at(i) += en*en;
    }

    // Increase the counter of valid events
    m_nValidEvents++;

    return;
}

// Method that computes means and rmss for each point
// Then, we take away the background level and recompute
// the means and RMSs.
void BraggStatistic::ComputeMeanRMS()
{
    double variance;
    for(int i=0; i<g_Min_Points; i++)
    {
        // Mean of energy for each of the 120 points
        m_energyMeans.at(i) = m_energySums.at(i)/m_nValidEvents;

        // RMS for each of the 120 points
        variance = m_sqEnergySums.at(i)/m_nValidEvents - pow(m_energyMeans.at(i),2);
        // Check if variance went a little under 0 due to truncation errors
        if(variance<0)
        {
            m_energyRMSs.at(i)=0;
        } else m_energyRMSs.at(i) = sqrt(variance);

        // BKG level subtraction
        m_energyMeans.at(i) -= BKGConstants::bgMean;

        // Update RMSs with error propagation, using error on bkg level
        double sigma_a = m_energyRMSs.at(i);
        double sigma_b = BKGConstants::bgRMS;
        m_energyRMSs.at(i) = sqrt( sigma_a*sigma_a + sigma_b*sigma_b);

    }
    return;
}

// Getter for the array of means
const vector<double>& BraggStatistic::GetMeans() const
{
    return m_energyMeans;
}

// Getter for the array of RMSs
const vector<double>& BraggStatistic::GetRMSs() const
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
               m_energyMeans.at(i),
               m_energyRMSs.at(i) );
	}
}
