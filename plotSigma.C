#define plotSigma_cxx
#include "plotSigma.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

double plotSigma::Loop(float genE, string fname, TFile *fout)
{

  TFile *fin = TFile::Open(Form("%s.root",fname.c_str()));
  TTree *tin = (fin)->Get("T2");
  Init(tin);

  TH1F* hdiff = new TH1F(Form("hdiff_%s",fname.c_str()),"",200,-10,10);

  //TFile *fout = new TFile(Form("%s_out.root",fname.c_str()));


  if (fChain == 0) return;

  /*
  // Open a file for writing
  std::ofstream outputFile;

  if(!append)
    outputFile.open(Form("%s_out.txt",fname.c_str()),std::ios::out);
  else 
    outputFile.open(Form("%s_out.txt",fname.c_str()),std::ios::app);
  
    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1; // Exit with an error code
    }

  */
  
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      /// 
      double rel_diff = (enpho-genE)/genE;

      hdiff->Fill(rel_diff);
      
   }

   double rms = hdiff->GetRMS();

   fout->cd();
   hdiff->Write();
   
   return rms;
}
