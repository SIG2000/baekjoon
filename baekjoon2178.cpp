#include <iostream>	
#include <vector>
#include <deque>
#include <string>	
#include <cmath>
using namespace std;

const int CANDIDATE_COUNT = 4;

typedef struct XY {

	int x;
	int y;
	
	XY(int x, int y) : x(x), y(y) {}

} XY;

void miro(vector<vector<int>> &, vector<vector<bool>> &, int, int);
inline void push(vector<vector<int>> &, deque<XY> &, vector<vector<bool>>&, int, int, int);

int main() {

	int N, M, i, j;
	string str, temp;
	cin >> N >> M;

	vector<int> col(M);
	vector<vector<int>> arr;

	vector<bool> v_col(M);
	vector<vector<bool>> visited;

	for (i = 0; i < N; i++) {

		cin >> str;

		for (j = 0; j < M; j++) {

			temp = str[j];
			col[j] = atoi(temp.c_str());

		}

		arr.push_back(col);
		visited.push_back(v_col);

	}

	miro(arr, visited, N, M);

	cout << arr[N - 1][M - 1];
	cout << endl;

	return 0;

}

void miro(vector<vector<int>> &vec, vector<vector<bool>> &visited, int x_max, int y_max) {

	deque<XY> posQue;
	int x_pos = 0, y_pos = 0;
	visited[x_pos][y_pos] = true;

	int size = vec.size();
	int value;

	while (true) {

		value = vec[x_pos][y_pos];

		// 상하좌우 0이 아니며, 방문하지 않았을 때 queue에 삽입

		if (x_pos > 0)
			if (vec[x_pos - 1][y_pos] && !visited[x_pos - 1][y_pos])
				push(vec, posQue, visited, x_pos - 1, y_pos, value);

		if (x_pos < x_max - 1)
			if (vec[x_pos + 1][y_pos] && !visited[x_pos + 1][y_pos])
				push(vec, posQue, visited, x_pos + 1, y_pos, value);

		if (y_pos > 0)
			if (vec[x_pos][y_pos - 1] && !visited[x_pos][y_pos - 1])
				push(vec, posQue, visited, x_pos, y_pos - 1, value);

		if (y_pos < y_max - 1)
			if (vec[x_pos][y_pos + 1] && !visited[x_pos][y_pos + 1])
				push(vec, posQue, visited, x_pos, y_pos + 1, value);

		if (posQue.empty()) return;

		x_pos = posQue.front().x;
		y_pos = posQue.front().y;
		posQue.pop_front();


	}
}

inline void push(vector<vector<int>> &vec, deque<XY> &que, 
	vector<vector<bool>> &visited, int x, int y, int value) {

	que.push_back(XY(x, y));
	visited[x][y] = true;
	vec[x][y] += value;

}

/*
vector<int>::const_iterator iter_col;
vector<vector<int>>::const_iterator iter_arr;

for (iter_arr = arr.begin(); iter_arr != arr.end(); iter_arr++) {

	for (iter_col = iter_arr->begin(); iter_col != iter_arr->end(); iter_col++) {

		cout << *iter_col << ' ';

	}

	cout << endl;

} // using iterator exam
*/
