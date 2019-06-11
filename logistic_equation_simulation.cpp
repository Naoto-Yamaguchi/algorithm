#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

double r, K, N_0, h;

string filename = "logistic_equation_simulation_by_for_loop.csv";
ofstream writing_file;

double dN_dt(double N) {
	return r * N * (1 - N / K);
}

// ロジスティック方程式の厳密解
double N(double t) {
	 return N_0 * K / (N_0 + (K - N_0) * exp(-r * t));
}

// 二乗和誤差を計算
double calculate_rse(double N_t, double t) {
	return sqrt(pow((N_t - N(t)), 2));
}

int main(void) {
	writing_file.open(filename, ios::out);
	cin >> r >> K >> N_0 >>  h;

	double error_sum = 0;

	double N_t1 = N_0;;
	for(int i=0; i<10/h + 1; i++) {
		if(i == 0) continue;
		double t = h * i;
		double N_t = N_t1 + h * dN_dt(N_t1);
		N_t1 = N_t;
		writing_file << t << ", " << N_t << "\n";

		// 二乗和誤差を求める。各点の二乗和誤差を足していく。
		error_sum += calculate_rse(N_t, t);
	}

	error_sum = error_sum / 10 * h;
	cout << "error_sum:" << error_sum << "\n";;

	writing_file.close();
}
