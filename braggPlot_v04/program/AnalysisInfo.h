// braggPlot04
/* AnalysisInfo class definition. This class manages the arguments given
    in input in the command line.
*/

#ifndef ANALYSIS_INFO_H
#define ANALYSIS_INFO_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class AnalysisInfo
{
    public:
        // Constructor that resambles main() function
        AnalysisInfo( int argc, char* argv[] );
        // Default destructor
        ~AnalysisInfo();

        // Gets the list of all words
        const vector<string>& argList() const;

        // Gets the word coming after the word 'key'
        const string& value( const string& a_key ) const;

        // Checks if the word 'key' is present
        bool contains( const string& a_key ) const;

    private:

        // Container for arguments
        vector<string> m_args;

        // Default value to return for keys not found
        static string m_defaultString;

        // Prevents shallow copy and assignment
        AnalysisInfo           ( const AnalysisInfo& x );
        AnalysisInfo& operator=( const AnalysisInfo& x );

};

#endif // ANALYSIS_INFO_H

