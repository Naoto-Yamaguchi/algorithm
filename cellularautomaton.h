#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <fstream>

using namespace std;

class CellularAutomaton {
private:
	vector<int> cell;
	int _size, _rule;
	map<int, int> transition;
public:
	CellularAutomaton(int size, int rule) {
		_size = size;
		_rule = rule;
		cell.assign(_size, 0);
		cell[_size/2] = 1;
	}

	void init_transition() {
		int rule = _rule;
		for(int i=7;i>=0;i--) {
			transition[i] = rule /(int) pow(2, i);
			rule = rule % (int)pow(2, i);
		}
	}

	void update() {
		int next_cell[_size];
		for(int i=0; i<_size; i++) {
			int current_state;
			if(i == 0) {
				current_state = cell[_size-1] * 4 + cell[i] * 2 + cell[i+1];
			} else if (i == _size-1) {
				current_state = cell[i-1] * 4 + cell[i] * 2 + cell[0];
			} else {
				current_state = cell[i-1] * 4 + cell[i] * 2 + cell[i+1];
			}
			next_cell[i] = transition[current_state];
		}
		for(int i=0; i<_size; i++) {
			cell[i] = next_cell[i];
		}
	}

	void print(int j, ofstream &writing_file) {
		for(int i=0; i<_size; i++) {
			if(cell[i] == 1) {
				writing_file << "<rect x=\"" << i << "\" y=\"" << j << "\" width=\"" << 1 << "\" height=\"" << 1 << "\" fill=\"black\" />" << "\n\t";
			}
		}
	}
};

