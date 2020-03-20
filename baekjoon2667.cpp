/*
*	baekjoon online judge : 2667
*/
#include <iostream>	
#include <vector>
#include <string>	
#include <algorithm>
#include <stack>
using namespace std;

struct idx { 

	int i, j; 

	idx(int i, int j) : i(i), j(j) {}
};

void dfs(vector<vector<int>> &);
bool exist(vector<vector<int>> &, vector<vector<bool>> &, int, int, int); // ������ ��ġ ����Ʈ ���� ���� Ȯ��, �湮

int main() {

	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	string apartment;
	apartment.reserve(N);
	// ----------------------------------------
	vector<vector<int>> complex(N);
	for (auto &com : complex) {

		com.reserve(N);
		cin >> apartment;
		for (auto const apart : apartment) com.push_back(apart - 48); // ASCII
	}
	// �迭 �Է�
	dfs(complex);
	// ���� ã��
	return 0;
}

void dfs(vector<vector<int>> &complex) {

	const int size = complex.size();

	int count = 0; // ���� ����
	vector<int> apart_count; // ����Ʈ ����
	
	stack<idx> _stack;
	vector<vector<bool>> visited(size, vector<bool>(size, false)); // �湮 Ȯ��

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			if (visited[i][j]) continue;
			if (complex[i][j]) _stack.emplace(i, j);
			else continue;

			visited[i][j] = true;
			apart_count.push_back(0); // ����Ʈ ����
			while (!_stack.empty()) {

				apart_count[count]++;
				idx current = _stack.top();
				_stack.pop();

				// -----------------------------------------------------------
				if (exist(complex, visited, size, current.i - 1, current.j)) 
					_stack.emplace(current.i - 1, current.j);
				if (exist(complex, visited, size, current.i, current.j - 1))
					_stack.emplace(current.i, current.j - 1);
				if (exist(complex, visited, size, current.i + 1, current.j))
					_stack.emplace(current.i + 1, current.j);
				if (exist(complex, visited, size, current.i, current.j + 1))
					_stack.emplace(current.i, current.j + 1);
				// �����¿� �˻�
			}
			count++;
		}
	}

	cout << count << endl; // ���� ��

	sort(apart_count.begin(), apart_count.end()); // ��������
	for (auto a_count : apart_count)
		cout << a_count << endl; // ���� �� ����Ʈ ��
}

bool exist(vector<vector<int>> &complex, vector<vector<bool>> &visited, int size, int i, int j) {

	if (i < 0 || j < 0 || i > size - 1 || j > size - 1) return false;

	if (visited[i][j]) return false;
	visited[i][j] = true;

	if (complex[i][j]) return true;
	else return false;
}
