//Institute of Physics - Federal University of Rio de Janeiro
//Interdisciplinary Academic Master's Degree in Applied Physics
//Student: Marcos Vieira
//February, 2019

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 27 15:50:45 2017 by ROOT version 6.06/08
// from TChain ntuple/
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// add
#include <string> 
#include <sstream> 

// Header file for the classes stored in the TTree if any.

class Analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evt;
   Int_t           pdg;
   Int_t           id;
   Int_t           mid;
   Double_t        x;
   Double_t        y;
   Double_t        z;
   Double_t        de;
   Double_t        e;
   Int_t           vol;
   Int_t           volrep;
   Int_t           mvol;
   Int_t           mvolrep;
   Int_t           inter;

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_id;   //!
   TBranch        *b_mid;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_de;   //!
   TBranch        *b_e;   //!
   TBranch        *b_vol;   //!
   TBranch        *b_volrep;   //!
   TBranch        *b_mvol;   //!
   TBranch        *b_mvolrep;   //!
   TBranch        *b_inter;   //!

   Analysis(TTree *tree=0);
   virtual ~Analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analysis_cxx
Analysis::Analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("ntuple",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      
      TChain * chain = new TChain("ntuple","");
      chain->Add("filename.root/ntuple");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Analysis::~Analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analysis::LoadTree(Long64_t entry)
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

void Analysis::Init(TTree *tree)
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

   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("pdg", &pdg, &b_pdg);
   fChain->SetBranchAddress("id", &id, &b_id);
   fChain->SetBranchAddress("mid", &mid, &b_mid);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("de", &de, &b_de);
   fChain->SetBranchAddress("e", &e, &b_e);
   fChain->SetBranchAddress("vol", &vol, &b_vol);
   fChain->SetBranchAddress("volrep", &volrep, &b_volrep);
   fChain->SetBranchAddress("mvol", &mvol, &b_mvol);
   fChain->SetBranchAddress("mvolrep", &mvolrep, &b_mvolrep);
   fChain->SetBranchAddress("inter", &inter, &b_inter);
   Notify();
}

Bool_t Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analysis_cxx
