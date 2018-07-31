using namespace std;

#define NFILE 2
void ana() {
  char* inputs [] = {"ktracker_eval.root", "ktracker_eval_mass_1GeV.root"};
  float mean[] = { 0, 0};
  float mean_error[] = { 0, 0};
  float gap_size[] = {0, 1};
  float gap_size_error[] = {0, 0};

  for (int i=0; i<NFILE; ++i) {
    TFile *f = TFile::Open(inputs[i]);
    TH1D *h = new TH1D("h","h",3,0,3);
    save->Project("h","recEvent.getNTracks()");
    mean[i] = h->GetMean();
    mean_error[i] = h->GetMeanError();
  }
  //TGraph* gr = new TGraph(NFILE, gap_size, mean);
  TGraphErrors* gr = new TGraphErrors(NFILE, gap_size, mean, gap_size_error, mean_error);
  gr->Draw("A*");
  gr->GetXaxis()->SetRangeUser(-1,2);
}
