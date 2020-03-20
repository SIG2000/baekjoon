/*
*	baekjoon online judge : 9466
*/
#include <iostream>	
#include <vector>	
#include <stack>
#include <cstdio>
using namespace std;

struct Info { // 학생 번호와 선호 학생 번호

	int number, target;

	Info(int num, int target) : number(num), target(target) {}
};

void termProject(vector<int> &, int);

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int test_case, N;
	cin >> test_case;

	for (int i = 0; i < test_case; i++) {

		cin >> N;
		vector<int> students(N + 1);
		for (int i = 1; i < N + 1; i++)
			cin >> students[i];

		termProject(students, N + 1); // 팀에 속하지 못한 학생 수 출력
		students.clear();
	}
	return 0;
}

void termProject(vector<int> &students, int size) {

	stack<Info> _stack;
	vector<bool> visited(size, false);
	vector<int> cycled(size, 0); // 사이클 확인

	int member = 0, depth = 1; // 깊이
	for (int i = 1; i < size; i++) {

		if (visited[i]) continue;

		_stack.emplace(i, students[i]);
		int start = depth; // 시작 깊이
		while (!_stack.empty()) {

			int current = _stack.top().number;
			int target = _stack.top().target;
			_stack.pop();

			if (visited[current]) { // 다른 정점을 볼 때
				if (cycled[current] - start >= 0) { 
				// ((사이클 + 시작 깊이 - 1) - 시작 깊이) >= 0 일 때 사이클에 포함
					member += depth - cycled[current]; // final depth - back edge depth = 팀 구성원 수 
					break;
				} // 사이클이 발견되면 멤버 추가
				continue;
			}
			visited[current] = true;
			cycled[current] = depth;

			_stack.emplace(target, students[target]); // 목표 학생 저장
			depth++;
		}
	}
	cout << (size - 1) - member << endl;
}