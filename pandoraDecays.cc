#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TFile.h"
#include <stdlib.h>
using namespace Pythia8;

//Root Histograms of relevant information
TH1F TauPtRoot("Tau Pt","Tau Pt Distribution",100,-0.1, 6.0);
TH1F TauEtaRoot("Tau Eta","Tau Eta Distribution",100,-9.0, 9.0);
TH1F TauPhiRoot("Tau Phi","Tau Phi Distribution",100,-3.141, 3.141);
TH1F TauEnergyRoot("Tau Energy","Tau Energy Distribution",200,0.0, 6.0);
TH1F TauAngleDiffRoot("Tau Angles", "Tau Separation Angle Distribution",200,-10, 3341.0);
TH1F TauPtDiffRoot("Tau Pt Difference","Tau Pt Difference Distribution",200,-0.1, .03);
TH1F TauEnergyDiffRoot("Tau Energy Difference","Tau Energy Difference Distribution",300,-0.1, 3.0);

//Histograms of relevant information
Hist TauPt("Tau Pt",100,-0.1, 6.0);
Hist TauEta("Tau Eta",100,-9.0, 9.0);
Hist TauPtLeading("Leading Tau Pt",100,-0.1, 6.0);
Hist TauPtTrailing("TrailingTau Pt",100,-0.1, 6.0);
Hist TauPhi("Tau Phi",100,-3.141, 3.141);
Hist TauEnergy("Tau Energy",200,0.0, 6.0);
Hist TauAngleDiff("Tau Angle Difference in mrad",200,-10, 3341.0);
Hist TauPtDiff("Tau Pt Difference",200,-0.1, .03);
Hist TauEnergyDiff("Tau Energy Difference",300,-0.1, 3.0);


//check if non-neutrino tau final daughters are within detector
bool daughterCheck(vector<int> & tDaughters, Pythia & pythia, double maxEta, double minPt) {
  //assume initially true
  bool accept = true;
  int nDecays = tDaughters.size();
  for(int iDecay = 0; iDecay < nDecays; iDecay++) {
    Particle pDecay = pythia.event[tDaughters[iDecay]];
    //check if it is a non-neutrino final particle
    if(pDecay.isFinal() && abs(pDecay.id()) != 12 && abs(pDecay.id()) != 14 && abs(pDecay.id()) != 16) {
      //check eta and pt against requirements
      accept = accept && abs(pDecay.eta()) < maxEta && pDecay.pT() > minPt;
    }
    //if ever false, return false
    if(!accept) return accept;
  }
  //return true if passes
  return accept;
}

//add kinematics to histograms
void addProperties(Particle & t) {
  TauPt.fill(t.pT());
  TauPhi.fill(t.phi());
  TauEta.fill(t.eta());
  TauEnergy.fill(t.e());

  TauPtRoot.Fill(t.pT());
  TauPhiRoot.Fill(t.phi());
  TauEtaRoot.Fill(t.eta());
  TauEnergyRoot.Fill(t.e());
}

//add non-neutrino final daughters to histograms
void addDaughters(vector<int> & tDaughters, Pythia & pythia) {
  int nDecays = tDaughters.size();
  for(int iDecay = 0; iDecay < nDecays; iDecay++) {
    Particle pDecay = pythia.event[tDaughters[iDecay]];
    //if it is an final non-neutrino, add to each histogram
    if(pDecay.isFinal() && abs(pDecay.id()) != 12 && abs(pDecay.id()) != 14 && abs(pDecay.id()) != 16) {
      addProperties(pDecay);
    }
  }
}


int main() {

  //Initialize Pythia settings, in Pythia object pythia
  Pythia pythia;
  pythia.readString("ProcessLevel:all = on");
  pythia.readString("ProcessLevel:resonanceDecays = on");
  pythia.readString("Beams:LHEF = pandoraTaus.lhe");
  pythia.readString("Next:numberShowLHA = 0");
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 1");
  pythia.readString("Beams:frameType = 4");

  //create file to write root plots to
  TFile* outFile = new TFile("eeTauDaughtersEta_2_4.root","RECREATE");

  //initialize
  pythia.init();

  //number of of events to print
  int nPrintLHA  = 10;
  int iPrintLHA  = 0;

  //Detector cuts
  double maxEta = 2.4;
  double minPt = -0.1;

  //for measuring acceptance
  int events = 0;
  int acceptedEvents = 0;

  // Begin event loop
  for (int iEvent = 0; ; ++iEvent) {

    // Generate until none left in input file.
    if (!pythia.next() && pythia.info.atEndOfFile()) {
      cout << "end at iEvent " << iEvent << endl;
      break;
    }

    // List first few Les Houches events.
    if (pythia.info.isLHA() && iPrintLHA < nPrintLHA) {
      cout << "LHA event list\n";
      pythia.LHAeventList();
      pythia.event.list();  

      //get the final daughters for each tau  
      vector<int> tDaughters1 = pythia.event[5].daughterListRecursive();
      int nDecays1 = tDaughters1.size();
      cout << "Tau 1 Final Decay Products:\n";
      for(int iDecay = 0; iDecay < nDecays1; iDecay++) {
        Particle pDecay = pythia.event[tDaughters1[iDecay]];
        if(pDecay.isFinal()) { //only get the final daughters, and print some info
          cout << iDecay << " " << pDecay.name() << " Pt: " << pDecay.pT() << " Eta: " << pDecay.eta() << "\n";
        }

      }
      cout << endl;

      vector<int> tDaughters2 = pythia.event[6].daughterListRecursive();
      int nDecays2 = tDaughters2.size();
      cout << "Tau 2 Final Decay Products:\n";
      for(int iDecay = 0; iDecay < nDecays2; iDecay++) {
        Particle pDecay = pythia.event[tDaughters2[iDecay]];
        if(pDecay.isFinal()) {
          cout << iDecay << " " << pDecay.name() << " Pt: " << pDecay.pT() << " Eta: " << pDecay.eta() << " Energy: " << pDecay.e() << endl;
        }

      }
      cout << endl;
      iPrintLHA++;
    }
    //get tau info for all events, not just ones being printed
    if(pythia.info.isLHA()) {
      Particle t1 = pythia.event[5]; // tau 1
      Particle t2 = pythia.event[6]; // tau 2
      //switching between plotting taus and plotting tau daughters
      if(false) {
        if(abs(t1.eta()) < maxEta && abs(t2.eta()) < maxEta) {
              //add basic kinematic properties to histograms
              addProperties(t1); addProperties(t2);

              //cos(angle) between 2 vectors = t1 dot t2 / |t1| |t2|
              double t1DotT2 = (t1.px()*t2.px()+t1.py()*t2.py()+t1.pz()*t2.pz());
              double t1Mag = sqrt(t1.px()*t1.px()+t1.py()*t1.py()+t1.pz()*t1.pz());
              double t2Mag = sqrt(t2.px()*t2.px()+t2.py()*t2.py()+t2.pz()*t2.pz());
	      double angle = 1000*acos(t1DotT2/(t1Mag*t2Mag));

              //add differences between two taus
	      TauPtDiff.fill(abs(t1.pT()-t2.pT()));
	      TauEnergyDiff.fill(abs(t1.e()-t2.e()));
	      TauAngleDiff.fill(abs(angle));

	      TauEnergyDiffRoot.Fill(abs(t1.e()-t2.e()));
	      TauPtDiffRoot.Fill(abs(t1.pT()-t2.pT()));
	      TauAngleDiffRoot.Fill(abs(angle));
        }
      } else {
        vector<int> tDaughters1 = t1.daughterListRecursive();
        bool accept = daughterCheck(tDaughters1, pythia, maxEta, minPt);

        vector<int> tDaughters2 = t2.daughterListRecursive();
        accept = accept && daughterCheck(tDaughters2, pythia, maxEta, minPt);

        if(abs(t1.eta()) < maxEta && abs(t2.eta()) < maxEta) acceptedEvents++;
        events++;

        if(accept) {
	  vector<int> tDaughters = t1.daughterListRecursive();
          addDaughters(tDaughters, pythia);
	  tDaughters = t2.daughterListRecursive();
          addDaughters(tDaughters, pythia);
        }
      }
    } else if(!pythia.info.isLHA()) {
      continue;
    }

  // End of event loop.
  }


  // Give statistics. Print histograms and acceptance.
  pythia.stat();
  cout << TauPt << TauEta << TauPhi << TauEnergy << TauPtDiff << TauEnergyDiff << TauAngleDiff;
  printf(" Of %d events, %d were accepted, so acceptance of %f\n",events,acceptedEvents,((double) acceptedEvents) / events);

//make tables to plot info
//  TauPt.table("eeTauPt"); TauEta.table("eeTauEta"); TauPhi.table("eeTauPhi"); TauEnergy.table("eeTauEnergy");
//  TauPtDiff.table("eeTauPtDiff"); TauEnergyDiff.table("eeTauEnergyDiff"); TauAngleDiff.table("eeTauAngleDiff");

  //write root plots to outfile
  TauPtRoot.Write();
  TauEnergyRoot.Write();
  TauPhiRoot.Write();
  TauEtaRoot.Write();

  TauEnergyDiffRoot.Write();
  TauPtDiffRoot.Write();
  TauAngleDiffRoot.Write();

  delete outFile;


  return 0;
}






