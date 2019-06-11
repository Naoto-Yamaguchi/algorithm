#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <utility>
#include <random>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
using namespace cv;

random_device rnd;
mt19937 get_rand_mt;

#define FOR(i,r,n) for(int i=(int)(r); i < (int)(n); i++)
#define REP(i,n) FOR(i,0,n)

typedef pair<pair<int, int>, int> value_type;

int get_gray(Mat &img, int x, int y) {
	int b = img.at<Vec3b>(y,x)[0];
	int g = img.at<Vec3b>(y,x)[1];
	int r = img.at<Vec3b>(y,x)[2];
	int gray = (b + 4*g + 2*r) / 7;
	return gray;
}

int main(void) {
	string input_file_name = "obokata.png";
	string output_file_name = "flattened_obokata.png";

	Mat img = imread(input_file_name, 1);
	int height = img.rows; int width = img.cols;

	vector<int> flattened(256);
	int n = height * width / 256;
	int p = height * width % 256;
	for(int i=0; i<256; i++) {
		flattened[i] = n;
	}
	for(int i=0; i<p; i++) {
		flattened[i]++;
	}

	vector<vector<int>> hist(256);
	REP(y, height) {
		REP(x, width) {
			int b = img.at<Vec3b>(y,x)[0];
			int g = img.at<Vec3b>(y,x)[1];
			int r = img.at<Vec3b>(y,x)[2];
			int gray = (b + 4*g + 2*r) / 7;
			REP(i, 3) {
				img.at<Vec3b>(y,x)[i] = gray;
			}
			hist[gray].push_back(width * y + x);
		}
	}

	vector<int> vc;
	for(auto h:hist) {
		shuffle(h.begin(), h.end(), get_rand_mt);
		for(auto e:h) {
			vc.push_back(e);
		}
	}

	REP(i, 256) {
		REP(j, flattened[i]) {
			int num = vc[i * flattened[i] + j];
			int x = num % width;
			int y = num / width;
			cout << "x: " << x << " y: " << y << " i: " << i << "\n";
			REP(k, 3) {
				img.at<Vec3b>(y,x)[k] = i;
			}
		}
	}
	imwrite(output_file_name, img);
	return(0);
}
