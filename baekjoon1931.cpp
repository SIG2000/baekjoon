/*
*	baekjoon online judge : 1931	
*/
#include <iostream>	
#include <vector>
#include <algorithm>
using namespace std;

struct Meeting {

	int start, end;

	Meeting(int start, int end) : start(start), end(end) {}
	Meeting() {}

	bool operator()(const Meeting &a, const Meeting &b) { // compare

		if (a.end == b.end) return a.start < b.start; // ���� ������ ��, ������ �ð� �ð��� �̸� ��
		else return a.end < b.end;
	}
};

int maxMeetingCount(vector<Meeting> &, int N);

int main() {

	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	int start, end;
	vector<Meeting> schedule;
	schedule.reserve(N);
	for (int i = 0; i < N; i++) {

		cin >> start >> end;
		schedule.emplace_back(start, end);
	}
	// �� ȸ���� �ð��� �����ٿ� ����
	cout << maxMeetingCount(schedule, N) << endl;

	return 0;
}

int maxMeetingCount(vector<Meeting> &schedule, int N) {

	sort(schedule.begin(), schedule.end(), Meeting()); // ���� ���� ������ ȸ�� ������ ���� nlogn

	int count = 0, current_time = -1; // end = ���� ȸ�ǰ� ���� ������ �ð�, �ʱ� -1
	for (auto const &meeting : schedule) {

		if (current_time > meeting.start) continue; // ���� ȸ�Ƕ� ��ĥ ��
		current_time = meeting.end;
		
		count++; // ���� ����
	}
	return count;
}