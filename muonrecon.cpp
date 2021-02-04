void muonrecon()
{
  //Get file and declare tree
  TFile *f = TFile::Open("/home/public/Z_decay_MC.root");
  TTree *tree = (TTree*)f->Get("tree");

  //Declare variables
  int mu1q(0), mu2q(0), nmu(0);
  double msquared(0);
  double xpf(0), ypf(0), zpf(0), epf(0);
  TLorentzVector *mu1 = nullptr;
  TLorentzVector *mu2 = nullptr;
  TLorentzVector *pf = nullptr;

  //Histogram
  TH1D *hist = new TH1D("hist", "P^2 for Muon Pair", 1000, -0.5, 200);

  //Branch addresses

  tree -> SetBranchAddress("mu1_charge", &mu1q);
  tree -> SetBranchAddress("mu2_charge", &mu2q);
  tree -> SetBranchAddress("nmus", &nmu);
  tree -> SetBranchAddress("muon_candidate_1", &mu1);
  tree -> SetBranchAddress("muon_candidate_2", &mu2);

  //Loop
  for(int i = 0; i < tree->GetEntries(); i++){
    tree->GetEntry(i);
    if(nmu==2){
      if(mu1q + mu2q == 0){
        TLorentzVector pf(mu1->Px()+mu2->Px(), mu1->Py()+mu2->Py(), mu1->Pz()+mu2->Pz(), mu1->E()+mu2->E());
        msquared = pf.M();
        hist->Fill(msquared);
      }
    }
  }
  // Graph
  TCanvas *can = new TCanvas("can", "Example Canvas", 600, 400);
  can -> cd();
  hist->SetLineColor(kRed);
  hist->SetLineWidth(4);
  hist->Draw();

  TLegend* leg;
  leg = can ->BuildLegend(0.5, 0.74, 0.9, 0.9);
}
