// braggPlot02
/* AnalysisInfo class implementation. This class provides code useful to
    manage input arguments.
*/

#include "AnalysisInfo.h"

using std::vector;
using std::string;

// Default value to return for keys not found (initialization of static member)
string AnalysisInfo::m_defaultString = "";

// Constructor
AnalysisInfo::AnalysisInfo( int argc, char* argv[] )
{
    // Resizes the internal vector to make it big enough
    m_args.resize( argc );
    // Stores the arguments given in command line after the executable name
    for ( int i = 1; i < argc; ++i )
        m_args[i] = argv[i];
}

// Default destructor
AnalysisInfo::~AnalysisInfo()
{}


// Gets the list of arguments
const vector<string>& AnalysisInfo::argList() const
{
    return m_args;
}


// Gets the word coming after the word 'key'
const string& AnalysisInfo::value( const string& a_key ) const
{
    // Loop over words
    int i = 0;
    int n = m_args.size();
    while ( i < n )
    {
        // If word is equal to key, return next word
        if ( m_args[i++] == a_key )
            return m_args[i];
    }

    // If key not found, return a default string
    return m_defaultString;
}


// Checks if the word 'key' is present
bool AnalysisInfo::contains( const string& a_key ) const
{
    // Loops over words
    int i = 0;
    int n = m_args.size();
    while ( i < n )
    {
        // If word is equal to key, return true
        if ( m_args[i++] == a_key )
            return true;
    }

    // If key not found, return false
    return false;
}

