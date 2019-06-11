#include <iostream>
#include <fstream>
#include "percolation.h"

using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 4) {
		cout << "行列の大きさ, 発火確率, イテレーション数の3つの引数を入力して下さい。" << "\n";
	}
	int size = stoi(argv[1]);
	double probability = stod(argv[2]);
	int iterCnt = stoi(argv[3]);
	int percolationCnt = 0;
	Percolation percolation(size);

	for(int i=0; i<iterCnt; i++) {
		percolation.simulation(probability);
		//percolation.print(size);
		percolation.detectConnectedComponents();
		percolationCnt += percolation.checkPercolation();
	}

	ofstream outputfile("percolation_result.csv", ios::app);
	outputfile << size << "," << probability << "," << iterCnt << "," << (double)percolationCnt / iterCnt << "\n";
	outputfile.close();

}
