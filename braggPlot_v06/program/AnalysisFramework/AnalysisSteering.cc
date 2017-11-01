// braggPlot06
/* AnalysisSteering abstract class implementation
    Interface class. Blueprint for data analysis classes.
*/

#include "AnalysisSteering.h"   // AnalysisSteering implementation
#include "AnalysisInfo.h"       // enum types and pointers used

// Constructor. The inner protected AnalysisInfo* is initialized
AnalysisSteering::AnalysisSteering( const AnalysisInfo* a_info ):
    m_AnaInfo(a_info)
{}

// Default virtual constructor
AnalysisSteering::~AnalysisSteering()
{}

// Function to be called when a notification arrives (at execution start/end)
void AnalysisSteering::update( const AnalysisInfo::AnalysisStatus& a_status )
{
    switch(a_status)
    {
        // If the notification is the enumeration type "begin", then run beginJob()
        case AnalysisInfo::begin:
            beginJob();
            break;

        // If the notification is the enumeration type "end", then run endJob()
        case AnalysisInfo::end:
            endJob();
            break;
    }

    return;
}
