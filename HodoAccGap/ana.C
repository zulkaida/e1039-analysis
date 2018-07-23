using namespace std;
void ana() {
	float mean_n_tracks[] = {1.8, 1.6, 1.2, 1.0};
	float gap_size[] = {0, 1, 5, 10};
	TGraph* gr = new TGraph(4, gap_size, mean_n_tracks);
	gr->Draw("AC*");
}
