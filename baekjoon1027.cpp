/*
*	baekjoon online judge 1027 : 고층 건물
*/ 
#include <iostream>
#include <vector>
using namespace std;

int view(vector<int> &);

int main() {

	int N, height;
	vector<int> Building;

	cin >> N;

	for (int i = 0; i < N; i++) {

		cin >> height;
		Building.push_back(height);

	}

	cout << view(Building) << endl;

	return 0;

}

int view(vector<int> & building) {

	int size = building.size();
	int current_height = 0, view_count = 0, max_view_count = INT_FAST32_MIN;
	double height_average, max_gradient, min_gradient;

	for (int i = 0; i < size; i++) {
		cout << endl;
		current_height = building[i];
		min_gradient = 1000000000; // 백준 알고리즘에서 1e9 같은 형식을 지원하지 않는다.

		for (int j = i - 1; j > -1; j--) {

			height_average = (double)(current_height - building[j]) / (i - j);

			if (height_average < min_gradient) {

				min_gradient = height_average;
				view_count++;

			}

		}

		max_gradient = -1000000000;

		for (int j = i + 1; j < size; j++) {

			height_average = (double)(building[j] - current_height) / (j - i);

			if (height_average > max_gradient) {

				max_gradient = height_average;
				view_count++;

			}


		}

		if (max_view_count < view_count) max_view_count = view_count;
		view_count = 0;
	}

	return max_view_count;
}
