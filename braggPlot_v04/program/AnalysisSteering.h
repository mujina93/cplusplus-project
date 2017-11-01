// braggPlot04
/* AnalysisSteering abstract class definition.
    Interface class. Blueprint for data analysis classes.
*/

#ifndef ANALYSISSTEERING_H
#define ANALYSISSTEERING_H

class Event;    // Event& used as function parameter
class AnalysisInfo; // AnalysisInfo* used as function parameter


class AnalysisSteering
{
    public:
        // Constructor and virtual destructor
        AnalysisSteering(const AnalysisInfo* a_info);
        virtual ~AnalysisSteering();

        // Abstract function to be called at execution start
        virtual void beginJob() = 0;
        // Abstract function to be called at execution end
        virtual void endJob() = 0;

    protected:
        //
        const AnalysisInfo* m_AnaInfo;

    private:
        // Copy constructor and assignment, prevent shallow copy
        AnalysisSteering( const AnalysisSteering& x );
        AnalysisSteering& operator=( const AnalysisSteering& x );
};

#endif // ANALYSISSTEERING_H

