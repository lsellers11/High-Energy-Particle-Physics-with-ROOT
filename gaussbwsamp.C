atomvoid hw7gaussbwsamp()
{
  // Initialize RNG
  TRandom3 RNG;

  // Declare histograms

  TH1D* hist1 = new TH1D("hist1", "Gaussian", 50, 0, 100);
  TH1D* hist2 = new TH1D("hist2", "Breit-Wigner", 50, 0, 100);

  // Declare distributions

  TF1* Gauss1 = new TF1("Gauss1", "0.5 / ([0]*(2*TMath::Pi())**(1/2)) * e**(-0.5 * ((x-[1])/[0])**2)", 0, 100);
  TF1* BreitWig1 = new TF1("BreitWig1", "[0] / (2 * TMath::Pi()) * 1 / ((x-[1])**2 + [0]**2 / 4)", 0,100);

  // Set Parameters

  Gauss1 -> SetParameters(10.0, 20);
  Gauss1 -> SetTitle("Gauss1 #mu = 0, #sigma = 10");
  Gauss1 -> SetLineColor(kRed);
  Gauss1 -> SetLineWidth(4);

  // Then the FWHM is ~ 2.355 * 10 = 23.55 -> Set Gamma for bw

  BreitWig1 -> SetParameters(23.55, 20);
  BreitWig1 -> SetTitle("BreitWig1 M = 0, #Gamma = 23.55");
  BreitWig1 -> SetLineColor(kBlue);
  BreitWig1 -> SetLineWidth(4);

  // Fill histograms

  for (int i = 0; i < 1000; i++){
    hist1 -> Fill(Gauss1 -> GetRandom());
    hist2 -> Fill(BreitWig1 -> GetRandom());
  }

  // Declare Canvas. Draw and Build legend

  TCanvas* can1 = new TCanvas("can1", "c1", 600, 400);
  can1 -> cd();

  hist1 -> SetLineColor(kRed);
  hist1 -> SetLineWidth(4);
  hist1 -> DrawNormalized();

  hist2 -> SetLineColor(kBlue);
  hist2 -> SetLineWidth(4);
  hist2 -> DrawNormalized("same");

  TLegend* leg = can1 -> BuildLegend(0.55, 0.7, 0.9, 0.9);

  Gauss1 -> SetTitle("Sample of Gaussian and Breit-Wigner over 1000 Events");

  return;

}
