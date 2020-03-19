/*
*	baekjoon online judge : 11047
*/
#include <iostream>	
#include <vector>
using namespace std;

int greedy(vector<int> &, int);

int main() {

	int N, K;
	cin >> N >> K;

	vector<int> coins(N);
	for (auto &coin : coins)
		cin >> coin;

	cout << greedy(coins, K) << endl; // 최소 동전 개수 출력

	return 0;
}

int greedy(vector<int> &coins, int money) {

	const int size = coins.size();
	int count = 0, idx = size - 1;

	while (money != 0) {

		if (coins[idx] <= money) count += money / coins[idx], money %= coins[idx];
		idx--;
	}
	return count;
}