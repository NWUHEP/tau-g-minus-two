#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
using namespace std;

//particle mass from id, mainly for the leptons/protons since inf eta makes the pt, eta formula weird
Double_t massId(Int_t id) {

  switch(abs(id)) {
  case 11:   return 0.00051099907; //electron
  case 2212: return 0.93827231; //proton
  case 2112: return 0.93956541; //neutron
  case 22:   return 0.0; //gamma
  case 13:   return 0.105658389; //mu
  case 15:   return 1.7768; //tau
  case 211:  return 0.13956995; //charged pion
  case 111:  return 0.1345766; //pi0?
  case 12: case 14: case 16: //neutrinos
             return 0.0;
  // case 221: return 0.54750; //eta
  // case 213: return 0.0; //omega
  // case 113: return 0.0;
  // case 310: return 0.0;
  // case 223: return 0.0;
    
  }
  cout << "Undefined particle id, " << id << ", returning 0 mass\n";
  return 0.0;
}


void myConvertLPairToLHE()
{
  const Double_t energy = 4000;
  const Int_t N = 200; // max number of particles in per event
  const Int_t max_events = 1e3;

  TFile *f1 = TFile::Open("events.root");
  TTree *t1 = (TTree*) f1->Get("h4444");
  TTree *t2 = (TTree*) f1->Get("run");  
  Double_t xsec, errxsec;
  Double_t en[N],pt[N],phi[N], eta[N], px[N], py[N], pz[N], m[N], sqrtS;
  Int_t partid[N], parent1[N], parent2[N], ip, status[N], iz[N];

  //set run information branches
  t2->SetBranchAddress("sqrt_s",&sqrtS);
  t2->SetBranchAddress("xsect",&xsec);
  t2->SetBranchAddress("errxsect",&errxsec);

  //set particle information branches
  t1->SetBranchAddress("pt",&pt);
  t1->SetBranchAddress("eta",&eta);
  t1->SetBranchAddress("phi",&phi);
  t1->SetBranchAddress("E",&en);
  t1->SetBranchAddress("npart",&ip);
  t1->SetBranchAddress("pdg_id",&partid);
  t1->SetBranchAddress("status",&status);
  t1->SetBranchAddress("parent1",&parent1);
  t1->SetBranchAddress("parent2",&parent2);

  ofstream output("gammagammamumu.lpair_inelel_pt15_8tev.lhe");
  //ofstream output("gammagammatautau.lpair_inelel_pt15_7tev.lhe");
  //ofstream output("gammagammatautau.lpair_inelel_tautau_pt25_8tev.lhe");
  //ofstream output("gammagammatautau.lpair_elel_tautau_pt40_7tev.lhe");

  Int_t nevts = t1->GetEntries();
  if(nevts<1) { std::cout << "no event in the file\n"; return;}

  int first_event = 0;

  output << "<LesHouchesEvents version=\"1.0\">"  << endl; 
  output << "<header>" << endl; 
  output << "This file was created from the output of the LPAIR generator" << endl; 
  output << "</header>" << endl; 

  t1->GetEntry(0);
  t2->GetEntry(0);
  cout << "xsect = " << xsec << " +/- " << errxsec << endl;

  output << "<init>" << endl;
  output << "2212 2212 " << sqrtS/2 << " " << sqrtS/2 << " 0 0 10042 10042 2 1" << endl;
  output << xsec << " " << errxsec << " 0.26731120000E-03 0" << endl;
  output << "</init>" << endl;

  Int_t maxPrint = 5;
  Int_t numPrint = 0;
  for(Int_t i = first_event;i < first_event+max_events;i++) {
    t1->GetEntry(i);
    if (i%10000==0) {
      cout << i << ", Npart = " << ip << endl;
    }
    
    output << "<event>" << endl; 
    output << ip-3 << " 0 0.2983460E-04  0.9118800E+02  0.7546772E-02  0.1300000E+00" << endl;
    //	cout << "there are " << ip << " particles in this event\n";

    
    Int_t offset = -1;
    for(int j=0; j<ip; j++) {
      //	Stupid trick to produce inelastic events in both directions!
      
      if (i%10000==0) {
	cout << "status, partid, parent1, parent2: " << status[j] << ", " << partid[j];
	cout << ", " << parent1[j] << ", " << parent2[j] << endl;
      }
      
      iz[j] = 0.;
      //parent1[j] -= 2;
      parent1[j] = TMath::Max(parent1[j], 0);
      if(j < 8 and abs(partid[j]) < 16 and abs(partid[j])>10 and status[j] == 21) continue;
      if(abs(partid[j]) < 16 and j < 8) {
	parent1[j] = 3;
	parent2[j] = 4;
      }
      else {
	parent2[j] = parent1[j];
      }
      
      if(i%2 == 0)
	eta[j] = -eta[j];


      pz[j] = (isinf(eta[j]) or abs(eta[j]) > 10.) ? copysign(sqrt(en[j]*en[j] - massId(partid[j])*massId(partid[j])), eta[j])
			  : pt[j]*sinh(eta[j]);
      px[j]=pt[j]*cos(phi[j]);
      py[j]=pt[j]*sin(phi[j]);
      Double_t mSq = (en[j]*en[j]-px[j]*px[j]-py[j]*py[j]-pz[j]*pz[j]);
      m[j] = (isinf(eta[j]) or abs(partid[j]) == 22 or abs(partid[j]) == 2212 or abs(partid[j]) == 2112) ?
			  massId(partid[j]) : copysign(sqrt(abs(mSq)),mSq);

      TLorentzVector* part = new TLorentzVector(0.,0.,0.,0.);
      part->SetPtEtaPhiE(pt[j],eta[j],phi[j],en[j]);
      if(numPrint < maxPrint and (abs(part->Pz() - pz[j]) > 10 or abs(part->M() - m[j]) > 0.5)) {
	cout << "Miss-Matched Momentum Algorithms!\n";
	part->Print();
	cout << "P: {" << px[j] << ", " << py[j] << ", " << pz[j] << ", " << en[j] << "}\n";
	cout << "status, partid, pt, eta, phi: " << status[j] << ", " << partid[j];
	cout << ", " << pt[j] << ", " << eta[j] << ", " <<  phi[j] << endl << endl;
	++numPrint;
      }
      if (i%10000==0) {
	cout << "P: {" << px[j] << ", " << py[j] << ", " << pz[j] << ", " << en[j] << "}\n";
	cout << "status, partid, parent1, parent2: " << status[j] << ", " << partid[j];
	cout << ", " << parent1[j] << ", " << parent2[j] << endl << endl;
      }
      
      if (partid[j]==2212 && status[j]==21 ) {
	if(j > 1) {offset +=2;cout << "SKIPPING! offset is now: " << offset << endl;continue;}
	//continue;
	status[j]=-1;
	parent1[j]=0;
	parent2[j]=0;
      }
      else if (partid[j]==22 && status[j]==21 && j < 4) {
	if (j%2==0) iz[j] = 1.;
	else iz[j] = -1.; // helicity
	parent1[j] = j-1;
	parent2[j] = j-1;
	status[j]  = 2; // incoming photon
      }
      else if (partid[j]==92) status[j] = 3; // string
      else if ((partid[j]==1 || partid[j]==2 || partid[j]==2101 || partid[j]==2103 || partid[j]==2203) && (status[j]>=11 && status[j]<=13)) status[j] = 3; // quarks content
      else if (status[j]==11) status[j] = 2; // intermediate resonance
      
      //output << partid[j] << " 1 1 2 0 0 " << px[j] << " " << py[j] << " " << pz[j] << " " << en[j] << " " << m[j] << " 0. " << iz[j] << endl;        
      output << fixed << setw(6) << partid[j] << setw(4)
             << status[j] << setw(4)
             << parent1[j] << "   " << parent2[j] << "   0   0" << setw(14)
             << px[j] << setw(14)
             << py[j] << setw(14)
             << pz[j] << setw(14)
             << en[j] << setw(11)
             << m[j] << " 0. " << setw(9)
             << iz[j] << endl;
      //        output << "P "<< i*N+j << " " << partid[j] << " " << px[j] << " " << py[j] << " " << pz[j] << " " << en[j] << " 1 0 0 0 0" << endl;      
    }
 
    
    output << "</event>" << endl;
  }
  output << "</LesHouchesEvents>" << endl;
  output.close();
  
  cout << "Converted " << max_events << " events" << endl;
}
