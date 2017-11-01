// braggPlot05
/* SourceFactory class definition. This class is a factory
    that creates other objects (the event sources).
*/

#ifndef SOURCE_FACTORY_H
#define SOURCE_FACTORY_H

class EventSource;      // ptr used
class AnalysisInfo;     // ptr used


class SourceFactory
{
public:
    // Default const. and dest.
    SourceFactory();
    virtual ~SourceFactory();

    // Creates event source
    static EventSource* create( const AnalysisInfo* a_info );

private:

    // Prevent shallow copy and =
    SourceFactory           ( const SourceFactory& x );
    SourceFactory& operator=( const SourceFactory& x );

};

#endif // SOURCE_FACTORY_H

