#include "TH1.h"
#include "THStack.h"
#include "TDirectory.h"

TFile* data0;
TFile* data1;
TFile* data2;
TFile* data3;
TFile* data4;
TFile* data5;
TFile* data6;
TFile* data7;
TFile* out;
Int_t _writeIms;
Int_t _drell;

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

void stacker(Int_t book, TString hist, Int_t drellBook, TString drellHist, TString label, Int_t mVsR, Int_t rebin) {
  char* name = new char[20];
  std::sprintf(name,"book_%i",book);
  TH1* massH_0   = (TH1F*) ((TFile*) data0->Get(name))->Get(hist);
  TH1* massH_1   = (TH1F*) ((TFile*) data1->Get(name))->Get(hist);
  TH1* massH_2   = (TH1F*) ((TFile*) data2->Get(name))->Get(hist);
  TH1* massH_3   = (TH1F*) ((TFile*) data3->Get(name))->Get(hist);
  TH1* massH_4   = (TH1F*) ((TFile*) data4->Get(name))->Get(hist);
  TH1* massH_5   = (TH1F*) ((TFile*) data5->Get(name))->Get(hist);
  TH1* massH_6   = 0;
  TH1* massH_7   = 0;
  if(_drell) {
    name = new char[20];
    std::sprintf(name,"book_%i",drellBook);
    massH_6      = (TH1F*) ((TFile*) data6->Get(name))->Get(drellHist);
    massH_7      = (TH1F*) ((TFile*) data7->Get(name))->Get(drellHist);
  }

  if(rebin) {
    massH_0->Rebin(10);
    massH_1->Rebin(10);
    massH_2->Rebin(10);
    massH_3->Rebin(10);
    massH_4->Rebin(10);
    massH_5->Rebin(10);
    if(_drell) massH_6->Rebin(10);
    if(_drell) massH_7->Rebin(10);
  }

  char* title = new char[80];
  if(mVsR) sprintf(title,"Invariant Mass");
  else sprintf(title,"Rapidity");
  char* stackName = new char[100];
  sprintf(stackName, "%s of Electron System", title);
  THStack* massH_E  = new THStack("massH_E", stackName);
  sprintf(stackName, "%s of Muon System", title);
  THStack* massH_M  = new THStack("massH_M", stackName);
  sprintf(stackName, "%s of Tau System", title);
  THStack* massH_T  = new THStack("massH_T", stackName);

  massH_0->SetFillColor(kSpring-8);
  massH_1->SetFillColor(kAzure+2);
  massH_2->SetFillColor(kSpring-8);
  massH_3->SetFillColor(kAzure+2);
  massH_4->SetFillColor(kSpring-8);
  massH_5->SetFillColor(kAzure+2);
  if(_drell) massH_6->SetFillColor(kRed+1);
  if(_drell) massH_7->SetFillColor(kRed+1);

  
  if(_drell) massH_E->Add(massH_6);
  massH_E->Add(massH_0);
  massH_E->Add(massH_1);


  if(_drell) massH_M->Add(massH_7);
  massH_M->Add(massH_2);
  massH_M->Add(massH_3);

  massH_T->Add(massH_4);
  massH_T->Add(massH_5);

  if(_writeIms) {
    char* fname = new char[30];
    if(mVsR) sprintf(title, "Lepton System Invariant Mass (GeV)");
    else     sprintf(title, "Lepton System Rapidity");
    if(_drell) std::sprintf(fname,"%s_Drell_E.png",hist.Data());
    else std::sprintf(fname,"%s_E.png",hist.Data());
    pngWriter(massH_E, title, label,  fname,   massH_0,  massH_1, massH_6); 
    if(_drell) std::sprintf(fname,"%s_Drell_M.png",hist.Data());
    else std::sprintf(fname,"%s_M.png",hist.Data());
    pngWriter(massH_M, title, label,  fname,   massH_2,  massH_3, massH_7);
    if(_drell) std::sprintf(fname,"%s_Drell_T.png",hist.Data());
    else std::sprintf(fname,"%s_T.png",hist.Data());
    pngWriter(massH_T, title, label,  fname,   massH_4,  massH_5, 0);
  }
  TDirectory* dir = out->mkdir(hist);
  dir->cd();
  massH_T->Write();
  massH_M->Write();
  massH_E->Write();
  delete dir;
}


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
  
  data0   = (TFile*) file0->Get("Data");
  data1   = (TFile*) file1->Get("Data");
  data2   = (TFile*) file2->Get("Data");
  data3   = (TFile*) file3->Get("Data");
  data4   = (TFile*) file4->Get("Data");
  data5   = (TFile*) file5->Get("Data");
  if(drellYan) {
    data6 = (TFile*) file6->Get("Data");
    data7 = (TFile*) file7->Get("Data");
  }
  out = new TFile("hstack.root","RECREATE");
  _drell = drellYan;
  _writeIms = writeImages;

  

  stacker(10,"massH1_10", 14, "massH1_14","Events / 50 GeV", 1, 1);
  stacker(9 ,"massH1_9" , 13, "massH1_13","Events / 50 GeV", 1, 1);
  stacker(44,"massH1_44", 47, "massH1_47","Events / 50 GeV", 1, 1);
  stacker(44,"massH2_44", 47, "massH2_47","Events / 10 GeV", 1, 1);
  stacker(51,"massH2_51", 51, "massH2_51","Events / 1 GeV" , 1, 0);

  stacker(10,"rapidityH_10", 14, "rapidityH_14","Events / 0.5", 0, 1);
  stacker(9 ,"rapidityH_9" , 13, "rapidityH_13","Events / 0.5", 0, 1);
  stacker(44,"rapidityH_44", 47, "rapidityH_47","Events / 0.5", 0, 1);
  stacker(51,"rapidityH_51", 51, "rapidityH_51","Events / 0.5", 0, 1);

  // delete file0;
  // delete file1;
  // delete file2;
  // delete file3;
  // delete file4;
  // delete file5;
  // delete file6;
  // delete file7;
  delete out;
}
