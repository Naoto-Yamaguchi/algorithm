#include <iostream>
#include "cellularautomaton.h"

using namespace std;

int main(void) {
	CellularAutomaton cell(500, 161);
	cell.init_transition();

	string filename = "cellularautomaton.html";
	ofstream writing_file;
	writing_file.open(filename, ios::out);
	writing_file << "<svg width=\"" << 10000 << "\" height=\"" << 10000 << "\">" << "\n\t";
	int steps = 500;

	for(int i=0; i<steps; i++) {
		cell.update();
		cell.print(i, writing_file);
	}
	writing_file << "</svg> " << "\n";
}
