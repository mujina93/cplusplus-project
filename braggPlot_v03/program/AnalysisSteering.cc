// braggPlot03
/* AnalysisSteering abstract class implementation
    Interface class. Blueprint for data analysis classes.
*/

#include "AnalysisSteering.h"   // AnalysisSteering implementation

// Constructor. The inner protected AnalysisInfo* is initialized
AnalysisSteering::AnalysisSteering( const AnalysisInfo* a_info ):
    m_AnaInfo(a_info)
{}

// Default virtual constructor
AnalysisSteering::~AnalysisSteering()
{}
