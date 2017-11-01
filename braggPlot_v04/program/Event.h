// braggPlot04
/* Definition of Event class.
    This class can store an array of energy (data for 1 Bragg curve)
*/

// Include Guards
#ifndef EVENT_H
#define EVENT_H

#include <vector>
using std::vector;

class Event
{
    private:
        // min and max number of measurements
        static int m_nMeasMax;
        static int m_nMeasMin;
        // event ID
        int m_evID;
        // vectors of ints (to store energy losses values)
        vector<int> m_energies;
    public:
        // constructor and destructor
        Event(int a_evID);
        ~Event();

        // non-const methods
        void AddEnergy(const int& a_energy);
        // const methods (getters)
        int GetEventID() const;
        int GetDataSize() const;
        int GetIthEnergy(const int& a_id) const;

        // static getters
        static int GetMaxSize();
        static int GetMinSize();
};

#endif // EVENT_H

