#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"
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
TH2* ptVsMass[n];
TH1* ptMass[n];
TH1* massPt[n];
TH1* massH1[n];
TH1* massH2[n];
TH1* rapidityH[n];

//read into the main method
Double_t lum;

//run information read
Double_t sqrtS,xsec, errxsec;
//particle inputs read
Double_t pt[N],en[N],eta[N],phi[N],rapidity[N],charge[N];
Int_t partid[N], parent1[N], parent2[N], status[N];
Int_t nevts;

TLorentzVector* tauSys;
TLorentzVector* gammaSys;
TLorentzVector* tau;
TLorentzVector* antitau;
TLorentzVector* gamma1;
TLorentzVector* gamma2;
TLorentzVector* proton1;
TLorentzVector* proton2;
Int_t partidOut[N];
Int_t parent1Out[N];
Int_t parent2Out[N];
Int_t statusOut[N];
Double_t px[N];
Double_t py[N];
Double_t pz[N];
Int_t np;
Int_t npOut;
Double_t acoplane;
Double_t fracLossPlus;
Double_t fracLossMinus;
Double_t ptM;
