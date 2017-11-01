// braggPlot05
/* AnalysisFactory class implementation. This class is a factory
    that can produce analyzers objects (concrete derived classes of AnalysisSteering).
    The creation of the objects is made via static method create().
*/

#include "AnalysisFactory.h"    // implementation of
#include "AnalysisInfo.h"       // AnalysisInfo methods used

#include <string>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::pair;

// Default constructor
AnalysisFactory::AnalysisFactory()
{}

// Default destructor
AnalysisFactory::~AnalysisFactory()
{}

// Creates all requested (a_info contains the requests) analysis objects.
// (static factory production method).
vector<AnalysisSteering*> AnalysisFactory::create( const AnalysisInfo* a_info )
{
    // Vector of AnalysisSteering* to return
    vector<AnalysisSteering*> AnaList;

    // Get the unique map and point to that with the static pointer
    static map<string,Builder*>* p_bm = GetBuilderMap();

    // Loops over analysis parameters and hence makes object builders
    map<string,Builder*>::iterator iter = p_bm->begin();
    map<string,Builder*>::iterator iend = p_bm->end();
    while ( iter != iend )
    {
        // Take the pair <name,builder> in the map
        const pair<string,Builder*>& element = *iter++;

        // If the name of the object to be built is present
        // among the command line arguments, the builder builds
        // the object, and then it is storend in the analyzers vector.
        if ( a_info->contains( element.first ) )
            AnaList.push_back( element.second->build( a_info ) );
    }

    // Returns the filled vector of analyzers
    return AnaList;
}


// Add the builder and its name to the <name,builder*> map.
void AnalysisFactory::registerBuilder( const string& a_name, Builder* a_b_ptr )
{
    // Dereferences the static pointer to get the map of the builders
    static map<string,Builder*>& r_bm = *GetBuilderMap();

    // Fills the map with the given builder, giving it a key name
    r_bm[a_name] = a_b_ptr;

    return;
}


// Static map getter to associate analyzer names with corresponding builders
// The definition of the actual static map is inside the implementation of this method.
// The map is instantiated once, while this method returns the static pointer to that map.
map<string,AnalysisFactory::Builder*>* AnalysisFactory::GetBuilderMap()
{
    // Dynamically creates the map once, and point to that
    // using the static p_bm pointer.
    static map<string,Builder*>* p_bm = new map<string,Builder*>;

    // Returns the pointer
    return p_bm;
}
