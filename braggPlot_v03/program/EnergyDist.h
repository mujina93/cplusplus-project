// braggPlot03
/* EnergyDist class definition.
    Inherits from (and implements) AnalysisSteering abstract class.
*/

#ifndef ENERGYDIST_H
#define ENERGYDIST_H

#include "AnalysisSteering.h"   // Inherits from AnalysisSteering
#include <vector>               // vector used
#include <string>				// string used

class AnalysisInfo;             // AnalysisInfo* used
class BraggStatistic;           // BraggStatistic* used
class TH1F;						// TH1F* used
using std::string;				// string used

class EnergyDist : public AnalysisSteering
{
    public:
		// BraggCurve nested struct definition
		struct BraggCurve
		{
			BraggStatistic* m_pBraggStat;
			TH1F* m_pHist;
		};

        // typedef for short
        typedef std::vector<BraggCurve*> BraCurvePtrVec;

        // Constructor that takes infos as argument
        EnergyDist( const AnalysisInfo* a_info );
        // Implemented (ex-virtual) destructor
        ~EnergyDist();

        // Implemented (ex-virtual) function to be called at execution start
        void beginJob();
        // Implemented (ex-virtual) function to be called at execution end
        void endJob();
        // Implemented (ex-virtual) function that dumps event's data
        void process( const Event& a_ev );

        // Prints statistical results in a good-looking format
        void PrintResults();

    private:
        // Vector of Bragg curves pointers for different total energy ranges (4 ranges)
        BraCurvePtrVec m_vBraggCurvePtrs;

		// Method to create BraggCurve object for a certain range
        void bCreate( int a_id, float a_minEn, float a_maxEn );

        // Prevent shallow copy
        EnergyDist( const EnergyDist& x );
        EnergyDist& operator=( const EnergyDist& x );

};

#endif // ENERGYDIST_H
