// braggPlot06
/* AnalysisSteering abstract class definition.
    Interface class. Blueprint for data analysis classes.
    AnalysisSteering is now an ActiveObserver of AnalysisInfo::status.
*/

#ifndef ANALYSISSTEERING_H
#define ANALYSISSTEERING_H


#include "inc/ActiveObserver.h" // inherits from
#include "AnalysisInfo.h"       // used in template inheritance

class Event;    // Event& used as function parameter
class AnalysisInfo; // AnalysisInfo* used as function parameter



class AnalysisSteering : public ActiveObserver<AnalysisInfo::AnalysisStatus>
{
    public:
        // Constructor and virtual destructor
        AnalysisSteering(const AnalysisInfo* a_info);
        virtual ~AnalysisSteering();

        // Function to be called when a notification arrives (at execution start/end)
        virtual void update( const AnalysisInfo::AnalysisStatus& a_status );

    protected:
        // Internal infos
        const AnalysisInfo* m_AnaInfo;

    private:
        // Abstract function to be called at execution start
        virtual void beginJob() = 0;
        // Abstract function to be called at execution end
        virtual void endJob() = 0;

        // Copy constructor and assignment, prevent shallow copy
        AnalysisSteering( const AnalysisSteering& x );
        AnalysisSteering& operator=( const AnalysisSteering& x );
};

#endif // ANALYSISSTEERING_H

