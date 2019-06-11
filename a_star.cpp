#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <queue>
using namespace std;
typedef pair<string, int> value_type;

struct second_order {
	bool operator()(const value_type& x, const value_type& y) const {
		return x.second > y.second;
	}
};

int hamming(string state) {
	int score = 0;
	for(int i=0; i < state.size(); i++) {
		if(i != state.size() - 1 && int(state[i])-48 != i+1) {
			score++;
			continue;
		} 
		if(i == state.size() - 1 && int(state[i])-48 != 0) {
			score++;
		}
	}
	return score;
}

int manhattan(string state) {
	int score = 0;
	for(int i=0; i < state.size(); i++) {
		int num = int(state[i])-48;
		if(num == 0) num = 9;
		int x = (num-1) / 3;
		int y = (num-1) % 3;
		int xx = i / 3;
		int yy = i % 3;
		int d = abs(x - xx) + abs(y - yy);
		score += d;
	}
	return score;
}

bool is_goal(string state) {
	if(state == "123456780") {
		return true;
	}
	return false;
}

int blank_position(string state) {
	for(int i=0; i<state.size(); i++) {
		if(int(state[i])-48 == 0) return i;
	}
}

string swap(string& state, int i, int j) {
	int tmp = state[i]; state[i] = state[j]; state[j] = tmp;
	return state;
}

int print(string state) {
	cout << state << "\n";
}

void traceback(map<string, string> parents, string state) {
	if(parents[state] == "") return;
	else {
		cout << state << "\n";
		traceback(parents, parents[state]);
	}
}

int main(void) {
	cout << "近似的な最短ルートを探索したい3*3の盤面の初期状態を9桁の文字で入力してください。余白は0とします:" << "\n";
	string initial_state;
	cin >> initial_state;
	multimap<string, int> open;
	multimap<string, int> closed;
	map<string, int> dist_from_start;
	map<string, string> parents;

	//
	//string initial_state = "143726850"; //18
	//string initial_state = "867254301"; //31
	//string initial_state = "534126780"; //14
	//string initial_state = "123456708"; //1
	//string initial_state = "063582741"; //30 O3最適化でも1分くらいかかる
	open.emplace(initial_state, manhattan(initial_state));
	dist_from_start.emplace(initial_state, 0);
	parents.emplace(initial_state, "");

	int num_of_loop = 0;
	while(true) {
		if(open.size() == 0) {
			cout << "No answer" << "\n";
			return 0;
		}
		
		//openリストとclosedリストの表示
		//cout << "open:" << "\n";
		//for(auto it = open.begin(); it != open.end(); ++it) {
		//	cout << "key= " << it->first << ", val= : " << it->second << "\n";
		//}
		//cout << "closed:" << "\n";
		//for(auto it = closed.begin(); it != closed.end(); ++it) {
		//	cout << "key= " << it->first << ", val= : " << it->second << "\n";
		//}
	
		
		//priority_queueを使う場合
		//priority_queue<value_type, vector<value_type>, second_order> que;
		//value_type p;
		//for(auto it = open.begin(); it != open.end(); ++it) {
			//cout << "key= " << it->first << ", val= : " << it->second << "\n";
		//	p = make_pair(it->first, it->second);
		//	que.push(p);
		//}
		//value_type item = que.top();
		//auto itr = open.find(item.first);


		auto min_itr = open.begin();
		int min_score = 1e9;
		for(auto itr = open.begin(); itr != open.end(); ++itr) {
			int score = itr->second + dist_from_start.find(itr->first)->second;
			if(min_score >= score) {
				min_score = score;
				min_itr = itr;
			}
		}
		

		auto itr = min_itr;
		closed.emplace(itr->first, itr->second);
		open.erase(itr);
		//cout << "現在の状況" << itr->first << "\n";
		//cout << "スタートからの距離" << dist_from_start.find(itr->first)->second << endl;

		string current_state(itr->first);
		if(is_goal(itr->first)) {
			cout << "探索終了" << endl;
			cout << "マスのスライド回数の近似的な最小値:" << dist_from_start.find(itr->first)->second << endl;
			//cout << "ループ回数:" << num_of_loop << "回\n";
			cout << "近似的な最短ルートのトレースバック\n";
			traceback(parents, "123456780");
			return 0;
		} else {
			vector<int> transition = {-3, -1, 1, 3};
			for(auto t:transition) {
				int blank = blank_position(current_state);
				if(blank+t >= 0 and blank+t < current_state.size()) {
					if(blank % 3 == 0 and t == -1) continue;
					if(blank % 3 == 2 and t == 1) continue;
					int current_h = itr->second;
					int current_g = dist_from_start.find(current_state)->second;
					int current_f = current_h + current_g;
					string possible_state(current_state);
					possible_state = swap(possible_state, blank, blank+t);
					int possible_h = manhattan(possible_state);
					int possible_g = current_g + 1;
					int possible_f = possible_h + possible_g;

					if(open.find(possible_state) == open.end() && closed.find(possible_state) == closed.end()) {
						dist_from_start.emplace(possible_state, possible_g);
						parents.emplace(possible_state, current_state);
						open.emplace(possible_state, possible_h);

					} else if (open.find(possible_state) != open.end() && possible_f < current_f) {
						dist_from_start.emplace(possible_state, possible_g);
						parents.emplace(possible_state, current_state);
						open.find(possible_state)->second = possible_h;

					} else if (closed.find(possible_state) != closed.end() && possible_f < current_f) {
						dist_from_start.emplace(possible_state, possible_g);
						parents.emplace(possible_state, current_state);
						open.emplace(possible_state, possible_h);
						closed.erase(closed.find(possible_state));
					}
				}
			}
		}
		num_of_loop++;
	}
}

