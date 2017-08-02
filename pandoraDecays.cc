#include "Pythia8/Pythia.h"
#include <stdlib.h>
using namespace Pythia8;

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

  //Histograms of relevant information
  Hist TauPt("Tau Pt",100,-0.1, 6.0);
  Hist TauEta("Tau Eta",100,-9.0, 9.0);
  Hist TauPtLeading("Leading Tau Pt",100,-0.1, 6.0);
  Hist TauPtTrailing("TrailingTau Pt",100,-0.1, 6.0);

  pythia.init();

  //number of of events to print
  int nPrintLHA  = 10;
  int iPrintLHA  = 0;

  //Detector cuts
  double maxEta = 2.4;
  double minPt = 0.0;

  //for measuring acceptance
  int events = 0;
  int acceptedEvents = 0;

  // Begin event loop
  for (int iEvent = 0; ; ++iEvent) {

    // Generate until none left in input file.
    if (!pythia.next()) {
      if (pythia.info.atEndOfFile()) {
        cout << "end at iEvent " << iEvent << endl;
        break;
      }
//     continue;
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
      TauPt.fill(t1.pT());
      TauPt.fill(t2.pT());
      TauEta.fill(t1.eta());
      TauEta.fill(t2.eta());
      if(t1.pT() > t2.pT()) { //check which is leading tau
        TauPtLeading.fill(t1.pT());
        TauPtTrailing.fill(t2.pT());
      } else {
        TauPtLeading.fill(t2.pT());
        TauPtTrailing.fill(t1.pT());
      }

      bool accept = true;      
      vector<int> tDaughters1 = pythia.event[5].daughterListRecursive();
      int nDecays1 = tDaughters1.size();
      for(int iDecay = 0; iDecay < nDecays1; iDecay++) {
        Particle pDecay = pythia.event[tDaughters1[iDecay]];
        if(pDecay.isFinal() && abs(pDecay.id()) != 12 && abs(pDecay.id()) != 14 && abs(pDecay.id()) != 16) { //only get the final daughters, and print some info
          accept = accept && abs(pDecay.eta()) < maxEta && pDecay.pT() > minPt;
        }
        if(!accept) break;
      }

      vector<int> tDaughters2 = pythia.event[6].daughterListRecursive();
      int nDecays2 = tDaughters2.size();
      for(int iDecay = 0; iDecay < nDecays2; iDecay++) {
        Particle pDecay = pythia.event[tDaughters2[iDecay]];
        if(pDecay.isFinal() && abs(pDecay.id()) != 12 && abs(pDecay.id()) != 14 && abs(pDecay.id()) != 16) { //only get the final daughters, and print some info
          accept = accept && abs(pDecay.eta()) < maxEta && pDecay.pT() > minPt;
        }
        if(!accept) break;
      }

      if(accept) acceptedEvents++;
      events++;
      //if event passes pt/eta cuts, accept it
 //     if(t1.pT() > minPt && t2.pT() > minPt && abs(t1.eta()) < maxEta && abs(t2.theta()) < maxEta) acceptedEvents++;
    } else if(!pythia.info.isLHA()) {
      continue;
    }


  // End of event loop.
  }

  // Give statistics. Print histograms and acceptance.
  pythia.stat();
  cout << TauPt << TauEta << TauPtLeading << TauPtTrailing;
  printf(" Of %d events, %d were accepted, so acceptance of %f\n",events,acceptedEvents,((double) acceptedEvents) / events);

//make tables to plot info
  return 0;
}
