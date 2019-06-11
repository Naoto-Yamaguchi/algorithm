#include <iostream>
#include <vector>

using namespace std;

int n;

int dfs(int r, vector<int> board) {
	if(r == n) {return 1;}
	int sum = 0;
	for(int c=0; c<n; c++) {
		int flag = 0;
		for(int k=1; k<=r; k++) {
			if (board[r-k]==c+k or board[r-k]==c-k or board[r-k]==c) {
				flag = 1;
			}
		}
		if (flag == 0) {
			board[r] = c;
			sum += dfs(r+1, board);
		}
	}
	return sum;
}

int main(void) {
	cin >> n;
	vector<int> board(n);
	cout <<dfs(0, board) << "\n";
}
