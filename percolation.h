#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <vector>
#include <random>
#include "unionfind.h"
using namespace std;
random_device rnd;
mt19937 mt(rnd());
uniform_real_distribution<> rand1(0, 1);


class Percolation {
private:
	vector<vector<int>> matrix;
	UnionFind f;
	int _size;
	int _elementCnt;
public:
	Percolation(int size) {
		_size = size;
		_elementCnt = size * size;
		f.init(size*size);
		initMatrix();
	};

	void print(int size) {
		for(int i=0; i<size; i++) {
			for(int j=0; j<size; j++) {
				cout << matrix[i][j] << ":";
			}
			cout << endl;
		}
	}

	void initMatrix() {
		matrix.assign(_size, vector<int>(_size, 0));
	}
	
	void simulation(double probability) {
		initMatrix();
		for(int i=0; i<_size; i++) {
			for(int j=0; j<_size; j++) {
				if (rand1(mt) <= probability) matrix[i][j] = 1;
			}
		}
	}

	void detectConnectedComponents() {
		f.init(_elementCnt);
		//f.print(_elementCnt);
		for(int row=0; row<_size; row++) {
			for(int col=0; col<_size; col++) {
				if(row != _size-1) uniteBottomGrid(row, col);
				if(col != _size-1) uniteRightGrid(row, col);
			}
		}
	}

	void uniteBottomGrid(int row, int col) {
		int idx = _size*row + col;
		if(matrix[row][col] == 1 && matrix[row+1][col] == 1) {
			f.unite(idx, idx+_size);
		}
	}
	
	void uniteRightGrid(int row, int col) {
		int idx = _size*row + col;
		if(matrix[row][col] == 1 && matrix[row][col+1] == 1) {
			f.unite(idx, idx+1);
		}
	}

	int checkPercolation() {
		for(int i=0; i<_size; i++) {
			//cout << f.find(i) << ":\n";
			for(int j = _elementCnt - _size; j < _elementCnt; j++) {
				//	cout << f.find(j) << ":";
				if(f.find(i) == f.find(j)) return 1;
			}
			//cout << "\n";
		}
		return 0;
	}

};

#endif
