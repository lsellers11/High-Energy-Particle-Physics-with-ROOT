void Higgs_reco_ggtozz() {
  TChain chain("tree"); // Use TChain to load multiple trees
  chain.Add("/home/public/Higgs/GluGluHToZZTo4L_M125_13TeV/*.root");
  //chain.Add("/home/public/Higgs/VBF_HToZZTo4L_M125_13TeV/*.root");
  // Setup Variables
  std::vector<float> *mu_pt(nullptr), *mu_eta(nullptr), *mu_phi(nullptr), *mu_iso(nullptr);
  std::vector<float> *el_pt(nullptr), *el_eta(nullptr), *el_phi(nullptr), *el_iso(nullptr);
  std::vector<bool>  *mu_id     = nullptr; std::vector<bool>  *el_id     = nullptr;
  std::vector<int>   *mu_charge = nullptr; std::vector<int>   *el_charge = nullptr;
  // Set Branch Addresses
  chain.SetBranchAddress("mus_pt", &mu_pt); chain.SetBranchAddress("els_pt", &el_pt);
  chain.SetBranchAddress("mus_eta", &mu_eta); chain.SetBranchAddress("els_sceta", &el_eta);
  chain.SetBranchAddress("mus_phi", &mu_phi); chain.SetBranchAddress("els_phi", &el_phi);
  chain.SetBranchAddress("mus_reliso",&mu_iso); chain.SetBranchAddress("els_reliso", &el_iso);
  chain.SetBranchAddress("mus_sigid", &mu_id); chain.SetBranchAddress("els_sigid", &el_id);
  chain.SetBranchAddress("mus_charge",&mu_charge); chain.SetBranchAddress("els_charge",&el_charge);
  // Setup Histograms
  TH1D* m_4l    = new TH1D("m_4l",   "Mass of 4l system;   m_{4l} [GeV];   Entries",70,60,340);
  TH1D* m_4e    = new TH1D("m_4e",   "Mass of 4e system;   m_{4e} [GeV];   Entries",70,60,340);
  TH1D* m_4mu   = new TH1D("m_4mu",  "Mass of 4mu system;  m_{4mu} [GeV];  Entries",70,60,340);
  TH1D* m_2e2mu = new TH1D("m_2e2mu","Mass of 2e2mu system;m_{2e2mu} [GeV];Entries",70,60,340);
  // Useful variables
  int nels(0), nmus(0), charge4(0), charge2mu(0), charge2el(0);
  TLorentzVector l1,l2,l3,l4,H;
  // Loop through events
  for(int i=0; i < chain.GetEntries(); i++) {
    chain.GetEntry(i);
    nels = 0; nmus = 0; charge4 = -1; charge2mu = -1; charge2el = -1;
    l1.SetPxPyPzE(0,0,0,1); l2.SetPxPyPzE(0,0,0,1);
    l3.SetPxPyPzE(0,0,0,1); l4.SetPxPyPzE(0,0,0,1);
    H.SetPxPyPzE(0,0,0,1);
    for(int j=0; j < el_pt->size(); j++) // Loop over electron list
      if(el_pt->at(j)>7 && abs(el_eta->at(j))<2.5 && el_iso->at(j)<0.35 && el_id->at(j)) nels++;
    for(int j=0; j < mu_pt->size(); j++) // Loop over muon list
      if(mu_pt->at(j)>5 && abs(mu_eta->at(j))<2.4 && mu_iso->at(j)<0.35 && mu_id->at(j)) nmus++;
    if(nmus == 4) {
      // Reconstruct 4mu mass, check that charge == 0, and fill relevant histograms
      int totmucharge(0);
      for(int k=0; k < 4; k++){
        totmucharge += mu_charge->at(k);
      }
      if(totmucharge==0){
        l1.SetPtEtaPhiM(mu_pt->at(0), mu_eta->at(0), mu_phi->at(0), 0.105658);
        l2.SetPtEtaPhiM(mu_pt->at(1), mu_eta->at(1), mu_phi->at(1), 0.105658);
        l3.SetPtEtaPhiM(mu_pt->at(2), mu_eta->at(2), mu_phi->at(2), 0.105658);
        l4.SetPtEtaPhiM(mu_pt->at(3), mu_eta->at(3), mu_phi->at(3), 0.105658);
        H.SetPxPyPzE(l1.Px()+l2.Px()+l3.Px()+l4.Px(), l1.Py()+l2.Py()+l3.Py()+l4.Py(), l1.Pz()+l2.Pz()+l3.Pz()+l4.Pz(), l1.E()+l2.E()+l3.E()+l4.E());
        m_4mu->Fill(H.M());
        m_4l->Fill(H.M());
      }
    }
    if(nels == 4) {
      // Reconstruct 4el mass, check that charge == 0, and fill relevant histograms
      int totelcharge(0);
      double shmem(0.0);
      double msquared(0.0);
      for(int k=0; k < 4; k++){
        totelcharge += el_charge->at(k);
      }
      if(totelcharge==0){
        l1.SetPtEtaPhiM(el_pt->at(0), el_eta->at(0), el_phi->at(0), 0.000511);
        l2.SetPtEtaPhiM(el_pt->at(1), el_eta->at(1), el_phi->at(1), 0.000511);
        l3.SetPtEtaPhiM(el_pt->at(2), el_eta->at(2), el_phi->at(2), 0.000511);
        l4.SetPtEtaPhiM(el_pt->at(3), el_eta->at(3), el_phi->at(3), 0.000511);
        H.SetPxPyPzE(l1.Px()+l2.Px()+l3.Px()+l4.Px(), l1.Py()+l2.Py()+l3.Py()+l4.Py(), l1.Pz()+l2.Pz()+l3.Pz()+l4.Pz(), l1.E()+l2.E()+l3.E()+l4.E());
        m_4e->Fill(H.M());
        m_4l->Fill(H.M());
      }
    }
    if(nels > 1 && nmus > 1) {
      // Reconstruct 2el2mu mass, check that charge == 0, and fill relevant histograms
      int totcharge(0);
      for(int k=0; k < 2; k++){
        totcharge += el_charge->at(k) + mu_charge->at(k);
      }
      if(totcharge==0){
          l1.SetPtEtaPhiM(mu_pt->at(0), mu_eta->at(0), mu_phi->at(0), 0.105658);
          l2.SetPtEtaPhiM(mu_pt->at(1), mu_eta->at(1), mu_phi->at(1), 0.105658);
          l3.SetPtEtaPhiM(el_pt->at(0), el_eta->at(0), el_phi->at(0), 0.000511);
          l4.SetPtEtaPhiM(el_pt->at(1), el_eta->at(1), el_phi->at(1), 0.000511);
          H.SetPxPyPzE(l1.Px()+l2.Px()+l3.Px()+l4.Px(), l1.Py()+l2.Py()+l3.Py()+l4.Py(), l1.Pz()+l2.Pz()+l3.Pz()+l4.Pz(), l1.E()+l2.E()+l3.E()+l4.E());
          m_2e2mu->Fill(H.M());
          m_4l->Fill(H.M());
      }
    }
  }
  //Write final histograms to file
  TFile out("higgs_peak_ggzz.root","RECREATE");
  m_4l->Write();
  m_4e->Write();
  m_4mu->Write();
  m_2e2mu->Write();
  out.Close();
  return;
}
