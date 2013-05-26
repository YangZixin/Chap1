#include <iostream>
//#include "TGraph.h"
//#include "TAxis.h"

double *reactionTime = NULL;
double *ParticleNum_A = NULL;
double *ParticleNum_B = NULL;


using namespace std;


void resonance(int numOfSteps, int N_A, int N_B, double tau)
{
	double dt = 0.05;
	int turnedNum = 0;
	reactionTime = new double[numOfSteps];
	ParticleNum_A = new double[numOfSteps];
	ParticleNum_B = new double[numOfSteps];
	for (int i = 0; i < numOfSteps ; i++)
	{
		reactionTime[i] = i * dt;
		ParticleNum_A[i] = N_A;
		ParticleNum_B[i] = N_B;
		turnedNum = (N_B / tau - N_A / tau) * dt;
		N_A += turnedNum;
		N_B -= turnedNum;
		turnedNum = (N_A / tau - N_B / tau) * dt;
		N_B += turnedNum;
		N_A -= turnedNum;
		cout << reactionTime[i] << " " << N_A << " " <<N_B << endl;
	}


}


void plot()
{
	int A, B, numOfSteps;
     	double tau;
	cout<<"Initial number of type A = ";
	cin>>A;
	cout<<"Initial number of type B = ";
	cin>>B;
	cout<<"Time constant tau = ";
	cin>>tau;
	cout<<"The times of resonance reaction = ";
	cin>>numOfSteps;

	resonance(numOfSteps, A, B, tau);
gROOT->Reset();
c1 = new TCanvas("c1","A Zoomed Graph",200,10,700,500);
// create a histogram for the axis range
hpx = new TH2F("hpx","Zoomed Graph Example",10,0.0,1.5,10,0.0,100.0);
// no statistics
hpx->SetStats(kFALSE);
hpx->Draw();


	TGraph *gr1 = new TGraph(numOfSteps, reactionTime, ParticleNum_A);
	TGraph *gr2 = new TGraph(numOfSteps, reactionTime, ParticleNum_B);
//	TCanvas* c1 = new TCanvas("c1", "Evolution of Resonance between nuclei A and B", 200, 10, 600, 400);
	gr1->GetXaxis()->SetTitle("Reaction Time");
	gr1->GetYaxis()->SetTitle("Numbers of the remnant nuclei");
	gr1->SetTitle("Nuclei Resonance between A and B");
	gr1->SetMarkerStyle(22);
	gr1->SetMarkerSize(1);
	gr1->SetMarkerColor(kBlue);
	gr1->Draw("AC*");

	gr2->SetLineWidth(3);
	gr2->SetMarkerStyle(21);
	gr2->SetLineColor(2);
	gr2->Draw("CP");
}


