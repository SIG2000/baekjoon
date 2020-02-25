/*
*	baekjoon online judge 7576 : 토마토
*/ 
#include <iostream>	
#include <vector>
#include <deque>
using namespace std;

typedef struct position {

	int x;
	int y;

	position(int x, int y) : x(x), y(y) {}

} position ;

int tomato(vector<vector<int>> &, int, int);
void inline push(vector<vector<int>> &, deque<position> &, int, int, int);

int main() {

	int M, N, i, j, result;
	cin >> M >> N;

	vector<int> col(M);
	vector<vector<int>> arr;
	arr.reserve(N);

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			cin >> col[j];
		}
		arr.push_back(col);
	}

	result = tomato(arr, N, M);

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) 
			if (!arr[i][j]) {
				cout << -1 << endl;
				return 0;
			}
	}

	cout << result - 1 << endl; // 시작점을 1일로 잡았다.

	return 0;
}

inline void push(vector<vector<int>> &arr, deque<position> &posQue
	, int x_pos, int y_pos, int value) {

	(++arr[x_pos][y_pos]) += value;
	posQue.push_back(position(x_pos, y_pos));

}

int tomato(vector<vector<int>> &arr, int x_max, int y_max) {

	deque<position> posQue;
	int x_pos, y_pos;

	// 입력할때 수행 하는 것과 복잡도 차이가 없음.
	for (x_pos = 0; x_pos < x_max; x_pos++) {
		for (y_pos = 0; y_pos < y_max; y_pos++) {
			if (arr[x_pos][y_pos] > 0) {
				posQue.push_back(position(x_pos, y_pos));
			}
		}
	}

	while (true) {

		if (posQue.empty()) return arr[x_pos][y_pos];
		
		x_pos = posQue.front().x;
		y_pos = posQue.front().y;
		posQue.pop_front();

		if (x_pos > 0) {
			if (!(arr[x_pos - 1][y_pos])) { // 0일때만
				push(arr, posQue, x_pos - 1, y_pos, arr[x_pos][y_pos]);
			}
		}
		if (x_pos < x_max - 1) {
			if (!(arr[x_pos + 1][y_pos])) { 
				push(arr, posQue, x_pos + 1, y_pos, arr[x_pos][y_pos]);
			}
		}
		if (y_pos > 0) {
			if (!(arr[x_pos][y_pos - 1])) {
				push(arr, posQue, x_pos, y_pos - 1, arr[x_pos][y_pos]);
			}
		}
		if (y_pos < y_max - 1) {
			if (!(arr[x_pos][y_pos + 1])) {
				push(arr, posQue, x_pos, y_pos + 1, arr[x_pos][y_pos]);
			}
		}
	}
}
