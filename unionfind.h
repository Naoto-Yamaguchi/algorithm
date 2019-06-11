using namespace std;
class UnionFind {
	static const int MAX_N = 1000000;
private:
	int parent[MAX_N], rank[MAX_N];
public:
	UnionFind(int n) {
		init(n);
	}
	UnionFind() {
		init(MAX_N);
	}

	void init(int n) {
		for(int i=0; i<n; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if(a != b) {
			if(rank[a] == rank[b]) {
				parent[b] = a;
				rank[a] += 1;
			} else if (rank[a] > rank[b]) {
				parent[b] = a;
			} else {
				parent[a] = b;
			}	
		}
	}

	int find(int n) {
		return parent[n] == n ? n : parent[n] = find(parent[n]);
	}

	bool same(int a, int b) {
		return (find(a) == find(b));		
	}

	void print(int n) {
		for(int i=0; i<n; i++) {
			cout << parent[i] << ":";
			//if(i % 10 == 9) cout << "\n";
		}
		cout << endl;
	}
};
