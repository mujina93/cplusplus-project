# Bragg Curve
C++ & ROOT (CERN data analysis framework) project for statistics computation and visualization of particle Physics data.

*Author: Michele Piccolini*

*Program version: braggPlot06*

## Compile
Execute the script "compile" with 
	
	./path/to/compile


The source files will be compiled into different dynamic libraries. The compilation will output several executables: `runAll`, `runDist`, `runBGCalc`, `runDump`.

In order to be able to run the files, make sure that the **data files**
`bragg_events.txt` and `energyRanges` are  in the same directory as the exectutables.

Make also sure the environment variable `LD_LIBRARY_PATH` is set. To set it, enter the last command printed out by the run of "compile". Something of the form

	export LD_LIBRARY_PATH=${ANALYSIS_PATH}


## Run
There will be 4 executables that can be run, each doing different things.

* **runDist** 
	Exe that supports only the option "dump", useful to print
data. Run with: 

		./runDump input bragg_events.txt dump

	Or with: 
	

 		./runDump sim <numberOfEvents> [seed] dump


* **runBGCalc** 
	Exe that supports only the option "bgcalc", useful to compute
the background energy level. Run with: 

	    ./runBGCalc input bragg_events.txt bgcalc

	Or with: 

		./runBGCalc sim <numberOfEvents> [seed] bgcalc

* **runDist** 
	Exe that supports only the option "dist <token_name>", useful to 
make statistics and to save histograms (.root files).

	The <token_name> can be any string. This will be the initial part of the names of the saved histograms. For example, if you type "dist h", the program will save the histograms: hBackground.root,hAfricium.root, hAustralium.root, hAsium.root, hHists.root, and hTotalEnergies.root. Do not insert token names as "h.root". "h" is enough.
	
	You must include also the option "ranges energyRanges" in this case, in order to make the program know where to read the energy ranges with which perform the statistics.
	
	Run with: 

		./runDump input bragg_events.txt ranges energyRanges dist <token_name>
	
	Or with: 
	
		./runDump sim <numberOfEvents> [seed] ranges energyRanges dist <token_name>

* **runAll** 
	Exe with all functionalities.
	
	Run by typing at least one input option (i.e. "input bragg_events.txt"
or "sim <numberOfEvents> [seed]").

	Run by inserting in command line any combination of options, among: "dump", "dist <token_name>", and "bgcalc".
	
	Remember to insert in the command line options the option "ranges energyRanges", if you chosed to include "dist <token_name>".
