/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVARegressionApplication                                          *
 *                                                                                *
 * This macro provides a simple example on how to use the trained regression MVAs *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"


using namespace TMVA;


class applyCorrection {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   applyCorrection(TTree *tree=0);
   virtual ~applyCorrection();
   virtual void     Loop(string fname, string corrMVAMethodName);

};

applyCorrection::applyCorrection(TTree *tree) : fChain(0) 
{
}

applyCorrection::~applyCorrection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


void applyCorrection::Loop(string fname, string corrMVAMethodName) 
{
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   Float_t         genE;
   Float_t         enpho;
   Float_t         thpho;
   Float_t         phpho;
   Float_t         fclus;
   Float_t         enr1ph;
   Float_t         enr9ph;
   Float_t         enr25ph;
   Float_t         dthe2ph;
   Float_t         dphi2ph;
   Float_t         diag1ph;
   Float_t         diag2ph;
   Float_t         mominx;
   Float_t         theinx;
   Float_t         phiinx;

   reader->AddVariable( "enpho", &enpho);
  reader->AddVariable( "fclus",  &fclus); // nhits in the cluster
  reader->AddVariable( "enr1ph", &enr1ph);
  reader->AddVariable( "enr9ph", &enr9ph);
  reader->AddVariable( "enr25ph", &enr25ph);
  reader->AddVariable( "dthe2ph", &dthe2ph);
  reader->AddVariable( "dphi2ph", &dphi2ph);
  reader->AddVariable( "diag1ph", &diag1ph);
  reader->AddVariable( "diag2ph", &diag2ph);

   // --- Book the MVA methods

  string dir    = "weights/";
  string prefix = "TMVARegression";
  
  // Book method(s)
  TString methodName = corrMVAMethodName + " method";
  
  cout<<"Method name "<<methodName<<endl;
  
  string weightfile_tmp = dir + prefix + "_" + corrMVAMethodName + ".weights.xml";
  cout<<"Weightfile is "<<weightfile_tmp<<endl;
  TString weightfile(weightfile_tmp);
  
  reader->BookMVA( methodName, weightfile );
  //reader->BookMVA( "MLP method", "weights/TMVARegression_MLP.weights.xml" ); 
  
  TFile *input = TFile::Open( Form("%s.root",fname.c_str()) ); // check if file in local directory exists


   TTree* theTree = (TTree*)input->Get("T2");
   std::cout << "--- Select signal sample" << std::endl;

   theTree->SetBranchAddress("genE", &genE);
   theTree->SetBranchAddress("enpho", &enpho);
   theTree->SetBranchAddress("thpho", &thpho);
   theTree->SetBranchAddress("phpho", &phpho);
   theTree->SetBranchAddress("fclus", &fclus);
   theTree->SetBranchAddress("enr1ph", &enr1ph);
   theTree->SetBranchAddress("enr9ph", &enr9ph);
   theTree->SetBranchAddress("enr25ph", &enr25ph);
   theTree->SetBranchAddress("dthe2ph", &dthe2ph);
   theTree->SetBranchAddress("dphi2ph", &dphi2ph);
   theTree->SetBranchAddress("diag1ph", &diag1ph);
   theTree->SetBranchAddress("diag2ph", &diag2ph);


   TFile *fout = new TFile(Form("%s_withCorr.root",fname.c_str()),"RECREATE");
   
   
   int nbins = 500;
   double xmin = -5;
   double xmax = 5;
   TH1F *hreso_nocorr = new TH1F("hreso_nocorr","hreso_nocorr",nbins, xmin, xmax);
   TH1F *hreso_corr = new TH1F("hreso_corr","hreso_corr",nbins, xmin, xmax);
   
   
   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }

      theTree->GetEntry(ievt);

      
      Float_t val = (reader->EvaluateRegression( "MLP method" ))[0];
	 //cout<<"enpho thpho phpho fclus enr1ph enr9ph enr25ph dthe2ph dphi2ph diag1ph diag2ph "<<enpho<<" "<<thpho<<" "<<phpho<<" "<<fclus<<" "<<enr1ph<<" "<<enr9ph<<" "<<enr25ph<<" "<<dthe2ph<<" "<<dphi2ph<<" "<<diag1ph<<" "<<diag2ph<<endl;
	 cout<<val<<endl;

	 corrE = enpho/val;
	 
	 double reso_nocorr = (enpho-genE)/genE;
	 double reso_corr = (corrE-genE)/genE;
	 
	 hreso_nocorr->Fill(reso_nocorr);
	 hreso_corr->Fill(reso_corr);
	 
   }
      
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   hreso_nocorr->Write();
   hreso_corr->Write();

   fout->Write();
      
   delete reader;
   
}
