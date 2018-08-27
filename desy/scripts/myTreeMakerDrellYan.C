#include "myTreeMakerDrellYan.h"
using namespace std;



//initialize the trees and the branches for the particle trees
void bookHistograms() {
  xsecOut = new TTree("xsec", "Cross Section information");
  for(int i = 0; i < n; i++) {
    if(sets[i]) {

      char* dirname        = new char[20];
      char* strname        = new char[20];
      char* histMname1     = new char[20];
      char* histMname2     = new char[20];
      char* histRname      = new char[20];
      char* histptVsMname  = new char[20];
      sprintf(dirname,"book_%i",i);
      sprintf(strname,"treeBook_%i",i);
      sprintf(histMname1,"massH1_%i",i);
      sprintf(histMname2,"massH2_%i",i);
      sprintf(histRname,"rapidityH_%i",i);
      sprintf(histptVsMname,"ptVsMassH_%i",i);

      directories[i] = topdir->mkdir(dirname);
      directories[i]->cd();
      
      treeOut[i] = new TTree(strname, "Event information");
      
      treeOut[i]->Branch("leptonSys",     "TLorentzVector",    &tauSys            );
      treeOut[i]->Branch("lepton",        "TLorentzVector",    &tau               );
      treeOut[i]->Branch("antilepton",    "TLorentzVector",    &antitau           );
      treeOut[i]->Branch("pdg1",          &pdg1,               "pdg1/I"           );
      treeOut[i]->Branch("pdg2",          &pdg2,               "pdg2/I"           );
      treeOut[i]->Branch("nJets",         &nJets,              "nJets/i"          );
      treeOut[i]->Branch("px1",           &px1,                "px1/D"            );
      treeOut[i]->Branch("py1",           &py1,                "py1/D"            );
      treeOut[i]->Branch("pz1",           &pz1,                "pz1/D"            );
      treeOut[i]->Branch("px2",           &px2,                "px2/D"            );
      treeOut[i]->Branch("py2",           &py2,                "py2/D"            );
      treeOut[i]->Branch("pz2",           &pz2,                "pz2/D"            );
      treeOut[i]->Branch("lepton1Iso",    &iso1,               "iso1/F"           );
      treeOut[i]->Branch("lepton2Iso",    &iso2,               "iso2/F"           );
      treeOut[i]->Branch("lepton1D0",     &d01,                "d01/F"            );
      treeOut[i]->Branch("lepton2D0",     &d02,                "d02/F"            );
      treeOut[i]->Branch("rPV",           "TVector3",          &primaryV          );
      treeOut[i]->Branch("eventWeight",   &eventWeight,        "eventWeight/F"    );
      treeOut[i]->Branch("acoplanar",     &acoplane,           "acoplanar/D"      );
      treeOut[i]->Branch("fracLossPlus",  &fracLossPlus,       "fracLossPlus/D"   );
      treeOut[i]->Branch("fracLossMinus", &fracLossMinus,      "fracLossMinus/D"  );

      massH1[i]    = new TH1F(histMname1,"Invariant Mass of Lepton System", 200,0,1000);
      massH2[i]    = new TH1F(histMname2,"Invariant Mass of Lepton System", 200,0,200);
      rapidityH[i] = new TH1F(histRname,"Rapidity of Lepton System", 120,-3,3);
      ptVsMass[i]  = new TH2F(histptVsMname,"Lepton Pt vs Lepton System Mass", 100,0,500,100,0,500);
    }
  }
}

void fillHistograms(Int_t index) {

  treeOut[index]->Fill();
  rapidityH[index]->Fill(tauSys->Rapidity(),1000*xsec/totalEvents*lum*eventWeight);
  massH1[index]->Fill(tauSys->M(),1000*xsec/totalEvents*lum*eventWeight);
  massH2[index]->Fill(tauSys->M(),1000*xsec/totalEvents*lum*eventWeight);
  ptVsMass[index]->Fill(tau->Pt(), tauSys->M());

}

void writeHistograms() {
  topdir->cd();
  xsecOut->Write();
  for(int i = 0; i < n; i++) {
    if(sets[i]){
      
      directories[i]->cd();
      treeOut[i]->Write();
      massH1[i]->Write();
      massH2[i]->Write();
      rapidityH[i]->Write();
      ptVsMass[i]->Write();
    }
  }
}

Int_t myTreeMakerDrellYan( TString filename = "/mnt/data/cms/sample_ntuple.root", TString foldername = "mumu",
			   TString treename = "bltTree_zjets_m-50", TString outfilename = "events_full.root",
			   Double_t luminosity = 15.6)
{
  lum=luminosity;
  
  //use sets array to determine which trees to build, write, and fill
  //this way adding a new cut or set is trivial
  for(int i = 0; i < n; i++) sets[i] = 0;


  sets[0] = 1; //all events
  //1-20 reserved for invariant mass > 110
  //20-40 reserved for invariant mass > 400  
  sets[1] = 1; //invariant mass > 110
  sets[2] = 0; // " + pt of each lepton > 33
  sets[3] = 0; // " + pt of each lepton > 38
  sets[4] = 1; // " + pt of each lepton > 50
  sets[5] = 1; // " + " + acoplane < 0.009
  sets[6] = 1; // " + " + acoplane < 0.006
  sets[7] = 0; // Mass > 110 + pt > 33 + eta < 2.4
  sets[8] = 1; // "       "    pt > 50 + "      "
  sets[9] = 1; // Mass > 110 + pt > 50 + eta < 2.4 + acoplane < 0.009
  sets[13] = 1; // " + nJets < 1
  sets[11] = 1; // Mass > 110 + pt > 50 + eta < 2.4 + acoplane < 0.009 + fracLoss check
  sets[10] = 1; // "       "    "    "  + "      "  + acoplane < 0.006
  sets[14] = 1; // " + nJets < 1 
  sets[12] = 1; // Mass > 110 + pt > 50 + eta < 2.4 + acoplane < 0.006 + fracLoss check
  sets[15] = 0; // M > 110, pt>50, eta<2.4, acoplane<0.006, nJets>1, pt lead/pt trail > 0.95
  
  sets[21] = 0; //invariant mass > 400
  sets[22] = 0; // " + pt of each lepton > 33
  sets[23] = 0; // " + pt of each lepton > 38
  sets[24] = 0; // " + pt of each lepton > 50

  //No invariant Mass Cut
  //MASS CUT AT 50 ALREADY IN NTUPLE SO THIS NEEDS FIXING
  sets[41] = 1; //Pt > 20 and eta < 2.4
  sets[43] = 1; //Pt > 20 and eta < 2.4 and acoplane < 0.009
  sets[44] = 1; //Pt > 20 and eta < 2.4 and acoplane < 0.006
  sets[42] = 0; //Pt > 33 and eta < 2.4
  sets[45] = 0; //Pt > 33 and eta < 2.4 and acoplane < 0.009
  sets[46] = 0; //Pt > 33 and eta < 2.4 and acoplane < 0.006
  sets[47] = 1; //Pt > 20 and eta < 2.4 and acoplane < 0.006 and nJets < 1
  sets[48] = 1; //Pt > 33 and eta < 2.4 and acoplane < 0.006 and nJets < 1
  sets[50] = 0; //pt>20, eta<2.4, acoplane<0.006, nJets>1, pt lead/pt trail > 0.95
  sets[51] = 1; //pt>20, eta<2.4, acoplane<0.006, nJets>1, 50 < Mass < 80
 
  //initialize input and output file
  TFile *f1 = TFile::Open(filename);
  if(f1 == NULL) return 1;
  TFile *out = new TFile(outfilename, "RECREATE", "Event information from LPair event.root file");

  //Get tree of interest
  TFile *folder = (TFile*) f1->Get(foldername);
  TTree* t1;
  TH1*   totalEventsH;
  totalEventsH = (TH1*) f1->Get("TotalEvents_zjets_m-50");
  
  if(folder) t1 = (TTree*) folder->Get(treename);
  else {std::cout << "Folder " << folder << " not found in "
		  << filename << std::endl; return 2;} //error getting the tree

  //initialize directory structure for root file
  topdir = out->mkdir("Data");
  topdir->cd();
  

  //initialize the trees
  bookHistograms();

  //set particle information branches
  t1->SetBranchAddress("leptonOneP4"      ,&momentum1       );
  t1->SetBranchAddress("leptonTwoP4"      ,&momentum2       );
  t1->SetBranchAddress("leptonOneFlavor"  ,&pdg1            );
  t1->SetBranchAddress("leptonTwoFlavor"  ,&pdg2            );
  t1->SetBranchAddress("leptonOneIso"     ,&iso1            );
  t1->SetBranchAddress("leptonTwoIso"     ,&iso2            );
  t1->SetBranchAddress("leptonOneD0"      ,&d01             );
  t1->SetBranchAddress("leptonTwoD0"      ,&d02             );

  //set event information branches
  t1->SetBranchAddress("eventWeight"      ,&eventWeight     );
  t1->SetBranchAddress("rPV"              ,&primaryV        );
  t1->SetBranchAddress("nElectrons"       ,&nElectrons      );
  t1->SetBranchAddress("nMuons"           ,&nMuons          );
  t1->SetBranchAddress("nTaus"            ,&nTaus           );
  t1->SetBranchAddress("nJets"            ,&nJets           );
  
  //for qqbar -> z->l+l- + jets mass > 50 GeV = 5776.1 pb  
  xsec = 5776.1;
  
  //get the number of events, exiting if no events
  nevts = t1->GetEntries();
  totalEvents = 1;
  if(nevts<1) { std::cout << "no event in the file\n"; return 2;}
  //if the run tree exists, save its information
  if(totalEventsH == NULL) {
    std::cout << "no cross section information\n";
  } else {
    totalEvents = totalEventsH->GetBinContent(1);
    Double_t effectiveXsec = ((Double_t) nevts)/totalEvents*xsec;
    xsecOut->Branch("xsec",           &xsec,          "xsec/D"         );
    xsecOut->Branch("totalEvents",    &totalEvents,   "totalEvents/I"  );
    xsecOut->Branch("nevts",          &nevts,         "nevts/I"        );
    xsecOut->Branch("intLum",         &lum,           "intLum/D"       );
    xsecOut->Branch("effectiveXsec",  &effectiveXsec, "effectiveXsec/D");
    xsecOut->Fill();
  }
  

  //Event Loop
  for(Int_t i = 0; i < nevts; i++) { //
    t1->GetEntry(i);
    if (i%50000==0) cout << "Event number: " << i << endl;

    acoplane = 0.0;

    //determine which is the lepton and which is the anti-lepton
    if(pdg1 > 0){ tau = new TLorentzVector(*momentum1); antitau = new TLorentzVector(*momentum2);}
    else { antitau = new TLorentzVector(*momentum1); tau = new TLorentzVector(*momentum2);}
    
    *tauSys = *tau+*antitau;
    //CMS-Totem paper definition of acoplanarity 
    acoplane = abs(1-abs(tau->Phi()-antitau->Phi())/3.141592654);

    fracLossPlus  = 1/13000.0*(tau->Pt()*exp(tau->Eta())+antitau->Pt()*exp(antitau->Eta()));
    fracLossMinus = 1/13000.0*(tau->Pt()*exp(-1*tau->Eta())+antitau->Pt()*exp(-1*antitau->Eta()));

    //kinematic cut filling
    fillHistograms(0);
    //no mass requirements
    if(abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4 and tau->Pt() > 20 and antitau->Pt() > 20) {
      if(sets[41]) fillHistograms(41);
      if(sets[43] and acoplane < 0.009) fillHistograms(43);
      if(sets[44] and acoplane < 0.006) fillHistograms(44);
      if(sets[47] and acoplane < 0.006 and nJets < 1) fillHistograms(47);
      if(sets[50] and acoplane < 0.006 and nJets < 1
	 and (tau->Pt()/antitau->Pt() > 0.95) and (antitau->Pt()/tau->Pt() > 0.95)) fillHistograms(50);
      if(sets[51] and acoplane < 0.006 and tauSys->M() < 80.0
	 and tauSys->M() > 50.0 and nJets < 1) fillHistograms(51);
      if(tau->Pt() > 33 and antitau->Pt() > 33) {
	if(sets[42]) fillHistograms(42);
	if(sets[45] and acoplane < 0.009) fillHistograms(45);
	if(sets[46] and acoplane < 0.006) fillHistograms(46);
	if(sets[48] and acoplane < 0.006 and nJets < 1) fillHistograms(48);   
      }
    }
    if(tauSys->M() > 110) {
      //110 GeV Mass Trees
      if(sets[1]) fillHistograms(1);
      if(tau->Pt() > 33 and antitau->Pt() > 33) {
    	if(sets[2]) fillHistograms(2);
	if(sets[7] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4) fillHistograms(7);
    	if(tau->Pt() > 38 and antitau->Pt() > 38) {
    	  if(sets[3]) fillHistograms(3);
    	  if(tau->Pt() > 50 and antitau->Pt() > 50) {
    	    if(sets[4]) fillHistograms(4);
	    if(sets[8] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4) fillHistograms(8);
	    if(acoplane < 0.009) {
	      if(sets[5]) fillHistograms(5);
	      if(sets[13] and nJets < 1) fillHistograms(13);
	      if(sets[9] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4){
		fillHistograms(9);
		if(sets[11] and (fracLossPlus > 0.032 or fracLossMinus > 0.024)) fillHistograms(11);
	      }
	      if(acoplane < 0.006) {
		if(sets[10] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4) {
		  fillHistograms(10);
		  if(sets[15] and nJets < 1 and (tau->Pt()/antitau->Pt() > 0.95)
		     and (antitau->Pt()/tau->Pt() > 0.95)) fillHistograms(15);
		  if(sets[14] and nJets < 1) fillHistograms(14);
		  if(sets[12] and (fracLossPlus > 0.032 or fracLossMinus > 0.024)) fillHistograms(12);
		}
		if(sets[6]) fillHistograms(6);
	      }
	    }
    	  }
    	}
      }
      //400 GeV Mass Trees
      if(tauSys->M() > 400) {
    	if(sets[21]) fillHistograms(21);
    	if(tau->Pt() > 33 and antitau->Pt() > 33) {
    	  if(sets[22]) fillHistograms(22);
    	  if(tau->Pt() > 38 and antitau->Pt() > 38) {
    	    if(sets[23]) fillHistograms(23);
    	    if(tau->Pt() > 50 and antitau->Pt() > 50) {
    	      if(sets[24]) fillHistograms(24);
    	    }
    	  }
    	}
      }
    }
  }
  //print out the number of events, cross section (fb), percent passing each cut, and each cuts cross section
  cout << "***Number of events, Total Number, cross section (fb), percent passing each cut, and each cuts cross section:\n";
  for(int i = 0; i < n; i++) {
    Double_t effX = nevts*xsec/totalEvents*1000;
    if(sets[i]){
      cout << "Set number " << i << ": " << nevts << ", " << totalEvents << ", " << effX << ", " <<
	(((treeOut[i]->GetEntries())*100.0)/nevts) << ", " << (((treeOut[i]->GetEntries())*1.0)/nevts)*effX << endl;
    }
  }
  //write trees after done with event loop
  writeHistograms();

  return 0;
}
