/*
*	baekjoon online judge
*/
#include <iostream>	
#include <vector>
#include <algorithm>
using namespace std;

inline int greedy(vector<int> &, int N);

int main() {

	int N;
	cin >> N;

	vector<int> time_table(N);
	for (auto &t : time_table)
		cin >> t;

	cout << greedy(time_table, N) << endl;

	return 0;
}

inline int greedy(vector<int> &table, int size) {

	int time = 0;

	sort(table.begin(), table.end(), less<int>());
	for (auto t : table)
		time += t * size--;

	return time;
}