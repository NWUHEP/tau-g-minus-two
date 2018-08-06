#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <sstream>

const Int_t n = 50; //max histogram sets
const Int_t N = 200; //max particles in event

Int_t sets[n];
TTree* treeOut[n];
TTree* xsecOut;

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
