#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TDirectory.h"
#include <iostream>
#include <fstream>
#include <sstream>

const Int_t n = 100; //max histogram sets
const Int_t N = 200; //max particles in event

TDirectory* topdir;
TDirectory* directories[n];

Int_t sets[n];
TTree* treeOut[n];
TTree* xsecOut;
TH1* drellTester;
TH1* setEvents;
TH1* setEventsN;
TH2* ptVsMass[n];
TH1* ptR[n];
TH1* ptMass[n];
TH1* massPt[n];
TH1* massH1[n];
TH1* massH2[n];
TH1* rapidityH[n];

//read into the main method
Double_t lum;

//run information read
Double_t xsec;
//particle inputs read
Int_t nevts, totalEvents;

TVector3* primaryV;
TLorentzVector* momentum1;
TLorentzVector* momentum2;
TLorentzVector* tauSys;
TLorentzVector* tau;
TLorentzVector* antitau;
Int_t pdg1;
Int_t pdg2;
UInt_t nElectrons;
UInt_t nMuons;
UInt_t nTaus;
UInt_t nJets;
Float_t iso1;
Float_t iso2;
Float_t d01;
Float_t d02;
Float_t eventWeight;
Double_t px1;
Double_t py1;
Double_t pz1;
Double_t px2;
Double_t py2;
Double_t pz2;
Double_t acoplane;
Double_t fracLossPlus;
Double_t fracLossMinus;
Double_t ptM;
Double_t ptRatio;
