// braggMean04
/* EnergyDist class definition.
    Inherits from (and implements) AnalysisSteering abstract class.
*/

#ifndef ENERGYDIST_H
#define ENERGYDIST_H

#include "AnalysisSteering.h"   // Inherits from AnalysisSteering
#include <vector>               // vector used

class BraggStatistic;           // BraggStatistic* used

class EnergyDist : public AnalysisSteering
{
    public:
        // typedef for short
        typedef std::vector<BraggStatistic*> BraStatPtrVec;

        // Implemented default constructor
        EnergyDist();
        // Implemented (ex-virtual) destructor
        ~EnergyDist();

        // Implemented (ex-virtual) function to be called at execution start
        void beginJob();
        // Implemented (ex-virtual) function to be called at execution end
        void endJob();
        // Implemented (ex-virtual) function that dumps event's data
        void process( const Event& a_ev );

    private:
        // Vector of Bragg curves pointers for different total energy ranges
        BraStatPtrVec m_vBraggCurvePtrs;

        // Prints statistical results in a good-looking format
        void PrintResults();

        // Prevent shallow copy
        EnergyDist( const EnergyDist& x );
        EnergyDist& operator=( const EnergyDist& x );

};

#endif // ENERGYDIST_H
