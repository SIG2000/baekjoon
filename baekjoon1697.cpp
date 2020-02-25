/*
*	baekjoon online judge 1697 : 술래잡기
*/
#include <iostream>	
#include <vector>
#include <deque>
using namespace std;

int hideAndSeek(vector<int> &, int, int);
inline bool push_and_check(vector<int> &, deque<int> &, int, int, int);
inline bool check(int, int);

int main() {

	int N, K;
	cin >> N >> K;

	if (N >= K) { // 같은 위치면 0초, N이 더 앞에 있다면 그 차만큼
		cout << N - K << endl;
		return 0;
	}

	vector<int> road(K + 3);
	road[N] = 1;

	cout << hideAndSeek(road, N, K) - 1 << endl;

	return 0;
}

inline bool push_and_check(vector<int> &road, deque<int> &posQue, int pos, int value, int find_value) {

	posQue.push_back(pos);
	(++road[pos]) += value;
	
	return check(pos, find_value);

}

inline bool check(int value, int find_value) {

	if (value == find_value) return true;
	return false;

}

int hideAndSeek(vector<int> &road, int N, int K) {

	deque<int> posQue;
	int pos = N, pos_max = K + 3;
	posQue.push_back(N);

	while (!posQue.empty()) {

		pos = posQue.front();
		posQue.pop_front();

		if (pos > 0) {
			if (!road[pos - 1]) { // 0일 때 동작
				if (push_and_check(road, posQue, pos - 1, road[pos], K)) {
					return road[pos - 1];
				}
			}
		}
		if (pos < pos_max - 1) {
			if (!road[pos + 1]) {
				if (push_and_check(road, posQue, pos + 1, road[pos], K)) {
					return road[pos + 1];
				}
			}
		}
		if (pos * 2 < pos_max - 1) {
			if (!road[pos * 2]) {
				if (push_and_check(road, posQue, pos * 2, road[pos], K)) {
					return road[pos * 2];
				}
			}
		}
	}

	return road[pos];
}
