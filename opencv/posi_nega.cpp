#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

#define FOR(i,r,n) for(int i=(int)(r); i < (int)(n); i++)
#define REP(i,n) FOR(i,0,n)
int main(void) {
	string input_file_name = "lena.png";
	string output_file_name = "posi_nega.png";

	Mat img = imread(input_file_name, 1);
	int height = img.rows;
	int width = img.cols;

	REP(x, width) {
		REP(y, height) {
			REP(i, 3) {
				img.at<Vec3b>(y,x)[i] = 255 - img.at<Vec3b>(y,x)[i];
			}
			cout << img.at<Vec3b>(y,x) << "\n";
		}
	}

	imwrite(output_file_name, img);

	return(0);
}
