/*
*	baekjoon online judge : 9019
*	���� �� ������ ����� �ƴ� ���� ���
*/
#include <iostream>	
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int LENGTH = 4;
const int REGISTER_MAX = 9999;
const int MAX = 10000;

inline short opD(short);
inline short opS(short);
inline short opL(short);
inline short opR(short);
inline bool push(queue<short> &, vector<bool> &, short);
inline bool found(short, short);
string dslr(short, short);

int main() {

	ios::sync_with_stdio(false);

	int T;
	cin >> T;

	short A, B;
	for (int i = 0; i < T; i++) {

		cin >> A >> B;
		cout << dslr(A, B) << endl;
	}

	return 0;
}

string dslr(short _register, short find_value) {

	short temp; // ���� ��� �� �ӽ� ����

	vector<string> command(MAX); // �� ���ں� �ּ� ��ɾ�
	queue<short> _que;
	vector<bool> visited(MAX, false); // �湮 Ȯ��
	_que.emplace(_register);
	visited[_register] = true;
	while (true) {

		short current = _que.front();
		_que.pop();

		temp = opD(current);
		if (push(_que, visited, temp)) command[temp] = command[current] + "D";// ���� ��ġ�� ��ɾ� ���� ��ɾ�� ���ļ� ����
		if (found(temp, find_value)) break; // ���� ������ ���� ����

		temp = opS(current);
		if (push(_que, visited, temp)) command[temp] = command[current] + "S";
		if (found(temp, find_value)) break;

		temp = opL(current);
		if (push(_que, visited, temp)) command[temp] = command[current] + "L";
		if (found(temp, find_value)) break;

		temp = opR(current);
		if (push(_que, visited, temp)) command[temp] = command[current] + "R";
		if (found(temp, find_value)) break;
	}

	return command[temp];
}

inline bool push(queue<short> & _que, vector<bool> & visited, short value) {

	if (visited[value]) return false;

	visited[value] = true;
	_que.emplace(value);
	return true;
}

inline bool found(short value, short find_value) {

	return value == find_value;
}

inline short opD(short _register) {

	return (_register * 2) % MAX;
}

inline short opS(short _register) {

	if (_register) // 0�� �ƴ� ��
		return _register - 1;
	else return REGISTER_MAX;
}

inline short opL(short _register) {

	// 1000���� ������, �������� 10�� + ��. 1234 -> 2341
	return (_register % 1000) * 10 + _register / 1000;
}

inline short opR(short _register) {

	// 10���� ������, �������� 1000�� + ��. 1234 -> 4123
	return (_register % 10) * 1000 + _register / 10;
}