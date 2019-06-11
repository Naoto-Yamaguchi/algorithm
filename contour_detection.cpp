#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

#define FOR(i,r,n) for(int i=(int)(r); i < (int)(n); i++)
#define REP(i,n) FOR(i,0,n)

//反時計周りに走査する。
pair<int, int> next_direction(int x, int y) {
	if(x == -1 & y == -1) return make_pair(-1, 0);
	else if(x == -1 & y == 0) return make_pair(-1, 1);
	else if(x == -1 & y == 1) return make_pair(0, 1);
	else if(x == 0 & y == 1) return make_pair(1, 1);
	else if(x == 1 & y == 1) return make_pair(1, 0);
	else if(x == 1 & y == 0) return make_pair(1, -1);
	else if(x == 1 & y == -1) return make_pair(0, -1);
	else if(x == 0 & y == -1) return make_pair(-1, -1);
	else return make_pair(0, 0);
}

bool is_black(const Mat &img, int x, int y) {
	return img.at<Vec3b>(y, x)[0] == 0;
}

//定められた追跡順に従い捜査し、移動先を定める
pair<int, int> scan(const Mat &img, int x, int y, int a, int b, int depth) {
	pair<int, int> p;
	if(is_black(img, x+a, y+b)) return make_pair(a, b);
	else if(depth >= 8) return make_pair(0, 0);
	else {
		depth++;
		pair<int, int> next_dir = next_direction(a, b);
		return scan(img, x, y, next_dir.first, next_dir.second, depth);
	}
}

//前回の追跡点との位置関係から、追跡順を定める。
pair<int, int> first_scan_direction(int x, int y) {
	if(x == 0 & y == 0) return make_pair(-1, 1);
	else if(x == -1 & y == -1) return make_pair(1, -1);
	else if(x == 0 & y == -1) return make_pair(1, 0);
	else if(x == 1 & y == -1) return make_pair(1, 1);
	else if(x == 1 & y == 0) return make_pair(0, 1);
	else if(x == 1 & y == 1) return make_pair(-1, 1);
	else if(x == 0 & y == 1) return make_pair(-1, 0);
	else if(x == -1 & y == 1) return make_pair(-1, -1);
	else if(x == -1 & y == 0) return make_pair(0, -1);
	else return make_pair(0, 0);
}

// 実際に移動して、出力画像の書き換え、周の長さの伸長をおこなう。
void contour_extraction(const Mat &img1, Mat &img2, int sx, int sy, int x, int y, int last_mvdir_x, int last_mvdir_y, float perimeter) {
	if(sx == x & sy == y & perimeter != 0) {
		cout << perimeter << "\n";
	} else {
		//今いるところを黒く塗る
		REP(i, 3) {
			img2.at<Vec3b>(y, x)[i] = 0;
		}
		//はじめに見るべき向きを返す
		pair<int, int> first_scan_dir = first_scan_direction(last_mvdir_x, last_mvdir_y);
		//移動するべき向きを返し、増やす周長を計算する
		pair<int, int> move_direction = scan(img1, x, y, first_scan_dir.first, first_scan_dir.second, 0);
		int mvdir_x = move_direction.first;
		int mvdir_y = move_direction.second;
		float length = sqrt(pow(mvdir_x, 2) + pow(mvdir_y, 2));
		//移動する
		contour_extraction(img1, img2, sx, sy, x+mvdir_x, y+mvdir_y, mvdir_x, mvdir_y, perimeter+length);
	}
}

pair<int, int> raster_scan(const Mat &img, int width, int height) {
	REP(x, width) {
		REP(y, height) {
			if(img.at<Vec3b>(y,x)[0] == 0) {
				return make_pair(x, y);
			}
		}
	}
	return make_pair(0,0);
} 

int main(void) {
	string input_file_name = "hokkaido.png";
	string output_file_name = "output.png";

	Mat img1 = imread(input_file_name, 1);
	Mat img2 = imread(input_file_name, 1);
	int height = img1.rows;
	int width = img1.cols;

	REP(x, width) {
		REP(y, height) {
			REP(i, 3) {
				img2.at<Vec3b> (y,x)[i] = 255;
			}
		}
	}

	pair<int, int> start_point = raster_scan(img1, width, height);
	int sx = start_point.first;
	int sy = start_point.second;
	REP(i, 3) {
		img2.at<Vec3b>(sy, sx)[i] = 0;
	}

	pair<int, int> p = scan(img1, sx, sy, -1, 1, 0);
	if(p.first == 0 & p.second == 0) imwrite(output_file_name, img2);
	else {
		float perimeter = 0;
		contour_extraction(img1, img2, sx, sy, sx, sy, p.first, p.second, perimeter);
		imwrite(output_file_name, img2);
	}
	return(0);
}
