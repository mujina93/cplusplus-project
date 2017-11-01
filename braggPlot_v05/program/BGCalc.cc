// braggPlot05
/* BGCalc class implementation. This class computes the
    background (= the mean energy of events from the
    100th point to the 120th point of the bragg curves).

    The creation of BGCalc is made by a BGCalcBuilder.
    BGCalcBuilder class defined here.
*/

#include "BGCalc.h"             // implementation of
#include "AnalysisFactory.h"    // AnalysisFactory::Builder implemented
#include "AnalysisSteering.h"   // constructor called
#include "AnalysisInfo.h"       // AnalysisInfo used
#include "TotalEnergy.h"        // TotalEnergy methods used
#include "Event.h"              // GetIthEnergy method used

#include <iostream>         // cout
#include <cmath>            // sqrt used

// Intermediate builder class to create an BGCalc analyzer
// This class implements the abstract nested Builder class
// that is defined inside AnalysisFactory
class BGCalcBuilder: public AnalysisFactory::Builder
{
    public:
        // Creates the builder object, assign "bgcalc" as
        // name for this analyzer and builder
        BGCalcBuilder():
            AnalysisFactory::Builder( "bgcalc" )
        {}

        // The AnalysisFactory will make the builder use
        // this method when it wants an BGCalc to be created.
        virtual AnalysisSteering* build( const AnalysisInfo* a_info )
        {
            // Dynamically creates an BGCalc object, if the infos require it
            return new BGCalc( a_info );
        }
};

// Create a global BGCalcBuilder, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an BGCalcBuilder will be available with name "dump".
static BGCalcBuilder BGCBuilder;

// Constructor (initializes following the given infos)
BGCalc::BGCalc( const AnalysisInfo* a_info ):
    AnalysisSteering( a_info ),
    m_nSelectedEvents(0),
    m_SumEnergies(0),
    m_SumSqEnergies(0)
{}

// Default destructor
BGCalc::~BGCalc()
{}

// Initializes members
void BGCalc::beginJob()
{
    // Take only events with total energy between min and max
    m_minEn = 3000;
    m_maxEn = 5000;

    // Use points from startPoint to endPoint to perform the calculation
    m_startPoint = 100;
    m_endPoint = 120;

    return;
}

// Sum up the energy sums and the energy squares sum
void BGCalc::update( const Event& a_ev )
{
    // Call the static instance() function of TotalEnergy.
    // By calling this function, the singleton static instance of TotalEnergy
    // is created (the function instance() creates the object).
    // A pointer to the singleton is returned.
    TotalEnergy* p_TE = TotalEnergy::instance();

    // Get total energy from the TotalEnergy object
    // (since TotalEnergy is a lazy object, it will update its
    // state now, and compute the total now, for the first time)
    int totEn = p_TE->GetRawSum();

    // If the event is in range, update sums and sums of squares, otherwise, exit
    if(totEn < m_minEn || totEn > m_maxEn){return;}

    // Loop from startPoint to endPoint and add its energy values to the big sums
    int temp_en;
    for(int i=m_startPoint; i < m_endPoint; i++)
    {
        temp_en = a_ev.GetIthEnergy(i);
        m_SumEnergies += temp_en;
        m_SumSqEnergies += temp_en*temp_en;
    }

    // Increase the counter of events used for the bkg calculation
    m_nSelectedEvents++;

    return;
}

// Computes mean and rms of energies and gives a level for the background
void BGCalc::endJob()
{
    using std::cout;
    using std::endl;

    // The total energies summed up until now
    int nTotalPoints = m_nSelectedEvents*(m_endPoint - m_startPoint);

    // The bkg mean level
    double mean = m_SumEnergies / nTotalPoints;

    // The variance
    double var = m_SumSqEnergies/nTotalPoints - pow(mean,2);

    // The bkg error
    double rms;
    // Check if variance went a little under 0 due to truncation errors
    if(var<0)
    {
        rms = 0;
    } else rms = sqrt(var);

    // Print background level results
    cout << "\nBackground calculation results:" << endl;
    cout << "Only events with total energy within [";
    cout << m_minEn << "-" << m_maxEn << "] were used.\n";
    cout << "Number of selected events for the calculation: ";
    cout << m_nSelectedEvents << endl;
    cout << "Only energies from the " << m_startPoint;
    cout << "th to the " << m_endPoint;
    cout << "th point of each event were taken into account for the calculation.\n";

    cout << "Background level (mean and rms): " << endl;
    cout << mean << " +/- " << rms << endl << endl;

    return;
}

