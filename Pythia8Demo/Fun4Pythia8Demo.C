#include <iostream>
using namespace std;

int Fun4Pythia8Demo(
    const int nEvents = 1
    )
{

  gSystem->Load("libPHPythia8.so");

  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(100);

  PHPythia8 *pythia8 = new PHPythia8();
  pythia8->set_config_file("phpythia8.cfg");
  pythia8->Verbosity(100);
  se->registerSubsystem(pythia8);

  // particle gun
  PHG4ParticleGun *gun = new PHG4ParticleGun("PGUN");
  gun->set_name("proton");
  gun->set_vtx(0, 0, 0);
  gun->set_mom(0, 0, 120);
  //se->registerSubsystem(gun);

  HepMCNodeReader *hr = new HepMCNodeReader();
  se->registerSubsystem(hr);

  gSystem->Load("libg4testbench");
  PHG4Reco *g4Reco = new PHG4Reco();
  g4Reco->SetWorldSizeX(200);
  g4Reco->SetWorldSizeY(200);
  g4Reco->SetWorldSizeZ(200);
  // shape of our world - it is a tube
  g4Reco->SetWorldShape("G4BOX");
  // this is what our world is filled with
  g4Reco->SetWorldMaterial("G4_Galactic");
  // Geant4 Physics list to use
  g4Reco->SetPhysicsList("FTFP_BERT");

  PHG4TruthSubsystem *truth = new PHG4TruthSubsystem();
  g4Reco->registerSubsystem(truth);

  se->registerSubsystem(g4Reco);

  Fun4AllInputManager *in = new Fun4AllDummyInputManager("JADE");
  se->registerInputManager(in);

  Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", "DST.root");
  se->registerOutputManager(out);

  //Convert DST to human command readable TTree for quick poke around the outputs
  gSystem->Load("libg4eval");
  PHG4DSTReader *ana = new PHG4DSTReader(string("DSTReader.root"));
  ana->set_save_particle(true);
  ana->set_load_all_particle(false);
  ana->set_load_active_particle(true);
  ana->set_save_vertex(true);
  //ana->AddNode("PHHepMCGenEvent");
  se->registerSubsystem(ana);

  //-----------------
  // Event processing
  //-----------------

  se->run(nEvents);

  //-----
  // Exit
  //-----

  se->End();
  std::cout << "All done" << std::endl;
  delete se;
  gSystem->Exit(0);
}
