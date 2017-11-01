// braggMean03
/* BraggStatistic class definition.
    The purpose of this class is to collect total energies from
    events with total energy in a specified range, and then
    compute means and RMSs for each point of the curve, over the
    several accepted events (events that were in range).
*/

#ifndef BRAGG_STATISTIC_H
#define BRAGG_STATISTIC_H

#include <vector>
using std::vector;

class Event; // forward declaration. Event* and Event& are used below.

class BraggStatistic
{
    private:
        // min and max energy
        int m_minEnergy;
        int m_maxEnergy;
        // number of selected events (events inside the range)
        int m_nValidEvents;
        // Arrays for sum of energies, sum of energy squares, energy means, and energy RMSs - for each event
        vector<double> m_energySums;
        vector<double> m_sqEnergySums;
        vector<double> m_energyMeans;
        vector<double> m_energyRMSs;
        //copy and assignment constructors (prevent shallow copy)
        BraggStatistic           ( const BraggStatistic& x );
        BraggStatistic& operator=( const BraggStatistic& x );
    public:
        // constructor and destructor
        BraggStatistic( int a_minEnergy, int a_maxEnergy );
        ~BraggStatistic();
        // non-const methods
        void AddEventUpdateSums( const Event& a_ev );
        void ComputeMeanRMS();
        // const methods (getters)
        int GetNValidEvents() const { return m_nValidEvents; } // inline implementation
        const vector<double>& GetMeans() const;
        const vector<double>& GetRMSs() const;
        // print results method
        void PrintStatisticalResults() const;
};

#endif // BRAGG_STATISTIC_H

