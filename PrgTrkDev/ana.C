using namespace std;

double ratio_error(
    const double a,
    const double b,
    const double ea,
    const double eb
    ) {
  double r = a/b;
  double er = r*sqrt(
      (ea/a)*(ea/a) + (eb/b)*(eb/b)
      );
  return er;
}

double binom_error(
    const double a,
    const double b
    ){
  double r=a/b;
  return sqrt(r*(1-r)/b);
}

TH1D * getEffHist(
    const char* hname,
    const TH1D* h1,
    const TH1D* h2
    ) {
  TH1D *h = h1->Clone(hname);
  int nbin = h->GetNbinsX();
  for(int ibin=1; ibin<=nbin; ++ibin) {
    double a = h1->GetBinContent(ibin);
    double b = h2->GetBinContent(ibin);
    double r = a/b;
    double e = binom_error(a, b);
    h->SetBinContent(ibin, r);
    h->SetBinError(ibin, e);
  }

  return h;
}

void drawTimeMul() {

  int n = 6;
  float y[]       = { 0.074, 0.207, 0.913, 5.503, 10.950, 46.440};
  float y_error[] = { 0, 0, 0, 0, 0, 0};
  float x[]       = { 1, 2, 5, 8, 10, 20};
  float x_error[] = { 0, 0, 0, 0, 0, 0};

  for(int i=0;i<n;++i) {
    y[i] /= x[i];
    y_error[i] = 0.1*y[i];
  }

  TCanvas *c0 = new TCanvas("drawTimeMul", "drawTimeMul");
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle(";multiplicity ; Time/event/particle [sec.]");
  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  gr->SetMaximum(2);
  //gr->GetXaxis()->SetRangeUser(-5,11);
  TF1 *fpol = new TF1("fpol","[0]*pow(x,[1])+[2]");
  gr->Fit(fpol);
}

void drawEffMul() {

  int n = 5;
  char* inputs [] = {
    "batch1/mu1/trk_eval.root",
    "batch1/mu2/trk_eval.root",
    "batch1/mu5/trk_eval.root",
    "batch1/mu8/trk_eval.root",
    "batch1/mu10/trk_eval.root"
  };

  float y[]       = { 0, 0, 0, 0, 0};
  float y_error[] = { 0, 0, 0, 0, 0};
  float x[]       = { 1, 2, 5, 8, 10};
  float x_error[] = { 0, 0, 0, 0, 0};

  for(int i=0;i<n;++i) {
    TFile *f = TFile::Open(inputs[i],"read");
    TH1D *h = new TH1D("h","h",2,-0.5,1.5);
    T->Project("h","ntruhits>0","gndc>=18");
    y[i] = h->GetMean();
    y_error[i] = h->GetMeanError();
  }

  TCanvas *c0 = new TCanvas("drawEffMul", "drawEffMul");
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle(";multiplicity ; Eff.");
  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  gr->SetMaximum(1.5);
  gr->SetMinimum(0);
}


void ana() {
  gStyle->SetOptFit();

  drawEffMul();

  drawTimeMul();
}
