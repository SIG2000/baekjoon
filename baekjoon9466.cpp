/*
*	baekjoon online judge : 9466
*/
#include <iostream>	
#include <vector>	
#include <stack>
#include <cstdio>
using namespace std;

struct Info { // �л� ��ȣ�� ��ȣ �л� ��ȣ

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

		termProject(students, N + 1); // ���� ������ ���� �л� �� ���
		students.clear();
	}
	return 0;
}

void termProject(vector<int> &students, int size) {

	stack<Info> _stack;
	vector<bool> visited(size, false);
	vector<int> cycled(size, 0); // ����Ŭ Ȯ��

	int member = 0, depth = 1; // ����
	for (int i = 1; i < size; i++) {

		if (visited[i]) continue;

		_stack.emplace(i, students[i]);
		int start = depth; // ���� ����
		while (!_stack.empty()) {

			int current = _stack.top().number;
			int target = _stack.top().target;
			_stack.pop();

			if (visited[current]) { // �ٸ� ������ �� ��
				if (cycled[current] - start >= 0) { 
				// ((����Ŭ + ���� ���� - 1) - ���� ����) >= 0 �� �� ����Ŭ�� ����
					member += depth - cycled[current]; // final depth - back edge depth = �� ������ �� 
					break;
				} // ����Ŭ�� �߰ߵǸ� ��� �߰�
				continue;
			}
			visited[current] = true;
			cycled[current] = depth;

			_stack.emplace(target, students[target]); // ��ǥ �л� ����
			depth++;
		}
	}
	cout << (size - 1) - member << endl;
}