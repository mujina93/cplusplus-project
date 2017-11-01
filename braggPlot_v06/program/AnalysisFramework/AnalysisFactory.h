// braggPlot06
/* AnalysisFactory class definition. This class is a factory
    that can produce analyzers objects (concrete derived classes of AnalysisSteering).
    The creation of the objects is made via static method create().
*/

#ifndef ANALYSIS_FACTORY_H
#define ANALYSIS_FACTORY_H

#include <string>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::map;

class AnalysisSteering;     // AnalysisSteering* used
class AnalysisInfo;         // AnalysisInfo* used

class AnalysisFactory
{
    public:
        // Const., dest.
        AnalysisFactory();
        virtual ~AnalysisFactory();

        // Creates all requested (a_info contains the requests) analysis objects.
        // (static factory production method).
        static vector<AnalysisSteering*> create( const AnalysisInfo* a_info );

        // Analysis object builder ( it's not a "builder" in the design pattern sense,
        // it's actually an abstract factory )
        class Builder {
            public:
                // Analyzers are registered with a name so that they are actually
                // created only if, at runtime, their name is listed in the command line
                Builder( const string& a_name )
                    { registerBuilder( a_name, this ); }

                // Virtual destructor
                virtual ~Builder() {}

                // Build abstract method - the builder builds the object it's made to build
                virtual AnalysisSteering* build( const AnalysisInfo* a_info ) = 0;
        };

    private:
        // Prevents shallow copy and =
        AnalysisFactory           ( const AnalysisFactory& x );
        AnalysisFactory& operator=( const AnalysisFactory& x );

        // Function to add analyzer builders to the factory
        static void registerBuilder( const string& a_name, Builder* a_b_ptr );

        // Static map getter to associate analyzer names with corresponding builders
        // The definition of the actual static map is inside the implementation of this method.
        // The map is instantiated once, while this method returns the static pointer to that map.
        static map<string,Builder*>* GetBuilderMap();
};

#endif // ANALYSIS_FACTORY_H

