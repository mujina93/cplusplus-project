// braggPlot05
/* Definition of static members of class BKGConstants.
    The values for bgMean and bgRMS are the mean and
    rms of background calculation found in the execution
    of the previous version of this program.
    (Program braggPlot04, values computed and printed
    by BGCalc class, execution of the program done via:
    ./execName input bragg_events.txt bgcalc ).
*/

#include "bkgconstants.h"   // definition of static members

// background mean and rms
const float BKGConstants::bgMean = 12.3978;
const float BKGConstants::bgRMS  = 1.05528;

