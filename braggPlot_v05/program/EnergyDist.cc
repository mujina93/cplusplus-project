// braggPlot05
/* EnergyDist class implementation.
    Inherits from (and implements) AnalysisSteering abstract class.

    This file contains also the definiton and the implementation
    for the EnergyDistBuilder class. This is a concrete class that
    inherits from and implements the abstract nested
    AnalysisFactory::Builder class.
    The class EnergyDistBuilder is responsible for actually building
    an EnergyDist object, and for registering its creation to the
    AnalysisFactory (factory that creates all the analyzers with the
    call to the static method create()).
*/

#include "EnergyDist.h"     // Implements EnergyDist class
#include "BraggStatistic.h" // Creates BraggStatistic objects
#include <vector>           // Uses vector methods
#include <iostream>         // cout, cin, endl used
#include "TH1F.h"			// TH1F used
#include <string>			// string used
#include "constants.h"		// g_Min_Points is used
#include "TDirectory.h"     // TDirectory used
#include "TFile.h"          // TFile used
#include "AnalysisSteering.h" // constructor called
#include "AnalysisInfo.h"   // AnalysisInfo used
#include "AnalysisFactory.h" // AnalysisFactory::Builder implemented
#include <fstream>          // fstream used
#include "TotalEnergy.h"    // static method used
#include "bkgconstants.h"   // static constants used

// Intermediate builder class to create an EnergyDist analyzer
// This class implements the abstract nested Builder class
// that is defined inside AnalysisFactory
class EnergyDistBuilder: public AnalysisFactory::Builder
{
    public:
        // Creates the builder object, assign "dist" as
        // name for this analyzer and builder
        EnergyDistBuilder():
            AnalysisFactory::Builder( "dist" )
        {}

        // The AnalysisFactory will make the builder use
        // this method when it wants an EnergyDist to be created.
        virtual AnalysisSteering* build( const AnalysisInfo* a_info )
        {
            // Dynamically creates an EnergyDist object, if the infos require it
            return new EnergyDist( a_info );
        }
};

// Create a global EnergyDistBuilder, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EnergyDistBuilder will be available with name "dump".
static EnergyDistBuilder EnDiBuilder;


// This constructor calls the base constructor
// and gives it the infos about what to build.
// Reads and stores the energy ranges from a file.
// Instantiates the histogram of total energies.
EnergyDist::EnergyDist( const AnalysisInfo* a_info ):
    AnalysisSteering( a_info )
{
}

// Implemented (ex-virtual) destructor
EnergyDist::~EnergyDist()
{
    // Deallocate dynamic memory allocated by the pointers in the vector member
    for (BraCurvePtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        delete (*it);
    }
    m_vBraggCurvePtrs.clear();
    delete m_pTotEnHist;
}

// Allocates N BraggCurve objects (1 for each range of energy)
void EnergyDist::beginJob()
{

    using std::ifstream;
    using std::ios;
    using std::string;
    using std::cout;
    using std::endl;

    // If "ranges" was prompted in command line at the execution...
    if(m_AnaInfo->contains("ranges"))
    {
        // Get file name from infos
        // (its the word after the key "ranges" given in command line
        string filename = m_AnaInfo->value("ranges");
        ifstream iRangeFile(filename.c_str(), ios::in);

        // Reads labels and ranges
        int label;
        int min_value;
        int max_value;
        do
        {
            iRangeFile >> label >> min_value >> max_value;

            // Dynamically creates the BraggCurves and store their pointers in the vector.
            // Use the read (from file energyRanges) ranges for the BraggCurves creation.
            if(!iRangeFile.eof())
            {
                bCreate(label, min_value, max_value);
            }
        }while(!iRangeFile.eof());

        // Closes file
        iRangeFile.close();
    } else
    {
        cout << "[\"ranges\" option missing] No file for the ranges was specified." << endl;
        cout << "No statistical computation will be made." << endl << endl;
    }

    // Histogram of total energies
    m_pTotEnHist = new TH1F("totalEnergies",
                            "totalEnergies",
                            100, //bins
                            0, //min tot energy
                            10000); //max tot energy

    return;
}

// Compute Mean and RMSs for each BraggCurve object
// then saves data in histograms (.root files)
void EnergyDist::endJob()
{
	using std::cout;
	using std::endl;

	// Variables for choosing the file where to save
	int j = 0;
	// The first part of the name for the files
    // is the token that
    // was given as input after the word "dist"
    // in command line.
    string token_name = m_AnaInfo->value("dist");

    // Loop over the vector and do things
    for (BraCurvePtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
		// Compute means and RMSs
        (*it)->m_pBraggStat->ComputeMeanRMS();

        // Set bin contents and errors using the means and the RMSs
        for(int i=1; i <= g_Min_Points; i++)
		{
			double en = (*it)->m_pBraggStat->GetMeans().at(i-1);
			double er = (*it)->m_pBraggStat->GetRMSs().at(i-1);
			(*it)->m_pHist->SetBinContent(i,en);
			(*it)->m_pHist->SetBinError(i,er);
		}

		// Save histograms on separate files
		// The first part of the name for the files
		// is the token that
		// was given as input after the word "dist"
		// in command line.
		string name = token_name;
		switch(j)
		{
			case 0:
				name += "Background";
				break;
			case 1:
				name += "Africium";
				break;
			case 2:
				name += "Asium";
				break;
			case 3:
				name += "Australium";
				break;
			default:
				name += "???";
		}
		name += ".root";
		TDirectory* currentDir = gDirectory;
		TFile* file = new TFile(name.c_str(),"RECREATE");
		(*it)->m_pHist->Write();
		file->Close();
		currentDir->cd();
		j++;

		// Inform about the saved file
		cout << "A histogram with energy means was saved in the file ";
		cout << name << " (using RECREATE mode)" << endl;
    }


	// Save histogram of total energies
    TDirectory* currentDir = gDirectory;
	currentDir = gDirectory;
	string totEnName = token_name + "TotalEnergies.root";
	TFile* totEnFile = new TFile(totEnName.c_str(),"RECREATE");
	m_pTotEnHist->Write();
	totEnFile->Close();
	currentDir->cd();

	// Inform about the total energies histogram
	cout << "The histogram with total energies of all events (bkg subtracted) ";
	cout << "was saved in the file " << totEnName << " (using RECREATE mode)" << endl;


    // Save on unique file
    string unique_name = token_name + "Hists.root";
    TFile* uni_file = new TFile(unique_name.c_str(),"RECREATE");
    for (BraCurvePtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        (*it)->m_pHist->Write();
    }
    m_pTotEnHist->Write();
    uni_file->Close();
    currentDir->cd();

    // Inform about the unique file
    cout << "All the histograms were saved in the file ";
    cout << unique_name << " (using RECREATE mode)" << endl;


	// Prints statistical results on the screen
	PrintResults();

    return;
}

// Observer update method:
// Method that takes an event and updates the right BraStat objects
// (correct energy range) with its energy values.
// It also updates the histogram of total energies.
void EnergyDist::update( const Event& a_ev )
{
    // Loop over the vector and add try to add the event data to each object
    for (BraCurvePtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        (*it)->m_pBraggStat->AddEventUpdateSums(a_ev);
    }


    // Retrieves the total energy for the given event, and stores it into the histogram:

    // Call the static instance() function of TotalEnergy.
    // By calling this function, the singleton static instance of TotalEnergy
    // is created (the function instance() creates the object).
    // A pointer to the singleton is returned.
    TotalEnergy* p_TE = TotalEnergy::instance();
    // Get now total energy from the TotalEnergy object
    // (since TotalEnergy is a lazy object, it will update its
    // state now, and compute the total now, for the first time)
    // Here we get the total energy with background level subtracted.
    int totEn = p_TE->GetEnergySum();

    // Fill histogram with one value of tot energy (bkg subtracted)
    m_pTotEnHist->Fill(totEn);

    return;
}

// Method that prints statistical results in a good-looking format
void EnergyDist::PrintResults()
{
    using std::cout;
    using std::cin;
    using std::endl;

    for (BraCurvePtrVec::iterator it = m_vBraggCurvePtrs.begin() ;
            it != m_vBraggCurvePtrs.end();
            ++it)
    {
        cout << "Press Enter to display (more) statistical output" << endl;
        cin.get();
        (*it)->m_pBraggStat->PrintStatisticalResults();
    }

    return;
}

// Method that creates a BraggCurve object
void EnergyDist::bCreate( int a_id, float a_minEn, float a_maxEn )
{
	// Makes file name
	using std::string;
	using std::to_string;

	string index = to_string(a_id);
	string hname = "hMeas" + index;

	// Create histogram
	TH1F* h = new TH1F(hname.c_str(),
						hname.c_str(),
						g_Min_Points,
						0,
						g_Min_Points);

	// Create BraggStatistic for the right range
	BraggStatistic* bs = new BraggStatistic(a_minEn, a_maxEn);

	// Store BraggStatistic and Histogram in a BraggCurve
	BraggCurve* p_bCurve = new BraggCurve{0,0};
	p_bCurve->m_pBraggStat = bs;
	p_bCurve->m_pHist = h;

	// Store BraggCurve*
	m_vBraggCurvePtrs.push_back(p_bCurve);

	return;
}

