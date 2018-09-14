#include "myTreeMaker.h"
using namespace std;


//particle mass from id, mainly for the leptons/protons since inf eta makes the pt, eta formula weird
Double_t massID(Int_t id) {

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
  //cout << "Undefined particle id, " << id << ", returning 0 mass\n";
  return 0.0;
}

//initialize the trees and the branches for the particle trees


void bookHistograms() {
  xsecOut = new TTree("xsec", "Cross Section information");
  setEvents   = new TH1F("setEvents",  "Events in each Set", n, 0. , n);
  setEventsN  = new TH1F("setEventsN", "Weighted Events in each Set", n, 0. , n);
  drellTester = new TH1F("drellTester", "drell tester", 100, 0. , 100.);
  drellTester->GetXaxis()->SetBinLabel(1,"All Events");
  drellTester->GetXaxis()->SetBinLabel(2,"Eta Cut");
  drellTester->GetXaxis()->SetBinLabel(3,"LeadPt > 30");
  drellTester->GetXaxis()->SetBinLabel(4,"TrailPt > 10");
  drellTester->GetXaxis()->SetBinLabel(5,"M < 80");
  drellTester->GetXaxis()->SetBinLabel(6,"M > 50");
  drellTester->GetXaxis()->SetBinLabel(7,"acoplane < .006");
  drellTester->GetXaxis()->SetBinLabel(8,"nJets < 1");
  
  for(int i = 0; i < n; i++) {
    if(sets[i]) {
      cnt[i] = 0;

      char* dirname          = new char[20];
      char* strname          = new char[20];
      char* histMname1       = new char[20];
      char* histMname2       = new char[20];
      char* histRname        = new char[20];
      char* histptRname      = new char[20];
      char* histptMname      = new char[20];
      char* histmPtname      = new char[20];
      char* histptVsMname    = new char[20];
      char* histPLossVsEta   = new char[20];
      char* histPLossVsEtaM2 = new char[20];
      char* histEConsname    = new char[20];
      char* histEConsnameM2  = new char[20];

      sprintf(dirname,          "book_%i",i);
      sprintf(strname,          "treeBook_%i",i);
      sprintf(histMname1,       "massH1_%i",i);
      sprintf(histMname2,       "massH2_%i",i);
      sprintf(histRname,        "rapidityH_%i",i);
      sprintf(histptRname,      "ptRatioH_%i",i);
      sprintf(histptVsMname,    "ptVsMassH_%i",i);
      sprintf(histptMname,      "ptMassH_%i",i);
      sprintf(histmPtname,      "massPtH_%i",i);
      sprintf(histPLossVsEta,   "pLossVsEtaH_%i",i);
      sprintf(histPLossVsEtaM2, "pLossVsEtaM2H_%i",i);
      sprintf(histEConsname,    "eConsH_%i",i);
      sprintf(histEConsnameM2,  "eConsM2H_%i",i);

      directories[i] = topdir->mkdir(dirname);
      directories[i]->cd();
      
      treeOut[i] = new TTree(strname, "Event information");
      
      treeOut[i]->Branch("npart",         &npOut,              "npart/I"          );
      treeOut[i]->Branch("leptonSys",     "TLorentzVector",    &tauSys            );
      treeOut[i]->Branch("gammaSys",      "TLorentzVector",    &gammaSys          );
      treeOut[i]->Branch("lepton",        "TLorentzVector",    &tau               );
      treeOut[i]->Branch("antilepton",    "TLorentzVector",    &antitau           );
      treeOut[i]->Branch("gamma1",        "TLorentzVector",    &gamma1            );
      treeOut[i]->Branch("gamma2",        "TLorentzVector",    &gamma2            );
      treeOut[i]->Branch("proton1",       "TLorentzVector",    &proton1           );
      treeOut[i]->Branch("proton2",       "TLorentzVector",    &proton2           );
      // treeOut[i]->Branch("leptonSysM2",   "TLorentzVector",    &tauSysM2          );
      // treeOut[i]->Branch("gammaSysM2",    "TLorentzVector",    &gammaSysM2        );
      // treeOut[i]->Branch("leptonM2",      "TLorentzVector",    &tauM2             );
      // treeOut[i]->Branch("antileptonM2",  "TLorentzVector",    &antitauM2         );
      // treeOut[i]->Branch("gamma1M2",      "TLorentzVector",    &gamma1M2          );
      // treeOut[i]->Branch("gamma2M2",      "TLorentzVector",    &gamma2M2          );
      // treeOut[i]->Branch("proton1M2",     "TLorentzVector",    &proton1M2         );
      // treeOut[i]->Branch("proton2M2",     "TLorentzVector",    &proton2M2         );
      treeOut[i]->Branch("parent1",       parent1Out,          "parent1[npart]/I" );
      treeOut[i]->Branch("parent2",       parent2Out,          "parent2[npart]/I" );
      treeOut[i]->Branch("status",        statusOut,           "status[npart]/I"  );
      treeOut[i]->Branch("pdg",           partidOut,           "pdg[npart]/I"     );
      treeOut[i]->Branch("px",            px,                  "px[npart]/D"      );
      treeOut[i]->Branch("py",            py,                  "py[npart]/D"      );
      treeOut[i]->Branch("pz",            pz,                  "pz[npart]/D"      );
      treeOut[i]->Branch("acoplanar",     &acoplane,           "acoplanar/D"      );
      treeOut[i]->Branch("fracLossPlus",  &fracLossPlus,       "fracLossPlus/D"   );
      treeOut[i]->Branch("fracLossMinus", &fracLossMinus,      "fracLossMinus/D"  );
      treeOut[i]->Branch("ptMass",        &ptM,                "ptM/D"            );
      treeOut[i]->Branch("ptRatio",       &ptRatio,            "ptRatio/D"        );

      eCons[i]        = new TH1F(histEConsname,"Energy Conservation of System", 500,-100,100);
      eConsM2[i]      = new TH1F(histEConsnameM2,"Energy Conservation of System Method 2", 500,-100,100);
      massH1[i]        = new TH1F(histMname1,"Invariant Mass of Lepton System", 200,0,1000);
      massH2[i]        = new TH1F(histMname2,"Invariant Mass of Lepton System", 200,0,200);
      ptR[i]           = new TH1F(histptRname,"Leading Lepton Pt Over Trailing Lepton Pt",   300,0, 5);
      ptMass[i]        = new TH1F(histptMname,"Invariant Mass of Lepton System Over Pt Sum", 250,0,50);
      massPt[i]        = new TH1F(histmPtname,"Pt Sum Over Invariant Mass of Lepton System", 300,0,30);
      rapidityH[i]     = new TH1F(histRname,"Rapidity of Lepton System", 120,-3,3);
      ptVsMass[i]      = new TH2F(histptVsMname,"Lepton Pt vs Lepton System Mass", 500,0,500,500,0,500);
      pLossVsEta[i]    = new TH2F(histPLossVsEta,"Proton Frac. Mom. Loss vs Eta", 500,-20.,20.,500,-0.02,0.3);
      pLossVsEtaM2[i]  = new TH2F(histPLossVsEtaM2,"Proton Frac. Mom. Loss vs Eta Method 2", 500,-20.,20.,500,-0.02,0.3);
    }
  }
}

void fillHistograms(Int_t index) {
  cnt[index] += 1;
  if(writeTree_) treeOut[index]->Fill();
  rapidityH[index]->Fill(tauSys->Rapidity(),xsec/nevts*1000*lum);
  massH1[index]->Fill(tauSys->M(),xsec/nevts*1000*lum);
  massH2[index]->Fill(tauSys->M(),xsec/nevts*1000*lum);
  ptVsMass[index]->Fill(tau->Pt(), tauSys->M(),xsec/nevts*1000*lum);
  ptMass[index]->Fill(1.0/ptM,xsec/nevts*1000*lum);
  pLossVsEta[index]->Fill(proton1->Eta(),1-proton1->P()/sqrtS*2.);
  pLossVsEta[index]->Fill(proton2->Eta(),1-proton2->P()/sqrtS*2.);
  pLossVsEtaM2[index]->Fill(proton1M2->Eta(),1-proton1M2->P()/sqrtS*2.);
  pLossVsEtaM2[index]->Fill(proton2M2->Eta(),1-proton2M2->P()/sqrtS*2.);
  eCons[index]->Fill(proton1->E()+proton2->E()+tauSys->E()-sqrtS);
  eConsM2[index]->Fill(proton1M2->E()+proton2M2->E()+tauSysM2->E()-sqrtS);
  massPt[index]->Fill(ptM,xsec/nevts*1000*lum);
  setEvents->Fill(index);
  setEventsN->Fill(index, 1.);
  ptR[index]->Fill(ptRatio,xsec/nevts*1000*lum);

}

void writeHistograms() {
  topdir->cd();
  xsecOut->Write();
  drellTester->Write();
  setEvents->Write();
  setEventsN->Write();
  for(int i = 0; i < n; i++) {
    if(sets[i]){
      
      directories[i]->cd();
      
      massH1[i]->Write();
      massH2[i]->Write();
      rapidityH[i]->Write();
      ptVsMass[i]->Write();
      ptMass[i]->Write();
      massPt[i]->Write();
      ptR[i]->Write();
      pLossVsEta[i]->Write();
      pLossVsEta[i]->Write();
      pLossVsEtaM2[i]->Write();
      pLossVsEtaM2[i]->Write();
      eCons[i]->Write();
      eConsM2[i]->Write();
      if(writeTree_) treeOut[i]->Write();
      else {
	char* bookName = new char[20];
	sprintf(bookName,"treeBook_%i", i);
	directories[i]->Delete(bookName);
      }
    }
  }
}

void myTreeMaker(Int_t leptonNum = 15, TString filename = "events.root", TString outfilename = "events_full.root", Int_t writeTree = 1, Double_t luminosity = 15.6)
{
  lum=luminosity;
  Int_t maxEvts = 1e7;
  writeTree_ = writeTree;

  //use sets array to determine which trees to build, write, and fill
  //this way adding a new cut or set is trivial
  for(int i = 0; i < n; i++) sets[i] = 0;


  sets[0] = 1; //all events
  //1-20 reserved for invariant mass > 110
  //20-40 reserved for invariant mass > 400  
  sets[1] = 0; //invariant mass > 110
  sets[2] = 0; // " + pt of each lepton > 33
  sets[3] = 0; // " + pt of each lepton > 38
  sets[4] = 0; // " + pt of each lepton > 50
  sets[5] = 0; // " + " + acoplane < 0.009
  sets[6] = 0; // " + " + acoplane < 0.006
  sets[7] = 0; // Mass > 110 + pt > 33 + eta < 2.4
  sets[8] = 1; // "       "    pt > 50 + "      "
  sets[9] = 1; // Mass > 110 + pt > 50 + eta < 2.4 + acoplane < 0.009
  sets[11] = 1; // Mass > 110 + pt > 50 + eta < 2.4 + acoplane < 0.009 + fracLoss check
  sets[10] = 1; // "       "    "    "  + "      "  + acoplane < 0.006
  sets[12] = 1; // Mass > 110 + pt > 50 + eta < 2.4 + acoplane < 0.006 + fracLoss check
  sets[15] = 0; // " +          "  +            "  +       "          +pt leading / pt trailing > 0.95
  
  sets[21] = 0; //invariant mass > 400
  sets[22] = 0; // " + pt of each lepton > 33
  sets[23] = 0; // " + pt of each lepton > 38
  sets[24] = 0; // " + pt of each lepton > 50

  sets[41] = 1; //Pt > 20 and eta < 2.4
  sets[43] = 1; //Pt > 20 and eta < 2.4 and acoplane < 0.009
  sets[44] = 1; //Pt > 20 and eta < 2.4 and acoplane < 0.006
  sets[50] = 0; // " +          "  +            "   +pt leading / pt trailing > 0.95
  sets[51] = 1; // " +          "  +            "   + 50 GeV < Mass < 80 GeV
  sets[52] = 1; // " +          "  +            "   + 10 GeV < Mass < 50 GeV
  sets[42] = 0; //Pt > 33 and eta < 2.4
  sets[45] = 0; //Pt > 33 and eta < 2.4 and acoplane < 0.009
  sets[46] = 0; //Pt > 33 and eta < 2.4 and acoplane < 0.006

  sets[53] = 1; //leading pt>30, trailing pt > 10, eta<2.4, acoplane<0.006, 50 < Mass < 80
  sets[54] = 1; //leading pt>30, trailing pt > 10, eta<2.4, acoplane<0.006, 10 < Mass < 50
  sets[55] = 1; //leading pt>30, trailing pt > 10, eta<2.4, acoplane<0.006,      Mass < 80


 
  //initialize input and output file
  TFile *f1 = TFile::Open(filename);
  TFile *out = new TFile(outfilename, "RECREATE", "Event information from LPair event.root file");

  //initialize directory structure for root file
  topdir = out->mkdir("Data");
  topdir->cd();
  

  //initialize the trees
  bookHistograms();

  //t1 is the particle information tree
  //t2 has some run information, such as cross section
  TTree *t1 = (TTree*) f1->Get("h4444");
  TTree *t2 = (TTree*) f1->Get("run");

  //set run information branches
  t2->SetBranchAddress("sqrt_s",&sqrtS);
  t2->SetBranchAddress("xsect",&xsec);
  t2->SetBranchAddress("errxsect",&errxsec);

  //set particle information branches
  t1->SetBranchAddress("pt",&pt);
  t1->SetBranchAddress("eta",&eta);
  t1->SetBranchAddress("phi",&phi);
  t1->SetBranchAddress("E",&en);
  t1->SetBranchAddress("npart",&np);
  t1->SetBranchAddress("pdg_id",&partid);
  t1->SetBranchAddress("status",&status);
  t1->SetBranchAddress("parent1",&parent1);
  t1->SetBranchAddress("parent2",&parent2);

  //get the number of events, exiting if no events
  nevts = t1->GetEntries();
  if(nevts<1) { std::cout << "no event in the file\n"; return;}
  cout << "Events in the Tree: " << nevts << endl;
  nevts = nevts>maxEvts ? maxEvts : nevts;
  
  //if the run tree exists, save its information
  if(t2->GetEntries() < 1) {
    std::cout << "no cross section information\n";
  } else {
    t2->GetEntry(0);
    xsecOut->Branch("xsec",    &xsec,    "xsec/D"   );
    xsecOut->Branch("errxsec", &errxsec, "errxsec/D");
    xsecOut->Branch("nevts",   &nevts,   "nevts/I"  );
    xsecOut->Branch("sqrt_s",  &sqrtS,   "sqrt_s/D");
    xsecOut->Fill();
  }

  //lorentz vector for the particle read in each loop in the event loop
  TLorentzVector* part   = new TLorentzVector(0.,0.,0.,0.);
  TLorentzVector* partM2 = new TLorentzVector(0.,0.,0.,0.);
  gamma1M2   = new TLorentzVector(0.,0.,0.,0.);
  gamma2M2   = new TLorentzVector(0.,0.,0.,0.);
  proton1M2  = new TLorentzVector(0.,0.,0.,0.);
  proton2M2  = new TLorentzVector(0.,0.,0.,0.);
  tauM2      = new TLorentzVector(0.,0.,0.,0.);
  antitauM2  = new TLorentzVector(0.,0.,0.,0.);
  tauSysM2   = new TLorentzVector(0.,0.,0.,0.);
  gammaSysM2 = new TLorentzVector(0.,0.,0.,0.);

  //Event Loop
  for(Int_t i = 0;i < nevts;i++) { //
    t1->GetEntry(i);
    if (i%50000==0) cout << "Event " << i << " of " << nevts << ", Npart = " << np << endl;

    npOut = np; //number of particles
    acoplane = 0.0;

    //loop over the particles in the event
    for(Int_t j = 0; j < np; j++) {
      //check for inf eta when getting pz
      pz[j] = copysign(sqrt(en[j]*en[j] - massID(partid[j])*massID(partid[j])), eta[j]);
      px[j]=pt[j]*cos(phi[j]);
      py[j]=pt[j]*sin(phi[j]);
      parent1Out[j]=parent1[j];
      parent2Out[j]=parent2[j];
      statusOut[j]=status[j];
      partidOut[j]=partid[j];
      part   = new TLorentzVector(px[j],py[j],pz[j],en[j]);
      partM2->SetPtEtaPhiE(pt[j],eta[j],phi[j],en[j]);
      
      //particle 1 and 2 are initial protons
      //particle 3 and 4 are gammas
      //a virtual particle has status 21, if found virtual lepton get its daughter instead
      if(partid[j] == leptonNum and ((parent1[j] == 3 and status[j] != 21) ||
				     (status[parent1[j]-1] == 21 and partid[parent1[j]-1] == leptonNum))) {*tau = *part; *tauM2 = *partM2;}

      else if(partid[j] == -leptonNum and ((parent1[j] == 3 and status[j] != 21) ||
					   (status[parent1[j]-1] == 21 and partid[parent1[j]-1] == -leptonNum))) {*antitau = *part; *antitauM2 = *partM2;}

      else if(partid[j] == 22 and  parent1[j] == 1 ) {*gamma1 = *part; *gamma1M2 = *partM2;}
      else if(partid[j] == 22 and parent1[j] == 2) {*gamma2 = *part; *gamma2M2 = *partM2;}
      else if(partid[j] == 2212 and parent1[j] == 1) {*proton1 = *part; *proton1M2 = *partM2;}
      else if(partid[j] == 2212 and parent1[j] == 2) {*proton2 = *part; *proton2M2 = *partM2;}

      // if (i%50000==0) cout  << "part " << j <<" lvector: " <<px[j] << " " << py[j] << " " << pz[j] << " " <<
      // 		       en[j] << "\npart pt, eta, id, status, parent, mass: " << pt[j] << " " << eta[j] << " " <<
      // 		       partid[j] << " " << status[j] << " " <<
      // 		       parent1[j] << " " << part->M() << endl;
    }
    // if(i%50000==0) cout << "Event " << i << " of " << nevts << endl;

    *tauSys = *tau+*antitau;
    *gammaSys = *gamma1+*gamma2;
    *tauSysM2 = *tauM2+*antitauM2;
    *gammaSysM2 = *gamma1M2+*gamma2M2;
    //CMS-Totem paper definition of acoplanarity 
    acoplane = abs(1-abs(tau->Phi()-antitau->Phi())/3.141592654);

    fracLossPlus = 1/sqrtS*(tau->Pt()*exp(tau->Eta())+antitau->Pt()*exp(antitau->Eta()));
    fracLossMinus = 1/sqrtS*(tau->Pt()*exp(-1*tau->Eta())+antitau->Pt()*exp(-1*antitau->Eta()));
    ptM = (tau->Pt() + antitau->Pt()) / tauSys->M();
    Double_t leadPt  = (tau->Pt() > antitau->Pt()) ? tau->Pt() : antitau->Pt();
    Double_t trailPt = (tau->Pt() < antitau->Pt()) ? tau->Pt() : antitau->Pt();
    ptRatio = leadPt / trailPt;
    
    //kinematic cut filling
    fillHistograms(0);

    drellTester->Fill(0.,1./nevts);
    if(sets[53] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4) {
      drellTester->Fill(1.0,1./nevts);
      if(leadPt > 30) {
	drellTester->Fill(2.,1./nevts);
	if(trailPt > 10) {
	  drellTester->Fill(3.,1./nevts);
	  if(tauSys->M() < 80) {
	    drellTester->Fill(4.0,1./nevts);
	    if(tauSys->M() > 50) {
	      drellTester->Fill(5.0,1./nevts);
	      if(acoplane < 0.006) {
		drellTester->Fill(6.,1./nevts); //no jet check in lpair files
		drellTester->Fill(7.,1./nevts);
	        fillHistograms(53);
	      }
	    }
	  }
	}
      }
    }
    
    if(sets[54] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4) {
      if(tauSys->M() < 50) {
	if(tauSys->M() > 10) {
	  if(acoplane < 0.006) {
	    if(leadPt > 30) {
	      if(trailPt > 10) {
		fillHistograms(54);
	      }
	    }
	  }
	}
      }
    }
    
    if(sets[55] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4 and
       tauSys->M() < 80 and acoplane < 0.006 and leadPt > 30 and trailPt > 10) fillHistograms(55);
    
    //no mass requirements
    if(abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4 and tau->Pt() > 20 and antitau->Pt() > 20) {
      if(sets[41]) fillHistograms(41);
      if(sets[43] and acoplane < 0.009) fillHistograms(43);
      if(sets[44] and acoplane < 0.006) fillHistograms(44);
      if(sets[50] and acoplane < 0.006 and (tau->Pt()/antitau->Pt() > 0.95) and (antitau->Pt()/tau->Pt() > 0.95)) fillHistograms(50);
      if(sets[51] and acoplane < 0.006 and tauSys->M() < 80.0 and tauSys->M() > 50.0) fillHistograms(51);
      if(sets[52] and acoplane < 0.006 and tauSys->M() < 50.0 and tauSys->M() > 10.0) fillHistograms(52);
      if(tau->Pt() > 33 and antitau->Pt() > 33) {
	if(sets[42]) fillHistograms(42);
	if(sets[45] and acoplane < 0.009) fillHistograms(45);
	if(sets[46] and acoplane < 0.006) fillHistograms(46);
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
	      if(sets[9] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4){
		fillHistograms(9);
		if(sets[11] and (fracLossPlus > 0.032 or fracLossMinus > 0.024)) fillHistograms(11);
	      }
	      if(acoplane < 0.006) {
		if(sets[10] and abs(tau->Eta()) < 2.4 and abs(antitau->Eta()) < 2.4) {
		  fillHistograms(10);
		  if(sets[12] and (fracLossPlus > 0.032 or fracLossMinus > 0.024)) fillHistograms(12);
		  if(sets[15] and (tau->Pt()/antitau->Pt() > 0.95) and (antitau->Pt()/tau->Pt() > 0.95)) fillHistograms(15);
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
  cout << "***Number of events, cross section (fb), percent passing each cut, and each cuts cross section:\n";
  for(int i = 0; i < n; i++) {
    if(sets[i]){
      cout << "Set number " << i << ": " << nevts << ", " << xsec*1000 << ", " <<
	(((cnt[i])*100.0)/nevts) << ", " << (((cnt[i])*1000.0)/nevts)*xsec << endl;
    }
  }
  //write trees after done with event loop
  writeHistograms();  
}
