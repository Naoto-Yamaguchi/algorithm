#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

#define FOR(i,r,n) for(int i=(int)(r); i < (int)(n); i++)
#define REP(i,n) FOR(i,0,n)
int main(void) {
	string input_file_name = "lena.png";
	string output_file_name = "gray_scale.png";

	Mat img = imread(input_file_name, 1);
	int height = img.rows;
	int width = img.cols;

	REP(x, width) {
		REP(y, height) {
			//cout << img.at<Vec3b>(y,x) << "\n";
			int b = img.at<Vec3b>(y,x)[0];
			int g = img.at<Vec3b>(y,x)[1];
			int r = img.at<Vec3b>(y,x)[2];
			int gray = (b + 4*g + 2*r) / 7;
			cout << gray << "\n";
			//cout <<  b << "\n";
			REP(i, 3) {
				img.at<Vec3b>(y,x)[i] = gray;
			}
			cout << img.at<Vec3b>(y,x) << "\n";
		}
	}

	imwrite(output_file_name, img);

	return(0);
}
