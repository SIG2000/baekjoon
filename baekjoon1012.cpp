#include <iostream>
#include <vector>
#include <array>
using namespace std;

typedef struct test {

	array<int, 3> test_case; // horizontal, vertical, count
	vector<vector<int>> location;

} test;

void addTest(vector<test>&);
int check(test&, int, int, int, int);

int main() {

	int test_case_count, count = 0, i, j, z;
	vector<test> input;

	cin >> test_case_count;
	for (i = 0; i < test_case_count; i++) {
		addTest(input);
	}

	for (i = 0; i < test_case_count; i++) {

		for (j = 0; j < input[i].test_case[0]; j++) {

			for (z = 0; z < input[i].test_case[1]; z++) {
				count += check(input[i], j, z, input[i].test_case[0], input[i].test_case[1]);
			}
		}

		cout << count << endl;
		count = 0;
	}

	return 0;
}

void addTest(vector<test> &input) {

	test t;
	int count, i, x, y;
	vector<int> temp;
	cin >> t.test_case[0] >> t.test_case[1] >> t.test_case[2];

	for (i = 0; i < t.test_case[1]; i++) {
		temp.push_back(0);
	}

	for (i = 0; i < t.test_case[0]; i++) {
		t.location.push_back(temp);
	}
	count = t.test_case[2];

	for (i = 0; i < count; i++) {
		cin >> x >> y;
		t.location[x][y] = 1;
	}
	input.push_back(t);

}

int check(test& t, int x, int y, int x_max, int y_max) {

	if (x < 0 || y < 0 || x >= x_max || y >= y_max) return 0; // 종료 조건
	if (t.location[x][y] < 1) return 0;

	t.location[x][y] = 0;

	check(t, x - 1, y, x_max, y_max);
	check(t, x + 1, y, x_max, y_max);
	check(t, x, y - 1, x_max, y_max);
	check(t, x, y + 1, x_max, y_max); // 이미 카운트하여 반환값을 받지않음

	return 1;

}