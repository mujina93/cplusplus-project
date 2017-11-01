// braggMean04
/* EnergyDist class implementation.
    Inherits from (and implements) AnalysisSteering abstract class.
*/

#include "EnergyDist.h"     // Implements EnergyDist class
#include "BraggStatistic.h" // Creates BraggStatistic objects
#include <vector>           // Uses vector methods
#include <iostream>         // cout, cin, endl used

// Implemented default constructor
EnergyDist::EnergyDist()
{
    // Reserves 4 places in the vector
    m_vBraggCurvePtrs.reserve(4);
}

// Implemented (ex-virtual) destructor
EnergyDist::~EnergyDist()
{
    // Deallocate dynamic memory allocated by the pointers in the vector member
    for (BraStatPtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        delete (*it);
    }
    m_vBraggCurvePtrs.clear();
}

// Allocates 4 BraggStatistic objects (1 for each range of energy)
void EnergyDist::beginJob()
{
    // Dynamically creates the BraggStatistic objects, 1 for each energy range
    BraggStatistic* pBackground= new BraggStatistic(3000,5000);
    BraggStatistic* pAfricium= new BraggStatistic(6000,6499);
    BraggStatistic* pAsium= new BraggStatistic(6500,6799);
    BraggStatistic* pAustralium= new BraggStatistic(6800,7200);
    // Store the 4 pointers
    m_vBraggCurvePtrs.push_back(pBackground);
    m_vBraggCurvePtrs.push_back(pAfricium);
    m_vBraggCurvePtrs.push_back(pAsium);
    m_vBraggCurvePtrs.push_back(pAustralium);
}

// Compute Mean and RMSs for each BraggStatistic object
void EnergyDist::endJob()
{
    // Loop over the vector and add try to add the event data to each object
    for (BraStatPtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        (*it)->ComputeMeanRMS();
    }
    // Prints statistical results
    PrintResults();
    return;
}

// Method that takes an event and updates the right BraStat objects
// (correct energy range) with its energy values
void EnergyDist::process( const Event& a_ev )
{
    // Loop over the vector and add try to add the event data to each object
    for (BraStatPtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        (*it)->AddEventUpdateSums(a_ev);
    }
    return;
}

// Method that prints statistical results in a good-looking format
void EnergyDist::PrintResults()
{
    using std::cout;
    using std::cin;
    using std::endl;

    for (BraStatPtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        cout << "Press Enter to display more output" << endl;
        cin.get();
        (*it)->PrintStatisticalResults();
    }

    return;
}
