// braggMean02
/* Definition of Event class.
    This class can store an array of energy (data for 1 Bragg curve)
*/

// Include Guards
#ifndef EVENT_H
#define EVENT_H

class Event
{
    private:
        // min and max number of measurements
        static int m_nMeasMax;
        static int m_nMeasMin;
        // event ID
        int m_evID;
        // # of measures
        int m_nMeasures;
        // array of ints (to store energy losses values)
        int* m_energies;
    public:
        // constructor and destructor
        Event(int a_evID);
        ~Event();
        // copy constructor and assignment operator for deep copy
        Event& operator=(const Event& a_ev);
        Event(const Event& a_ev);
        // non-const methods
        void AddEnergy(const int& a_energy);
        // const methods (getters)
        int GetEventID() const;
        int GetDataSize() const;
        int GetIthEnergy(const int& a_id) const;
        int GetMaxSize() const;
        int GetMinSize() const;
};

#endif // EVENT_H

