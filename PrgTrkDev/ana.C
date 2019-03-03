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

void drawTimeDSLevel() {

  int n = 3;
  float y[]       = { 43.0, 23.6, 11.6};
  float x[]       = { 0, 2, 3};

  float y_error[] = { 0, 0, 0, 0, 0, 0};
  float x_error[] = { 0, 0, 0, 0, 0, 0};

  for(int i=0;i<n;++i) {
    y_error[i] = 0.1*y[i];
  }

  TCanvas *c0 = new TCanvas("drawTimeDSLevel", "drawTimeDSLevel");
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle(";DS level ; Time/event [sec.]");
  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  //gr->SetMaximum(2);
  //gr->GetXaxis()->SetRangeUser(-5,11);
  //TF1 *fpol = new TF1("fpol","[0]*pow(x,[1])+[2]");
  //gr->Fit(fpol);
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

void drawTimeAna(const char* name) {

  //int n = 2;
  //char* inputs [] = {
  //  "nrm_4_res222_ds0_100/ktracker_ana.root",
  //  "nrm_4_res222_ds2_100/ktracker_ana.root",
  //};
  //float x[]       = { 0, 2};

  int n = 3;
  char* inputs [] = {
    "nrh_4_res222_ds0_100/ktracker_ana.root",
    "nrh_4_res222_ds2_100/ktracker_ana.root",
    "nrh_4_res222_ds3_100/ktracker_ana.root"
  };
  float x[]       = { 0, 2, 3};

  float y[]       = { 0, 0, 0, 0, 0, 0};
  float y_error[] = { 0, 0, 0, 0, 0, 0};
  float x_error[] = { 0, 0, 0, 0, 0, 0};

  for(int i=0;i<n;++i) {
    TFile *f = TFile::Open(inputs[i],"read");
    TH1D *h = new TH1D("h","h",50,-0.5,49.5);
    TNtuple *T = (TNtuple*) f->Get(name);
    T->Project("h","time","");
    y[i] = h->GetMean();
    y_error[i] = h->GetMeanError();
  }

  TCanvas *c0 = new TCanvas(name, name);
  c0->SetGridy();
  //c0->SetLogy();
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle(";DS Level ; Time/event [sec.]");
  gr->SetMarkerStyle(20);
  gr->Draw("ap,text");
  gr->SetMaximum(12);
  gr->SetMinimum(0);
  gr->GetXaxis()->SetRangeUser(-1,4);
  gr->Print();
}


void drawEffMul() {

  int n = 6;
  char* inputs [] = {
    "batch1/mu1/trk_eval.root",
    "batch1/mu2/trk_eval.root",
    "batch1/mu5/trk_eval.root",
    "batch1/mu8/trk_eval.root",
    "batch1/mu10/trk_eval.root",
    "batch1/mu20/trk_eval.root"
  };

  float y[]       = { 0, 0, 0, 0, 0, 0};
  float y_error[] = { 0, 0, 0, 0, 0, 0};
  float x[]       = { 1, 2, 5, 8, 10,20};
  float x_error[] = { 0, 0, 0, 0, 0, 0};

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


void drawEffDS123Survey() {

  int n = 6;
  char* inputs [] = {
     "st123/0.0cm/trk_eval.root"
    ,"st123/.15cm/trk_eval.root"
    ,"st123/0.1cm/trk_eval.root"
    ,"st123/0.2cm/trk_eval.root"
    ,"st123/0.5cm/trk_eval.root"
    ,"st123/1.0cm/trk_eval.root"
  };

  float y[]       = { 0, 0, 0, 0, 0, 0};
  float y_error[] = { 0, 0, 0, 0, 0, 0};
  float x[]       = { 0, 0.1, 0.15, 0.2, 0.5, 1};
  float x_error[] = { 0, 0, 0, 0, 0, 0};

  for(int i=0;i<n;++i) {
    TFile *f = TFile::Open(inputs[i],"read");
    TH1D *h = new TH1D("h","h",2,-0.5,1.5);
    T->Project("h","ntruhits>0","gndc>=18");
    y[i] = h->GetMean();
    y_error[i] = h->GetMeanError();
  }

  TCanvas *c0 = new TCanvas("drawEffDS123Survey", "drawEffDS123Survey");
  c0->SetGridy();
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle("; X0 shift [cm] ; Eff.");
  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  gr->SetMaximum(1.1);
  gr->SetMinimum(0);
}


void drawEffDSLevel() {

  //int n = 2;
  //char* inputs [] = {
  //   "nrm_4_res222_ds0_100/trk_eval.root"
  //  ,"nrm_4_res222_ds2_100/trk_eval.root"
  //};
  //float x[]       = { 0, 2};

  int n = 3;
  char* inputs [] = {
     "nrh_4_res222_ds0_100/trk_eval.root"
    ,"nrh_4_res222_ds2_100/trk_eval.root"
    ,"nrh_4_res222_ds3_100/trk_eval.root"
  };
  float x[]       = { 0, 2, 3};

  float x_error[] = { 0, 0, 0, 0, 0, 0};
  float y[]       = { 0, 0, 0, 0, 0, 0};
  float y_error[] = { 0, 0, 0, 0, 0, 0};

	float ref_mean = 1.0;

  for(int i=0;i<n;++i) {
    TFile *f = TFile::Open(inputs[i],"read");
    TH1D *h = new TH1D("h","h",2,-0.5,1.5);
    T->Project("h","ntruhits>0","gndc>=18");
		//if(i==0) ref_mean = h->GetMean();
    y[i] = h->GetMean()/ref_mean;
    y_error[i] = h->GetMeanError()/ref_mean;
  }

  TCanvas *c0 = new TCanvas("drawEffDSLevel", "drawEffDSLevel");
  c0->SetGridy();
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle("; DS level; Eff.");
  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  gr->SetMaximum(1.1);
  gr->SetMinimum(0);
  gr->GetXaxis()->SetRangeUser(-1,4);
  gr->Print();
}


void drawEffDS23Survey() {

  int n = 4;
  char* inputs [] = {
     "st23/0.0cm/trk_eval.root"
    ,"st23/0.5cm/trk_eval.root"
    ,"st23/1.0cm/trk_eval.root"
    ,"st23/2.0cm/trk_eval.root"
  };

  float y[]       = { 0, 0, 0, 0, 0, 0};
  float y_error[] = { 0, 0, 0, 0, 0, 0};
  float x[]       = { 0, 0.5, 1, 2};
  float x_error[] = { 0, 0, 0, 0, 0, 0};

  for(int i=0;i<n;++i) {
    TFile *f = TFile::Open(inputs[i],"read");
    TH1D *h = new TH1D("h","h",2,-0.5,1.5);
    T->Project("h","ntruhits>0","gndc>=18");
    y[i] = h->GetMean();
    y_error[i] = h->GetMeanError();
  }

  TCanvas *c0 = new TCanvas("drawEffDS23Survey", "drawEffDS23Survey");
  c0->SetGridy();
  TGraphErrors* gr = new TGraphErrors(n, x, y, x_error, y_error);
  gr->SetTitle("; X0 shift [cm] ; Eff.");
  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  gr->SetMaximum(1.1);
  gr->SetMinimum(0);
}


void ana() {
  gStyle->SetOptFit();

  drawTimeAna("St23");
  drawTimeAna("St123");

	drawEffDSLevel();
	//drawTimeDSLevel();

  //drawEffDS23Survey();
  //drawEffDS123Survey();

  //drawEffMul();
  //drawTimeMul();
}
