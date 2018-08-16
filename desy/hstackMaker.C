#include "TH1.h"
#include "THStack.h"

void pngWriter(THStack* h, TString xtitle, TString ytitle, TString outfile, TH1* h1, TH1* h2) {
  TCanvas* c1 = new TCanvas("c1", "Lepton System");
  h->Draw("HIST");
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  TLegend *legend = new TLegend(0.6,0.7,0.89,0.89);
  legend->AddEntry(h1,"Semi-Exclusive");
  legend->AddEntry(h2,"Exclusive");
  legend->SetHeader("Processes");
  legend->Draw();
  c1->Modified();
  c1->Update();
  TImage* img = TImage::Create();
  img->FromPad(c1);
  img->WriteImage(outfile);
  delete c1;
  delete img;
}

//assumes you called something like
//"root.exe /media/michael/Seagate\ Exp/UBUNTU/LPair/lpair/desy/Data/events_full_*Pt10.root" 
//before doing .L hstackMaker
// hstackMaker()
void hstackMaker(){
  TH1* massH10_0  = (TH1F*) _file0->Get("massH1_10");
  TH1* massH10_1  = (TH1F*) _file1->Get("massH1_10");
  TH1* massH10_2  = (TH1F*) _file2->Get("massH1_10");
  TH1* massH10_3  = (TH1F*) _file3->Get("massH1_10");
  TH1* massH10_4  = (TH1F*) _file4->Get("massH1_10");
  TH1* massH10_5  = (TH1F*) _file5->Get("massH1_10");
		 
  TH1* massH9_0   = (TH1F*) _file0->Get("massH1_9") ;
  TH1* massH9_1   = (TH1F*) _file1->Get("massH1_9") ;
  TH1* massH9_2   = (TH1F*) _file2->Get("massH1_9") ;
  TH1* massH9_3   = (TH1F*) _file3->Get("massH1_9") ; 
  TH1* massH9_4   = (TH1F*) _file4->Get("massH1_9") ;
  TH1* massH9_5   = (TH1F*) _file5->Get("massH1_9") ;

  TH1* massH241_0 = (TH1F*) _file0->Get("massH2_41");
  TH1* massH241_1 = (TH1F*) _file1->Get("massH2_41");
  TH1* massH241_2 = (TH1F*) _file2->Get("massH2_41");
  TH1* massH241_3 = (TH1F*) _file3->Get("massH2_41");
  TH1* massH241_4 = (TH1F*) _file4->Get("massH2_41");
  TH1* massH241_5 = (TH1F*) _file5->Get("massH2_41");

  TH1* massH41_0  = (TH1F*) _file0->Get("massH1_41");
  TH1* massH41_1  = (TH1F*) _file1->Get("massH1_41");
  TH1* massH41_2  = (TH1F*) _file2->Get("massH1_41");
  TH1* massH41_3  = (TH1F*) _file3->Get("massH1_41");
  TH1* massH41_4  = (TH1F*) _file4->Get("massH1_41");
  TH1* massH41_5  = (TH1F*) _file5->Get("massH1_41");

  massH10_0->Rebin(10);
  massH10_1->Rebin(10);
  massH10_2->Rebin(10);
  massH10_3->Rebin(10);
  massH10_4->Rebin(10);
  massH10_5->Rebin(10);
  	   
  massH9_0->Rebin(10);
  massH9_1->Rebin(10);
  massH9_2->Rebin(10);
  massH9_3->Rebin(10); 
  massH9_4->Rebin(10);
  massH9_5->Rebin(10);
	    
  massH241_0->Rebin(10);
  massH241_1->Rebin(10);
  massH241_2->Rebin(10);
  massH241_3->Rebin(10);
  massH241_4->Rebin(10);
  massH241_5->Rebin(10);
	    
  massH41_0->Rebin(10);
  massH41_1->Rebin(10);
  massH41_2->Rebin(10);
  massH41_3->Rebin(10);
  massH41_4->Rebin(10);
  massH41_5->Rebin(10);
     
  THStack* massH10_E  = new THStack("massH10_E", "Invariant Mass of Electron System");
  THStack* massH10_M  = new THStack("massH10_M", "Invariant Mass of Muon System");
  THStack* massH10_T  = new THStack("massH10_T", "Invariant Mass of Tau System");
 
  THStack* massH9_E   = new THStack("massH9_E", "Invariant Mass of Electron System");
  THStack* massH9_M   = new THStack("massH9_M", "Invariant Mass of Muon System");
  THStack* massH9_T   = new THStack("massH9_T", "Invariant Mass of Tau System");

  THStack* massH41_E  = new THStack("massH41_E", "Invariant Mass of Electron System");
  THStack* massH41_M  = new THStack("massH41_M", "Invariant Mass of Muon System");
  THStack* massH41_T  = new THStack("massH41_T", "Invariant Mass of Tau System");

  THStack* massH241_E = new THStack("mass2H41_E", "Invariant Mass of Electron System");
  THStack* massH241_M = new THStack("mass2H41_M", "Invariant Mass of Muon System");
  THStack* massH241_T = new THStack("mass2H41_T", "Invariant Mass of Tau System");

  massH10_0->SetFillColor(kSpring-8);
  massH10_1->SetFillColor(kAzure+2);
  massH10_2->SetFillColor(kSpring-8);
  massH10_3->SetFillColor(kAzure+2);
  massH10_4->SetFillColor(kSpring-8);
  massH10_5->SetFillColor(kAzure+2);

  massH9_0->SetFillColor(kSpring-8);
  massH9_1->SetFillColor(kAzure+2);
  massH9_2->SetFillColor(kSpring-8);
  massH9_3->SetFillColor(kAzure+2);
  massH9_4->SetFillColor(kSpring-8);
  massH9_5->SetFillColor(kAzure+2);

  massH41_0->SetFillColor(kSpring-8);
  massH41_1->SetFillColor(kAzure+2);
  massH41_2->SetFillColor(kSpring-8);
  massH41_3->SetFillColor(kAzure+2);
  massH41_4->SetFillColor(kSpring-8);
  massH41_5->SetFillColor(kAzure+2);

  massH241_0->SetFillColor(kSpring-8);
  massH241_1->SetFillColor(kAzure+2);
  massH241_2->SetFillColor(kSpring-8);
  massH241_3->SetFillColor(kAzure+2);
  massH241_4->SetFillColor(kSpring-8);
  massH241_5->SetFillColor(kAzure+2);

  massH10_E->Add(massH10_0);
  massH10_E->Add(massH10_1);

  massH10_M->Add(massH10_2);
  massH10_M->Add(massH10_3);

  massH10_T->Add(massH10_4);
  massH10_T->Add(massH10_5);

  massH9_E->Add(massH9_0);
  massH9_E->Add(massH9_1);

  massH9_M->Add(massH9_2);
  massH9_M->Add(massH9_3);

  massH9_T->Add(massH9_4);
  massH9_T->Add(massH9_5);

  massH41_E->Add(massH41_0);
  massH41_E->Add(massH41_1);
     		    
  massH41_M->Add(massH41_2);
  massH41_M->Add(massH41_3);
     		    
  massH41_T->Add(massH41_4);
  massH41_T->Add(massH41_5);
  
  massH241_E->Add(massH241_0);
  massH241_E->Add(massH241_1);
     		    
  massH241_M->Add(massH241_2);
  massH241_M->Add(massH241_3);
     		    
  massH241_T->Add(massH241_4);
  massH241_T->Add(massH241_5);

  TH1* rapidityH10_0 = (TH1F*) _file0->Get("rapidityH_10");
  TH1* rapidityH10_1 = (TH1F*) _file1->Get("rapidityH_10");
  TH1* rapidityH10_2 = (TH1F*) _file2->Get("rapidityH_10");
  TH1* rapidityH10_3 = (TH1F*) _file3->Get("rapidityH_10");
  TH1* rapidityH10_4 = (TH1F*) _file4->Get("rapidityH_10");
  TH1* rapidityH10_5 = (TH1F*) _file5->Get("rapidityH_10");

  TH1* rapidityH9_0  = (TH1F*) _file0->Get("rapidityH_9");
  TH1* rapidityH9_1  = (TH1F*) _file1->Get("rapidityH_9");
  TH1* rapidityH9_2  = (TH1F*) _file2->Get("rapidityH_9");
  TH1* rapidityH9_3  = (TH1F*) _file3->Get("rapidityH_9");
  TH1* rapidityH9_4  = (TH1F*) _file4->Get("rapidityH_9");
  TH1* rapidityH9_5  = (TH1F*) _file5->Get("rapidityH_9");

  TH1* rapidityH41_0 = (TH1F*) _file0->Get("rapidityH_41");
  TH1* rapidityH41_1 = (TH1F*) _file1->Get("rapidityH_41");
  TH1* rapidityH41_2 = (TH1F*) _file2->Get("rapidityH_41");
  TH1* rapidityH41_3 = (TH1F*) _file3->Get("rapidityH_41");
  TH1* rapidityH41_4 = (TH1F*) _file4->Get("rapidityH_41");
  TH1* rapidityH41_5 = (TH1F*) _file5->Get("rapidityH_41");

  rapidityH10_0->Rebin(10);
  rapidityH10_1->Rebin(10);
  rapidityH10_2->Rebin(10);
  rapidityH10_3->Rebin(10);
  rapidityH10_4->Rebin(10);
  rapidityH10_5->Rebin(10);
  	   
  rapidityH9_0->Rebin(10);
  rapidityH9_1->Rebin(10);
  rapidityH9_2->Rebin(10);
  rapidityH9_3->Rebin(10); 
  rapidityH9_4->Rebin(10);
  rapidityH9_5->Rebin(10);

  rapidityH41_0->Rebin(10);
  rapidityH41_1->Rebin(10);
  rapidityH41_2->Rebin(10);
  rapidityH41_3->Rebin(10);
  rapidityH41_4->Rebin(10);
  rapidityH41_5->Rebin(10);
  
  THStack* rapidityH10_E = new THStack("rapidityH10_E", "Rapidity of Electron System");
  THStack* rapidityH10_M = new THStack("rapidityH10_M", "Rapidity of Muon System");
  THStack* rapidityH10_T = new THStack("rapidityH10_T", "Rapidity of Tau System");

  THStack* rapidityH9_E  = new THStack("rapidityH9_E", "Rapidity of Electron System");
  THStack* rapidityH9_M  = new THStack("rapidityH9_M", "Rapidity of Muon System");
  THStack* rapidityH9_T  = new THStack("rapidityH9_T", "Rapidity of Tau System");

  THStack* rapidityH41_E = new THStack("rapidityH41_E", "Rapidity of Electron System");
  THStack* rapidityH41_M = new THStack("rapidityH41_M", "Rapidity of Muon System");
  THStack* rapidityH41_T = new THStack("rapidityH41_T", "Rapidity of Tau System");  
  
  rapidityH10_0->SetFillColor(kSpring-8);
  rapidityH10_1->SetFillColor(kAzure+2);
  rapidityH10_2->SetFillColor(kSpring-8);
  rapidityH10_3->SetFillColor(kAzure+2);
  rapidityH10_4->SetFillColor(kSpring-8);
  rapidityH10_5->SetFillColor(kAzure+2);

  rapidityH9_0->SetFillColor(kSpring-8);
  rapidityH9_1->SetFillColor(kAzure+2);
  rapidityH9_2->SetFillColor(kSpring-8);
  rapidityH9_3->SetFillColor(kAzure+2);
  rapidityH9_4->SetFillColor(kSpring-8);
  rapidityH9_5->SetFillColor(kAzure+2);

  rapidityH41_0->SetFillColor(kSpring-8);
  rapidityH41_1->SetFillColor(kAzure+2);
  rapidityH41_2->SetFillColor(kSpring-8);
  rapidityH41_3->SetFillColor(kAzure+2);
  rapidityH41_4->SetFillColor(kSpring-8);
  rapidityH41_5->SetFillColor(kAzure+2);

  rapidityH10_E->Add(rapidityH10_0);
  rapidityH10_E->Add(rapidityH10_1);

  rapidityH10_M->Add(rapidityH10_2);
  rapidityH10_M->Add(rapidityH10_3);

  rapidityH10_T->Add(rapidityH10_4);
  rapidityH10_T->Add(rapidityH10_5);

  rapidityH9_E->Add(rapidityH9_0);
  rapidityH9_E->Add(rapidityH9_1);

  rapidityH9_M->Add(rapidityH9_2);
  rapidityH9_M->Add(rapidityH9_3);

  rapidityH9_T->Add(rapidityH9_4);
  rapidityH9_T->Add(rapidityH9_5);

  rapidityH41_E->Add(rapidityH41_0);
  rapidityH41_E->Add(rapidityH41_1);
     		    
  rapidityH41_M->Add(rapidityH41_2);
  rapidityH41_M->Add(rapidityH41_3);
     		    
  rapidityH41_T->Add(rapidityH41_4);
  rapidityH41_T->Add(rapidityH41_5);

  
  TFile* out = new TFile("hstack.root","RECREATE");

  pngWriter(massH9_E,  "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH9_E.png",   massH9_0,  massH9_1); 
  pngWriter(massH9_M,  "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH9_M.png",   massH9_2,  massH9_3); 
  pngWriter(massH9_T,  "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH9_T.png",   massH9_4,  massH9_5); 
  pngWriter(massH10_E, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH10_E.png",  massH10_0, massH10_1); 
  pngWriter(massH10_M, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH10_M.png",  massH10_2, massH10_3); 
  pngWriter(massH10_T, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH10_T.png",  massH10_4, massH10_5); 
  pngWriter(massH41_E, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH41_E.png",  massH41_0, massH41_1); 
  pngWriter(massH41_M, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH41_M.png",  massH41_2, massH41_3); 
  pngWriter(massH41_T, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH41_T.png",  massH41_4, massH41_5); 
  pngWriter(massH241_E,"Lepton System Invariant Mass (GeV)","Events / 10 GeV", "massH241_E.png", massH41_0, massH241_1); 
  pngWriter(massH241_M,"Lepton System Invariant Mass (GeV)","Events / 10 GeV", "massH241_M.png", massH41_2, massH241_3); 
  pngWriter(massH241_T,"Lepton System Invariant Mass (GeV)","Events / 10 GeV", "massH241_T.png", massH41_4, massH241_5); 
  
  massH10_T->Write();
  massH10_M->Write();
  massH10_E->Write();
  massH9_T->Write();
  massH9_M->Write();
  massH9_E->Write();
  massH41_T->Write();
  massH41_M->Write();
  massH41_E->Write();
  massH241_T->Write();
  massH241_M->Write();
  massH241_E->Write();

  pngWriter(rapidityH9_E,  "Lepton System Rapidity","Events / 0.5", "rapidityH9_E.png",  rapidityH9_0,  rapidityH9_1); 
  pngWriter(rapidityH9_M,  "Lepton System Rapidity","Events / 0.5", "rapidityH9_M.png",  rapidityH9_2,  rapidityH9_3); 
  pngWriter(rapidityH9_T,  "Lepton System Rapidity","Events / 0.5", "rapidityH9_T.png",  rapidityH9_4,  rapidityH9_5); 
  pngWriter(rapidityH10_E, "Lepton System Rapidity","Events / 0.5", "rapidityH10_E.png", rapidityH10_0, rapidityH10_1); 
  pngWriter(rapidityH10_M, "Lepton System Rapidity","Events / 0.5", "rapidityH10_M.png", rapidityH10_2, rapidityH10_3); 
  pngWriter(rapidityH10_T, "Lepton System Rapidity","Events / 0.5", "rapidityH10_T.png", rapidityH10_4, rapidityH10_5); 
  pngWriter(rapidityH41_E, "Lepton System Rapidity","Events / 0.5", "rapidityH41_E.png", rapidityH41_0, rapidityH41_1); 
  pngWriter(rapidityH41_M, "Lepton System Rapidity","Events / 0.5", "rapidityH41_M.png", rapidityH41_2, rapidityH41_3); 
  pngWriter(rapidityH41_T, "Lepton System Rapidity","Events / 0.5", "rapidityH41_T.png", rapidityH41_4, rapidityH41_5); 

  rapidityH10_T->Write();
  rapidityH10_M->Write();
  rapidityH10_E->Write();
  rapidityH9_T->Write();
  rapidityH9_M->Write();
  rapidityH9_E->Write();
  rapidityH41_T->Write();
  rapidityH41_M->Write();
  rapidityH41_E->Write();
}
