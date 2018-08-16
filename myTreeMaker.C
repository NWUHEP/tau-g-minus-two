#include "Riostream.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TFile.h"


using namespace std;

	double IDtoMass(int particleCode){
                double mass;
                if (particleCode == 2 || particleCode==3) {mass = 0.00051099907;} // electron
                else if (particleCode == 5 || particleCode==6) {mass = 0.105658389;} // muon
                else if (particleCode == 8 || particleCode==9)  {mass = 0.13956995;} // charged pion
                else if (particleCode == 7) {mass = 0.1345766;} // neutral pion
                else if (particleCode == 11|| particleCode==12) {mass = 0.493677;} // charged kaon
                else if (particleCode == 10 || particleCode == 16)  {mass = 0.497614;} // neutral kaon
                else if (particleCode == 14 || particleCode == 2212)    {mass = 0.93827231;} // proton
                else if (particleCode == 15 || particleCode == -15)    {mass = 1.7768;} // tau
		else if (particleCode == 22)    {mass = 0.0;} // gamma
		else {
                        cout << "unknown daughter particle (ID = " << particleCode << "), please modify code to accomodate" << endl;
                        mass = -1.0;
//                      exit(0); 
                     }

                return mass;
        }

void myTreeMaker(const char* outFileName = "starlight.root") {


// create output tree
        TFile* outFile = new TFile(outFileName, "RECREATE");
        if (!outFile) {
                cerr << "    error: could not create output file '" << outFileName << "'" << endl;
                return;
        }
        TTree*          outTree    = new TTree("starlightTree", "starlightTree");
        TLorentzVector* total      = new TLorentzVector();
        TLorentzVector* leading    = new TLorentzVector();
        TLorentzVector* trailing   = new TLorentzVector();
        TLorentzVector* antitau    = new TLorentzVector();
        TLorentzVector* tau   = new TLorentzVector();
	TLorentzVector* gamma1    = new TLorentzVector();
        TLorentzVector* gamma2   = new TLorentzVector();
	TLorentzVector* protonIn1    = new TLorentzVector();
        TLorentzVector* protonIn2   = new TLorentzVector();
	TLorentzVector* protonOut1    = new TLorentzVector();
        TLorentzVector* protonOut2   = new TLorentzVector();

	
        outTree->Branch("System",    "TLorentzVector", &total,    32000, -1);
        outTree->Branch("Tau",    "TLorentzVector", &tau,    32000, -1);
        outTree->Branch("AntiTau",    "TLorentzVector", &antitau,    32000, -1);
        outTree->Branch("Leading",    "TLorentzVector", &leading,    32000, -1);
        outTree->Branch("Trailing",    "TLorentzVector", &trailing,    32000, -1);
	outTree->Branch("ProtonIn1",    "TLorentzVector", &protonIn1,    32000, -1);
	outTree->Branch("ProtonIn2",    "TLorentzVector", &protonIn2,    32000, -1);
	outTree->Branch("Gamma1",    "TLorentzVector", &gamma1,    32000, -1);
	outTree->Branch("Gamma2",    "TLorentzVector", &gamma2,    32000, -1);
	outTree->Branch("ProtonOut1",    "TLorentzVector", &protonOut1,    32000, -1);
	outTree->Branch("ProtonOut2",    "TLorentzVector", &protonOut2,    32000, -1);

		
        ifstream inFile;
        inFile.open("eventsParsed.txt");
        unsigned int countLines = 0;
        while (inFile.good()) {
                total = new TLorentzVector(0, 0, 0, 0);
		int id(0);
                double px, py, pz, mass, evt;

		//read next line
		inFile >> id >> evt >> px >> py >> pz;
		//if 0 line may have been empty
		if(id == 0) { continue;}

		//check if gammas included
		if(id==2212) {
		  double pmass = IDtoMass(id);
		  double Eproton = sqrt(px*px + py*py + pz*pz + pmass*pmass);
		  protonIn1 = new TLorentzVector(px, py, pz, Eproton);
		  //fill in next particle info
		  inFile >> id >> evt >> px >> py >> pz;
		}
		if(id==2212) {
		  double pmass = IDtoMass(id);
		  double Eproton = sqrt(px*px + py*py + pz*pz + pmass*pmass);
		  protonIn2 = new TLorentzVector(px, py, pz, Eproton);
		  //fill in next particle info
		  inFile >> id >> evt >> px >> py >> pz;
		}
		
		//check if gammas included
		if(id==22) {
		  double Egamma = sqrt(px*px + py*py + pz*pz);
		  gamma1 = new TLorentzVector(px, py, pz, Egamma);
		  //fill in next particle info
		  inFile >> id >> evt >> px >> py >> pz;
		}
		if(id==22) {
		  double Egamma = sqrt(px*px + py*py + pz*pz);
		  gamma2 = new TLorentzVector(px, py, pz, Egamma);
		  //fill in next particle info
		  inFile >> id >> evt >> px >> py >> pz;
		}
		//check if gammas included
		if(id==2212) {
		  double pmass = IDtoMass(id);
		  double Eproton = sqrt(px*px + py*py + pz*pz + pmass*pmass);
		  protonOut1 = new TLorentzVector(px, py, pz, Eproton);
		  //fill in next particle info
		  inFile >> id >> evt >> px >> py >> pz;
		}
		if(id==2212) {
		  double pmass = IDtoMass(id);
		  double Eproton = sqrt(px*px + py*py + pz*pz + pmass*pmass);
		  protonOut2 = new TLorentzVector(px, py, pz, Eproton);
		  //fill in next particle info
		  inFile >> id >> evt >> px >> py >> pz;
		}

		
		int id2(0);
                double px2, py2, pz2, mass2, evt2;
		
		inFile >> id2 >> evt2 >> px2 >> py2 >> pz2;

		double E = sqrt(px*px + py*py + pz*pz + IDtoMass(id)*IDtoMass(id));
                double E2 = sqrt(px2*px2 + py2*py2 + pz2*pz2 + IDtoMass(id2)*IDtoMass(id2));


                TLorentzVector* tau1 = new TLorentzVector(px, py, pz, E);
		TLorentzVector* tau2 = new TLorentzVector(px2, py2, pz2, E2);
                *total = *tau1 + *tau2;
		//check which is the leading tau
                if(E > E2) {
			leading = tau1;
			trailing = tau2;
		} else {
			leading = tau2;
			trailing = tau1;
		}
		if(id2 < 0) {
		  antitau = tau2;
		  tau = tau1;
		} else {
		  antitau = tau1;
		  tau = tau2;
		}
                outTree->Fill();
        }

        outTree->Write();
        if (outFile) {
                outFile->Close();
                delete outFile;
        }
}
