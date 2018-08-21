#include "TH1.h"
#include "THStack.h"

void pngWriter(THStack* h, TString xtitle, TString ytitle, TString outfile, TH1* h1, TH1* h2, TH1* h3) {
  TCanvas* c1 = new TCanvas("c1", "Lepton System");
  h->Draw("HIST");
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  TLegend *legend = new TLegend(0.6,0.7,0.89,0.89);
  if(h3!=0) legend->AddEntry(h3, "Drell Yan");
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
void hstackMaker(Int_t drellYan = 1, Int_t writeImages = 1){

  TFile* file0 = new TFile("Data/events_full_electron_disassociate_MinE20_MinPt10.root");
  TFile* file1 = new TFile("Data/events_full_electron_elastic_MinE20_MinPt10.root");
  TFile* file2 = new TFile("Data/events_full_muon_disassociate_MinE20_MinPt10.root");
  TFile* file3 = new TFile("Data/events_full_muon_elastic_MinE20_MinPt10.root");
  TFile* file4 = new TFile("Data/events_full_tau_disassociate_MinE20_MinPt10.root");
  TFile* file5 = new TFile("Data/events_full_tau_elastic_MinE20_MinPt10.root");
  TFile* file6;
  TFile* file7;
  if(drellYan) {
    file6      = new TFile("Data/events_full_electron_DrellYan.root");
    file7      = new TFile("Data/events_full_muon_DrellYan.root");
  }
  
  TFile* data0 = (TFile*) file0->Get("Data");
  TFile* data1 = (TFile*) file1->Get("Data");
  TFile* data2 = (TFile*) file2->Get("Data");
  TFile* data3 = (TFile*) file3->Get("Data");
  TFile* data4 = (TFile*) file4->Get("Data");
  TFile* data5 = (TFile*) file5->Get("Data");
  TFile* data6;
  TFile* data7;
  if(drellYan) {data6 = (TFile*) file6->Get("Data"); data7 = (TFile*) file7->Get("Data");}

  TH1* massH10_0   = (TH1F*) ((TFile*) data0->Get("book_10"))->Get("massH1_10");
  TH1* massH10_1   = (TH1F*) ((TFile*) data1->Get("book_10"))->Get("massH1_10");
  TH1* massH10_2   = (TH1F*) ((TFile*) data2->Get("book_10"))->Get("massH1_10");
  TH1* massH10_3   = (TH1F*) ((TFile*) data3->Get("book_10"))->Get("massH1_10");
  TH1* massH10_4   = (TH1F*) ((TFile*) data4->Get("book_10"))->Get("massH1_10");
  TH1* massH10_5   = (TH1F*) ((TFile*) data5->Get("book_10"))->Get("massH1_10");
  TH1* massH10_6 = 0;
  TH1* massH10_7 = 0;
  if(drellYan) {
    massH10_6      = (TH1F*) ((TFile*) data6->Get("book_14"))->Get("massH1_14");
    massH10_7      = (TH1F*) ((TFile*) data7->Get("book_14"))->Get("massH1_14");
  }
  
  TH1* massH9_0    = (TH1F*) ((TFile*) data0->Get("book_9"))->Get("massH1_9");
  TH1* massH9_1    = (TH1F*) ((TFile*) data1->Get("book_9"))->Get("massH1_9");
  TH1* massH9_2    = (TH1F*) ((TFile*) data2->Get("book_9"))->Get("massH1_9");
  TH1* massH9_3    = (TH1F*) ((TFile*) data3->Get("book_9"))->Get("massH1_9");
  TH1* massH9_4    = (TH1F*) ((TFile*) data4->Get("book_9"))->Get("massH1_9");
  TH1* massH9_5    = (TH1F*) ((TFile*) data5->Get("book_9"))->Get("massH1_9");
  TH1* massH9_6 = 0;
  TH1* massH9_7 = 0;
  if(drellYan) {
    massH9_6       = (TH1F*) ((TFile*) data6->Get("book_13"))->Get("massH1_13");
    massH9_7       = (TH1F*) ((TFile*) data7->Get("book_13"))->Get("massH1_13");
  }
  
  TH1* massH241_0  = (TH1F*) ((TFile*) data0->Get("book_44"))->Get("massH2_44");
  TH1* massH241_1  = (TH1F*) ((TFile*) data1->Get("book_44"))->Get("massH2_44");
  TH1* massH241_2  = (TH1F*) ((TFile*) data2->Get("book_44"))->Get("massH2_44");
  TH1* massH241_3  = (TH1F*) ((TFile*) data3->Get("book_44"))->Get("massH2_44");
  TH1* massH241_4  = (TH1F*) ((TFile*) data4->Get("book_44"))->Get("massH2_44");
  TH1* massH241_5  = (TH1F*) ((TFile*) data5->Get("book_44"))->Get("massH2_44");
  TH1* massH241_6 = 0;
  TH1* massH241_7 = 0;
  if(drellYan) {
    massH241_6     = (TH1F*) ((TFile*) data6->Get("book_47"))->Get("massH2_47");
    massH241_7     = (TH1F*) ((TFile*) data7->Get("book_47"))->Get("massH2_47");
  }
						   
  TH1* massH41_0   = (TH1F*) ((TFile*) data0->Get("book_44"))->Get("massH1_44");
  TH1* massH41_1   = (TH1F*) ((TFile*) data1->Get("book_44"))->Get("massH1_44");
  TH1* massH41_2   = (TH1F*) ((TFile*) data2->Get("book_44"))->Get("massH1_44");
  TH1* massH41_3   = (TH1F*) ((TFile*) data3->Get("book_44"))->Get("massH1_44");
  TH1* massH41_4   = (TH1F*) ((TFile*) data4->Get("book_44"))->Get("massH1_44");
  TH1* massH41_5   = (TH1F*) ((TFile*) data5->Get("book_44"))->Get("massH1_44");
  TH1* massH41_6 = 0;
  TH1* massH41_7 = 0;
  if(drellYan) {
    massH41_6      = (TH1F*) ((TFile*) data6->Get("book_47"))->Get("massH1_47");
    massH41_7      = (TH1F*) ((TFile*) data7->Get("book_47"))->Get("massH1_47");
  }

  massH10_0->Rebin(10);
  massH10_1->Rebin(10);
  massH10_2->Rebin(10);
  massH10_3->Rebin(10);
  massH10_4->Rebin(10);
  massH10_5->Rebin(10);
  if(drellYan) massH10_6->Rebin(10);
  if(drellYan) massH10_7->Rebin(10);
  	   
  massH9_0->Rebin(10);
  massH9_1->Rebin(10);
  massH9_2->Rebin(10);
  massH9_3->Rebin(10); 
  massH9_4->Rebin(10);
  massH9_5->Rebin(10);
  if(drellYan) massH9_6->Rebin(10);
  if(drellYan) massH9_7->Rebin(10);
	    
  massH241_0->Rebin(10);
  massH241_1->Rebin(10);
  massH241_2->Rebin(10);
  massH241_3->Rebin(10);
  massH241_4->Rebin(10);
  massH241_5->Rebin(10);
  if(drellYan) massH241_6->Rebin(10);
  if(drellYan) massH241_7->Rebin(10);
	    
  massH41_0->Rebin(10);
  massH41_1->Rebin(10);
  massH41_2->Rebin(10);
  massH41_3->Rebin(10);
  massH41_4->Rebin(10);
  massH41_5->Rebin(10);
  if(drellYan) massH41_6->Rebin(10);
  if(drellYan) massH41_7->Rebin(10);
     
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
  if(drellYan) massH10_6->SetFillColor(kRed+1);
  if(drellYan) massH10_7->SetFillColor(kRed+1);

  massH9_0->SetFillColor(kSpring-8);
  massH9_1->SetFillColor(kAzure+2);
  massH9_2->SetFillColor(kSpring-8);
  massH9_3->SetFillColor(kAzure+2);
  massH9_4->SetFillColor(kSpring-8);
  massH9_5->SetFillColor(kAzure+2);
  if(drellYan) massH9_6->SetFillColor(kRed+1);
  if(drellYan) massH9_7->SetFillColor(kRed+1);

  massH41_0->SetFillColor(kSpring-8);
  massH41_1->SetFillColor(kAzure+2);
  massH41_2->SetFillColor(kSpring-8);
  massH41_3->SetFillColor(kAzure+2);
  massH41_4->SetFillColor(kSpring-8);
  massH41_5->SetFillColor(kAzure+2);
  if(drellYan) massH41_6->SetFillColor(kRed+1);
  if(drellYan) massH41_7->SetFillColor(kRed+1);

  massH241_0->SetFillColor(kSpring-8);
  massH241_1->SetFillColor(kAzure+2);
  massH241_2->SetFillColor(kSpring-8);
  massH241_3->SetFillColor(kAzure+2);
  massH241_4->SetFillColor(kSpring-8);
  massH241_5->SetFillColor(kAzure+2);
  if(drellYan) massH241_6->SetFillColor(kRed+1);
  if(drellYan) massH241_7->SetFillColor(kRed+1);

  if(drellYan) massH10_E->Add(massH10_6);
  massH10_E->Add(massH10_0);
  massH10_E->Add(massH10_1);


  if(drellYan) massH10_M->Add(massH10_7);
  massH10_M->Add(massH10_2);
  massH10_M->Add(massH10_3);

  massH10_T->Add(massH10_4);
  massH10_T->Add(massH10_5);

  if(drellYan) massH9_E->Add(massH9_6);
  massH9_E->Add(massH9_0);
  massH9_E->Add(massH9_1);

  if(drellYan) massH9_M->Add(massH9_7);
  massH9_M->Add(massH9_2);
  massH9_M->Add(massH9_3);

  massH9_T->Add(massH9_4);
  massH9_T->Add(massH9_5);

  if(drellYan) massH41_E->Add(massH41_6);
  massH41_E->Add(massH41_0);
  massH41_E->Add(massH41_1);
     		    
  if(drellYan) massH41_M->Add(massH41_7);
  massH41_M->Add(massH41_2);
  massH41_M->Add(massH41_3);
     		    
  massH41_T->Add(massH41_4);
  massH41_T->Add(massH41_5);
  
  if(drellYan) massH241_E->Add(massH241_6);
  massH241_E->Add(massH241_0);
  massH241_E->Add(massH241_1);
     		    
  if(drellYan) massH241_M->Add(massH241_7);
  massH241_M->Add(massH241_2);
  massH241_M->Add(massH241_3);
     		    
  massH241_T->Add(massH241_4);
  massH241_T->Add(massH241_5);

  TH1* rapidityH10_0   = (TH1F*) ((TFile*) data0->Get("book_10"))->Get("rapidityH_10");
  TH1* rapidityH10_1   = (TH1F*) ((TFile*) data1->Get("book_10"))->Get("rapidityH_10");
  TH1* rapidityH10_2   = (TH1F*) ((TFile*) data2->Get("book_10"))->Get("rapidityH_10");
  TH1* rapidityH10_3   = (TH1F*) ((TFile*) data3->Get("book_10"))->Get("rapidityH_10");
  TH1* rapidityH10_4   = (TH1F*) ((TFile*) data4->Get("book_10"))->Get("rapidityH_10");
  TH1* rapidityH10_5   = (TH1F*) ((TFile*) data5->Get("book_10"))->Get("rapidityH_10");
  TH1* rapidityH10_6 = 0;
  TH1* rapidityH10_7 = 0;
  if(drellYan) {
    rapidityH10_6      = (TH1F*) ((TFile*) data6->Get("book_14"))->Get("rapidityH_14");
    rapidityH10_7      = (TH1F*) ((TFile*) data7->Get("book_14"))->Get("rapidityH_14");
  }
  
  TH1* rapidityH9_0    = (TH1F*) ((TFile*) data0->Get("book_9"))->Get("rapidityH_9");
  TH1* rapidityH9_1    = (TH1F*) ((TFile*) data1->Get("book_9"))->Get("rapidityH_9");
  TH1* rapidityH9_2    = (TH1F*) ((TFile*) data2->Get("book_9"))->Get("rapidityH_9");
  TH1* rapidityH9_3    = (TH1F*) ((TFile*) data3->Get("book_9"))->Get("rapidityH_9");
  TH1* rapidityH9_4    = (TH1F*) ((TFile*) data4->Get("book_9"))->Get("rapidityH_9");
  TH1* rapidityH9_5    = (TH1F*) ((TFile*) data5->Get("book_9"))->Get("rapidityH_9");
  TH1* rapidityH9_6 = 0;
  TH1* rapidityH9_7 = 0;
  if(drellYan) {
    rapidityH9_6       = (TH1F*) ((TFile*) data6->Get("book_13"))->Get("rapidityH_13");
    rapidityH9_7       = (TH1F*) ((TFile*) data7->Get("book_13"))->Get("rapidityH_13");
  }
						   
  TH1* rapidityH41_0   = (TH1F*) ((TFile*) data0->Get("book_44"))->Get("rapidityH_44");
  TH1* rapidityH41_1   = (TH1F*) ((TFile*) data1->Get("book_44"))->Get("rapidityH_44");
  TH1* rapidityH41_2   = (TH1F*) ((TFile*) data2->Get("book_44"))->Get("rapidityH_44");
  TH1* rapidityH41_3   = (TH1F*) ((TFile*) data3->Get("book_44"))->Get("rapidityH_44");
  TH1* rapidityH41_4   = (TH1F*) ((TFile*) data4->Get("book_44"))->Get("rapidityH_44");
  TH1* rapidityH41_5   = (TH1F*) ((TFile*) data5->Get("book_44"))->Get("rapidityH_44");
  TH1* rapidityH41_6 = 0;
  TH1* rapidityH41_7 = 0;
  if(drellYan) {
    rapidityH41_6      = (TH1F*) ((TFile*) data6->Get("book_47"))->Get("rapidityH_47");
    rapidityH41_7      = (TH1F*) ((TFile*) data7->Get("book_47"))->Get("rapidityH_47");
  }

  rapidityH10_0->Rebin(10);
  rapidityH10_1->Rebin(10);
  rapidityH10_2->Rebin(10);
  rapidityH10_3->Rebin(10);
  rapidityH10_4->Rebin(10);
  rapidityH10_5->Rebin(10);
  if(drellYan) rapidityH10_6->Rebin(10);
  if(drellYan) rapidityH10_7->Rebin(10);
  	   
  rapidityH9_0->Rebin(10);
  rapidityH9_1->Rebin(10);
  rapidityH9_2->Rebin(10);
  rapidityH9_3->Rebin(10); 
  rapidityH9_4->Rebin(10);
  rapidityH9_5->Rebin(10);
  if(drellYan) rapidityH9_6->Rebin(10);
  if(drellYan) rapidityH9_7->Rebin(10);
	    
  rapidityH41_0->Rebin(10);
  rapidityH41_1->Rebin(10);
  rapidityH41_2->Rebin(10);
  rapidityH41_3->Rebin(10);
  rapidityH41_4->Rebin(10);
  rapidityH41_5->Rebin(10);
  if(drellYan) rapidityH41_6->Rebin(10);
  if(drellYan) rapidityH41_7->Rebin(10);
     
  THStack* rapidityH10_E  = new THStack("rapidityH10_E", "Rapidity of Electron System");
  THStack* rapidityH10_M  = new THStack("rapidityH10_M", "Rapidity of Muon System");
  THStack* rapidityH10_T  = new THStack("rapidityH10_T", "Rapidity of Tau System");
 
  THStack* rapidityH9_E   = new THStack("rapidityH9_E", "Rapidity of Electron System");
  THStack* rapidityH9_M   = new THStack("rapidityH9_M", "Rapidity of Muon System");
  THStack* rapidityH9_T   = new THStack("rapidityH9_T", "Rapidity of Tau System");

  THStack* rapidityH41_E  = new THStack("rapidityH41_E", "Rapidity of Electron System");
  THStack* rapidityH41_M  = new THStack("rapidityH41_M", "Rapidity of Muon System");
  THStack* rapidityH41_T  = new THStack("rapidityH41_T", "Rapidity of Tau System");

  THStack* rapidityH241_E = new THStack("rapidity2H41_E", "Rapidity of Electron System");
  THStack* rapidityH241_M = new THStack("rapidity2H41_M", "Rapidity of Muon System");
  THStack* rapidityH241_T = new THStack("rapidity2H41_T", "Rapidity of Tau System");

  rapidityH10_0->SetFillColor(kSpring-8);
  rapidityH10_1->SetFillColor(kAzure+2);
  rapidityH10_2->SetFillColor(kSpring-8);
  rapidityH10_3->SetFillColor(kAzure+2);
  rapidityH10_4->SetFillColor(kSpring-8);
  rapidityH10_5->SetFillColor(kAzure+2);
  if(drellYan) rapidityH10_6->SetFillColor(kRed+1);
  if(drellYan) rapidityH10_7->SetFillColor(kRed+1);

  rapidityH9_0->SetFillColor(kSpring-8);
  rapidityH9_1->SetFillColor(kAzure+2);
  rapidityH9_2->SetFillColor(kSpring-8);
  rapidityH9_3->SetFillColor(kAzure+2);
  rapidityH9_4->SetFillColor(kSpring-8);
  rapidityH9_5->SetFillColor(kAzure+2);
  if(drellYan) rapidityH9_6->SetFillColor(kRed+1);
  if(drellYan) rapidityH9_7->SetFillColor(kRed+1);

  rapidityH41_0->SetFillColor(kSpring-8);
  rapidityH41_1->SetFillColor(kAzure+2);
  rapidityH41_2->SetFillColor(kSpring-8);
  rapidityH41_3->SetFillColor(kAzure+2);
  rapidityH41_4->SetFillColor(kSpring-8);
  rapidityH41_5->SetFillColor(kAzure+2);
  if(drellYan) rapidityH41_6->SetFillColor(kRed+1);
  if(drellYan) rapidityH41_7->SetFillColor(kRed+1);

  if(drellYan) rapidityH10_E->Add(rapidityH10_6);
  rapidityH10_E->Add(rapidityH10_0);
  rapidityH10_E->Add(rapidityH10_1);

  if(drellYan) rapidityH10_M->Add(rapidityH10_7);
  rapidityH10_M->Add(rapidityH10_2);
  rapidityH10_M->Add(rapidityH10_3);

  rapidityH10_T->Add(rapidityH10_4);
  rapidityH10_T->Add(rapidityH10_5);

  if(drellYan) rapidityH9_E->Add(rapidityH9_6);
  rapidityH9_E->Add(rapidityH9_0);
  rapidityH9_E->Add(rapidityH9_1);

  if(drellYan) rapidityH9_M->Add(rapidityH9_7);
  rapidityH9_M->Add(rapidityH9_2);
  rapidityH9_M->Add(rapidityH9_3);

  rapidityH9_T->Add(rapidityH9_4);
  rapidityH9_T->Add(rapidityH9_5);

  if(drellYan) rapidityH41_E->Add(rapidityH41_6);
  rapidityH41_E->Add(rapidityH41_0);
  rapidityH41_E->Add(rapidityH41_1);
     		    
  if(drellYan) rapidityH41_M->Add(rapidityH41_7);
  rapidityH41_M->Add(rapidityH41_2);
  rapidityH41_M->Add(rapidityH41_3);
     		    
  rapidityH41_T->Add(rapidityH41_4);
  rapidityH41_T->Add(rapidityH41_5);
  
  TFile* out = new TFile("hstack.root","RECREATE");

  if(writeImages) {
    pngWriter(massH9_E,  "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH9_E.png",   massH9_0,  massH9_1, massH9_6); 
    pngWriter(massH9_M,  "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH9_M.png",   massH9_2,  massH9_3, massH9_7); 
    pngWriter(massH9_T,  "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH9_T.png",   massH9_4,  massH9_5, 0); 
    pngWriter(massH10_E, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH10_E.png",  massH10_0, massH10_1, massH10_6); 
    pngWriter(massH10_M, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH10_M.png",  massH10_2, massH10_3, massH10_7); 
    pngWriter(massH10_T, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH10_T.png",  massH10_4, massH10_5, 0); 
    pngWriter(massH41_E, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH44_E.png",  massH41_0, massH41_1, massH41_6); 
    pngWriter(massH41_M, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH44_M.png",  massH41_2, massH41_3, massH41_7); 
    pngWriter(massH41_T, "Lepton System Invariant Mass (GeV)","Events / 50 GeV", "massH44_T.png",  massH41_4, massH41_5, 0); 
    pngWriter(massH241_E,"Lepton System Invariant Mass (GeV)","Events / 10 GeV", "massH244_E.png", massH41_0, massH241_1, massH241_6); 
    pngWriter(massH241_M,"Lepton System Invariant Mass (GeV)","Events / 10 GeV", "massH244_M.png", massH41_2, massH241_3, massH241_7); 
    pngWriter(massH241_T,"Lepton System Invariant Mass (GeV)","Events / 10 GeV", "massH244_T.png", massH41_4, massH241_5, 0); 
  }
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

  if(writeImages) {
    pngWriter(rapidityH9_E,  "Lepton System Rapidity","Events / 0.5", "rapidityH9_E.png",  rapidityH9_0,  rapidityH9_1, rapidityH9_6); 
    pngWriter(rapidityH9_M,  "Lepton System Rapidity","Events / 0.5", "rapidityH9_M.png",  rapidityH9_2,  rapidityH9_3, rapidityH9_7); 
    pngWriter(rapidityH9_T,  "Lepton System Rapidity","Events / 0.5", "rapidityH9_T.png",  rapidityH9_4,  rapidityH9_5, 0); 
    pngWriter(rapidityH10_E, "Lepton System Rapidity","Events / 0.5", "rapidityH10_E.png", rapidityH10_0, rapidityH10_1, rapidityH10_6); 
    pngWriter(rapidityH10_M, "Lepton System Rapidity","Events / 0.5", "rapidityH10_M.png", rapidityH10_2, rapidityH10_3, rapidityH10_7); 
    pngWriter(rapidityH10_T, "Lepton System Rapidity","Events / 0.5", "rapidityH10_T.png", rapidityH10_4, rapidityH10_5, 0); 
    pngWriter(rapidityH41_E, "Lepton System Rapidity","Events / 0.5", "rapidityH44_E.png", rapidityH41_0, rapidityH41_1, rapidityH41_6); 
    pngWriter(rapidityH41_M, "Lepton System Rapidity","Events / 0.5", "rapidityH44_M.png", rapidityH41_2, rapidityH41_3, rapidityH41_7); 
    pngWriter(rapidityH41_T, "Lepton System Rapidity","Events / 0.5", "rapidityH44_T.png", rapidityH41_4, rapidityH41_5, 0); 
  }
  
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
