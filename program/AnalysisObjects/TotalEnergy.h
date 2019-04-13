// braggPlot06
/* TotalEnergy class definition.
    This class is a singleton, and it is a lazy observer
    of Events. (updates only when checked with data coming
    from events' notifications).
*/

#ifndef TOTAL_ENERGY_H
#define TOTAL_ENERGY_H

#include "inc/Singleton.h"      // Inherits from
#include "inc/LazyObserver.h"   // Inherits from
#include "Event.h"              // Used in template


class TotalEnergy: public Singleton<TotalEnergy>,
                   public LazyObserver<Event>
{
    // Singleton class is able to manipulate TotalEnergy private members
    friend class Singleton<TotalEnergy>;

    public:

        // Function to be called when a new event arrives
        virtual void update( const Event& a_ev );

        // Sum of measurements, no background subtraction
        double GetRawSum();

        // Sum of measurements, with background subtraction
        double GetEnergySum();

    private:

        // Raw sum of energy for an event (no bkg subtraction)
        double m_RawSum;
        // Sum of energy with background subtraction
        double m_EnergySum;

        // Prevents creation, destruction, copy, assignment
        TotalEnergy();
        ~TotalEnergy();
        TotalEnergy           ( const TotalEnergy& x );
        TotalEnergy& operator=( const TotalEnergy& x );

};

#endif // TOTAL_ENERGY_H

