#include "TH2.h"

TFile* data0;
TFile* data1;
TFile* data2;
TFile* data3;
TFile* data4;
TFile* data5;
TFile* data6;
TFile* data7;
Double_t xmin;
Double_t xmax;
Double_t ymin;
Double_t ymax;
TString opt;

void pngWriter(TH2* h, TString title, TString xtitle, TString ytitle, TString outfile) {
  TCanvas* c1 = new TCanvas("c1", "Lepton System");

  
  gStyle->SetOptStat(1111111);
  // Set stat options
  gStyle->SetStatY(0.9);                
  // Set y-position (fraction of pad size)
  gStyle->SetStatX(0.9);                
  // Set x-position (fraction of pad size)
  gStyle->SetStatW(0.25);                
  // Set width of stat-box (fraction of pad size)
  gStyle->SetStatH(0.15);                
  // Set height of stat-box (fraction of pad size)
  // gStyle->SetPalette(1); 

  h->Draw(opt);
  h->SetTitle(title);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->SetAxisRange(xmin,xmax,"X");
  h->SetAxisRange(ymin,ymax,"Y");
  
  c1->SetLogz();
  c1->Modified();
  c1->Update();
  TImage* img = TImage::Create();
  img->FromPad(c1);
  img->WriteImage(outfile);
  delete c1;
  delete img;
}

void plotter(Int_t book, TFile* data, Int_t flavor, Int_t process) {
  char* title = new char[100];
  char* bname  = new char[30];
  char* hname  = new char[30];
  sprintf(bname,"book_%i",book);
  sprintf(hname,"ptVsMassH_%i",book);
  TH2* ptMass = ((TH2F*) ((TFile*) data->Get(bname))->Get(hname));
  char* fl = new char[20];
  char* pr = new char[20];

  if(flavor == 15){
    sprintf(title, "Tau Pt vs Tau System Invariant Mass (GeV)");
    sprintf(fl,"tau");
  }else if(flavor == 13) {
    sprintf(title, "Muon Pt vs Muon System Invariant Mass (GeV)");
    sprintf(fl,"muon");
  }  else {
    sprintf(title, "Electron Pt vs Electron System Invariant Mass (GeV)");
    sprintf(fl,"electron");
  }
  
  if(process == 0) sprintf(pr, "disassociate");
  else if(process == 1) sprintf(pr, "elastic");
  else sprintf(pr,"Drell");

  char* fname = new char[40];
  sprintf(fname,"%s_massPt_%s_%i.png",fl,pr,book);

  pngWriter(ptMass, title, "Lepton Pt (GeV)", "Lepton System Mass (GeV)", fname);


}


void massPlotter(){

  TFile* file0 = new TFile("Data/events_full_electron_disassociate_MinE20_MinPt10.root");
  TFile* file1 = new TFile("Data/events_full_electron_elastic_MinE20_MinPt10.root");
  TFile* file2 = new TFile("Data/events_full_muon_disassociate_MinE20_MinPt10.root");
  TFile* file3 = new TFile("Data/events_full_muon_elastic_MinE20_MinPt10.root");
  TFile* file4 = new TFile("Data/events_full_tau_disassociate_MinE20_MinPt10.root");
  TFile* file5 = new TFile("Data/events_full_tau_elastic_MinE20_MinPt10.root");
  TFile* file6 = new TFile("Data/events_full_electron_DrellYan.root");
  TFile* file7 = new TFile("Data/events_full_muon_DrellYan.root");
  
  data0   = (TFile*) file0->Get("Data");
  data1   = (TFile*) file1->Get("Data");
  data2   = (TFile*) file2->Get("Data");
  data3   = (TFile*) file3->Get("Data");
  data4   = (TFile*) file4->Get("Data");
  data5   = (TFile*) file5->Get("Data");
  data6   = (TFile*) file6->Get("Data");
  data7   = (TFile*) file7->Get("Data");
  
  xmax = 500.;
  xmin = 0.;
  ymax = 500.;
  ymin = 0.;
  opt = "COLZ";
  plotter(0, data0, 11, 0);
  plotter(0, data1, 11, 1);
  plotter(0, data6, 11, 2);
  plotter(0, data2, 13, 0);
  plotter(0, data3, 13, 1);
  plotter(0, data7, 13, 2);
  plotter(0, data4, 15, 0);
  plotter(0, data5, 15, 1);

  xmax = 100.;
  xmin = 0.;
  ymax = 100.;
  ymin = 0.;
  opt = "CONT4Z";
  plotter(51, data0, 11, 0);
  plotter(51, data1, 11, 1);
  plotter(51, data6, 11, 2);
  plotter(51, data2, 13, 0);
  plotter(51, data3, 13, 1);
  plotter(51, data7, 13, 2);
  plotter(51, data4, 15, 0);
  plotter(51, data5, 15, 1);

}
