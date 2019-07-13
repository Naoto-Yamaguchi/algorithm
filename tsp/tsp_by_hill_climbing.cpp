#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;
random_device seed_gen;
mt19937 engine(seed_gen());

int dis(pair<int, int> i, pair<int, int> j) {
	return sqrt(pow((i.first - j.first), 2) + pow((i.second - j.second), 2));
}

float score(vector<pair<int, int>> cities, vector<int> route) {
	float score = 0;
	for(int i=0; i<route.size()-1; i++) {
		score += dis(cities[route[i]], cities[route[i+1]]);
	}
	return score;
}

void output_svg(vector<pair<int, int>> cities, vector<int> route) {
	string filename = "tsp_by_hill_climbing_O3.html";
	ofstream writing_file;
	writing_file.open(filename, ios::out);
	int width = 10000;
	int height = 10000;
	writing_file << "<svg width=\"" << width << "\" height=\"" << height << "\">" << "\n\t";

	for(int i=0; i<route.size()-1; i++) {
		float x1 = cities[route[i]].first;
		float y1 = cities[route[i]].second;
		float x2 = cities[route[i+1]].first;
		float y2 = cities[route[i+1]].second;
		writing_file << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2 =\"" << x2 << "\" y2=\"" << y2 << "\" stroke=\"black\" />" << "\n\t";
	}

	float sx = cities[route[0]].first;
	float sy = cities[route[0]].second;
	float gx = cities[route[route.size()-1]].first;
	float gy = cities[route[route.size()-1]].second;
	writing_file << "<line x1=\"" << gx << "\" y1=\"" << gy << "\" x2 =\"" << sx << "\" y2=\"" << sy << "\" stroke=\"blue\" />";

	writing_file << "\n</svg>";

}

int main(void) {
	vector<pair<int, int>> cities;
	int index;
	float x, y;
	vector<int> initial_route;
	while(cin >> index >> x >> y) {
		pair<int, int> p = make_pair(x, y);
		cities.push_back(p);
		initial_route.push_back(index-1);
	}

	ofstream outputfile("hill_climbing_O3.csv", ios::app);
	int total_best_score = 1e10;
	vector<int> total_best_route;

	auto start = chrono::system_clock::now();
	for(int i=0; i<1000; i++) {
		cout << i << "\n";
		shuffle(initial_route.begin(), initial_route.end(), engine);
		//for(auto i:initial_route) {
		//	cout << i << ":";
		//}

		//cout << "\n";

	//	for(auto p:cities) {
	//		cout << p.first << ":" << p.second << "\n";
	//	}
	//	for(auto i:initial_route) {
	//		cout << i << "\n"; 
	//	}
		//cout << score(cities, initial_route) << "\n";

		float best_score = score(cities, initial_route);
		vector<int> best_route = initial_route;
		bool updated = true;
		
		while(updated) {
			for(int i=0; i<best_route.size()-1; i++) {
				for(int j=0; j<best_route.size()-1; j++) {
					if(i==j) continue;
						
					vector<int> route = best_route;
					int tmp = route[i]; route[i] = route[j]; route[j] = tmp;
					float tmp_score = score(cities, route);
					updated = false;
					if(best_score > tmp_score) {
						best_route = route;
						best_score = tmp_score;
						//cout << best_score << "\n";
						updated = true;
					}
				}
			}
		}

		outputfile << best_score << "\n";
		//cout << "route:" << "\n";
		if(total_best_score >= best_score) {
			total_best_score = best_score;
			total_best_route = best_route;
		}

	}
	auto end = chrono::system_clock::now();
	auto dur = end - start;
	auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    // 要した時間をミリ秒（1/1000秒）に変換して表示
    cout << msec << " milli sec \n";

	cout << total_best_score << "\n";
	output_svg(cities, total_best_route);
	outputfile.close();

}
// 初期値をランダムに1000回くらい
// 近傍の決め方
