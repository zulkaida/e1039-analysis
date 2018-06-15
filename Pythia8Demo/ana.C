using namespace std;
void ana() {
  TFile *f = TFile::Open("DSTReader.root");
  TTree *T = (TTree*) f->Get("T");
  //T->Show(0);

  int n_PHG4Particle;
  TClonesArray *particles;

  T->SetBranchAddress("n_PHG4Particle", &n_PHG4Particle);
  T->SetBranchAddress("PHG4Particle", &particles);

  for(int ientry=0; ientry<T->GetEntries(); ++ientry) {
    T->GetEntry(ientry);
    cout<< ientry << ": " << n_PHG4Particle << endl;
    //particles->Print();
    for(int ipar=0; ipar<n_PHG4Particle; ++ipar) {
      PHG4Particle* particle = (PHG4Particle*) particles->At(ipar);
      cout
      << particle->get_track_id() << ": "
      << particle->get_parent_id() << ": "
      << particle->get_name() << ": " 
      << particle->get_pid()<< endl;
    }
  }
}
