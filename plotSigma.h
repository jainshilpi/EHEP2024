//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan  9 19:58:32 2024 by ROOT version 5.34/37
// from TTree T2/test
// found on file: input_singlex_1sigma_noise0.040.root
//////////////////////////////////////////////////////////

#ifndef plotSigma_h
#define plotSigma_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class plotSigma {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
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

   // List of branches
   TBranch        *b_enpho;   //!
   TBranch        *b_thpho;   //!
   TBranch        *b_phpho;   //!
   TBranch        *b_fclus;   //!
   TBranch        *b_enr1ph;   //!
   TBranch        *b_enr9ph;   //!
   TBranch        *b_enr25ph;   //!
   TBranch        *b_dthe2ph;   //!
   TBranch        *b_dphi2ph;   //!
   TBranch        *b_diag1ph;   //!
   TBranch        *b_diag2ph;   //!
   TBranch        *b_mominx;   //!
   TBranch        *b_theinx;   //!
   TBranch        *b_phiinx;   //!

   plotSigma(TTree *tree=0);
   virtual ~plotSigma();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
  virtual double     Loop(float genE, string fname, TFile *fout);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef plotSigma_cxx
plotSigma::plotSigma(TTree *tree) : fChain(0) 
{
  /*
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("input_singlex_1sigma_noise0.040.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("input_singlex_1sigma_noise0.040.root");
      }
      f->GetObject("T2",tree);

   }
   Init(tree);
  */
}

plotSigma::~plotSigma()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t plotSigma::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t plotSigma::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void plotSigma::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("enpho", &enpho, &b_enpho);
   fChain->SetBranchAddress("thpho", &thpho, &b_thpho);
   fChain->SetBranchAddress("phpho", &phpho, &b_phpho);
   fChain->SetBranchAddress("fclus", &fclus, &b_fclus);
   fChain->SetBranchAddress("enr1ph", &enr1ph, &b_enr1ph);
   fChain->SetBranchAddress("enr9ph", &enr9ph, &b_enr9ph);
   fChain->SetBranchAddress("enr25ph", &enr25ph, &b_enr25ph);
   fChain->SetBranchAddress("dthe2ph", &dthe2ph, &b_dthe2ph);
   fChain->SetBranchAddress("dphi2ph", &dphi2ph, &b_dphi2ph);
   fChain->SetBranchAddress("diag1ph", &diag1ph, &b_diag1ph);
   fChain->SetBranchAddress("diag2ph", &diag2ph, &b_diag2ph);
   fChain->SetBranchAddress("mominx", &mominx, &b_mominx);
   fChain->SetBranchAddress("theinx", &theinx, &b_theinx);
   fChain->SetBranchAddress("phiinx", &phiinx, &b_phiinx);
   Notify();
}

Bool_t plotSigma::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void plotSigma::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t plotSigma::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef plotSigma_cxx
