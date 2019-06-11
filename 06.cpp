#include <iostream>
#include "unionfind.h"

using namespace std;

int main(void) {
	int n = 30;
	UnionFind f(n);

	cout << f.find(2) << endl;

	f.unite(2, 10);
	f.unite(10, 20);
	f.unite(5, 2);

	cout << f.find(10) << endl;
	cout << f.same(5, 10) << endl;
	cout << f.same(5, 20) << endl;
	cout << f.same(15, 10) << endl;

	f.print(n);
}

