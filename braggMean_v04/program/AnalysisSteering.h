// braggMean04
/* AnalysisSteering abstract class definition.
    Interface class. Blueprint for data analysis classes.
*/

#ifndef ANALYSISSTEERING_H
#define ANALYSISSTEERING_H

class Event;    // Event& used as function parameter


class AnalysisSteering
{
    public:
        // Constructor and virtual destructor
        AnalysisSteering(){}
        virtual ~AnalysisSteering(){}

        // Abstract function to be called at execution start
        virtual void beginJob() = 0;
        // Abstract function to be called at execution end
        virtual void endJob() = 0;
        // Abstract function to be called for each event (it should dump event's data)
        virtual void process( const Event& a_ev ) = 0;

    private:
        // Copy constructor and assignment, prevent shallow copy
        AnalysisSteering( const AnalysisSteering& x );
        AnalysisSteering& operator=( const AnalysisSteering& x );
};

#endif // ANALYSISSTEERING_H

