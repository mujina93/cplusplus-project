// braggPlot05
/* BGCalc class definition. This class computes the
    background (= the mean energy of events from the
    100th point to the 120th point of the bragg curves).
*/

#ifndef BGCALC_H
#define BGCALC_H

#include "AnalysisSteering.h"   // Inherits from AnalysisSteering
#include "inc/ActiveObserver.h" // Inherits from ActiveObserver template

class AnalysisInfo;     // ptr used
class Event;            // ptr used


class BGCalc: public AnalysisSteering,
              public ActiveObserver<Event>
{

    public:
        // Const (taking infos), dest
        BGCalc( const AnalysisInfo* a_info );
        virtual ~BGCalc();

        // function to be called at execution start
        // Initializes members
        virtual void beginJob();
        // function to be called at execution end
        // Computes mean and rms of energies and gives a level for the background
        virtual void   endJob();
        // function to be called for each event
        // Updates sums and sum of squares
        virtual void update( const Event& a_ev );

    private:

        // Min and max energy (the background calculation
        // is done only on events whose total energy is
        // between m_minEn and m_maxEn - usually in [3000,5000])
        int m_minEn;
        int m_maxEn;
        // Point where to start and to end the calculation
        int m_startPoint;
        int m_endPoint;
        // Number of selected events for the background calculation
        int m_nSelectedEvents;
        // Sum of energies and sum of square energies for all
        // valid events and for all points from start to end
        double m_SumEnergies;
        double m_SumSqEnergies;

        // Prevent shallow cpy, =
        BGCalc           ( const BGCalc& x );
        BGCalc& operator=( const BGCalc& x );

};

#endif // BGCALC_H

