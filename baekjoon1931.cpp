#include <iostream>	
#include <vector>
#include <algorithm>
using namespace std;

struct Meeting { 

	int start, end; // 0 ~ INT32_MAX

	bool operator()(const Meeting &a, const Meeting &b) { // compare

		return (a.end - a.start) < (b.end - b.start);
	}
};

istream& operator>>(istream &in, Meeting &meeting) {

	cin >> meeting.start >> meeting.end;
	return in;
}

int MaxMeetingCount(vector<Meeting> &, int N);

int main() {

	ios::sync_with_stdio(false);

	int N; // N = input
	cin >> N;

	vector<Meeting> schedule;
	schedule.reserve(N);
	Meeting meeting;
	for (int i = 0; i < N; i++) {

		cin >> meeting;
		schedule.push_back(meeting);
	}
	// 각 회의의 시간을 스케줄에 저장
	cout << MaxMeetingCount(schedule, N) << endl;
	// 최대로 진행할 수 있는 회의 수 출력
	
	return 0;
}

int MaxMeetingCount(vector<Meeting> &schedule, int N) {

	vector<bool> is_posible(N, true); // 가리키는 시간에 회의가 가능한 지 저장

	sort(schedule.begin(), schedule.end(), Meeting()); // 우선 진행 시간이 가장 작은 순으로 정렬



	return 0;
}