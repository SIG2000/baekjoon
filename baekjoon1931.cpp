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

		if (a.end == b.end) return a.start < b.start; // 일찍 끝나는 순, 같으면 시간 시간이 이른 순
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
	// 각 회의의 시간을 스케줄에 저장
	cout << maxMeetingCount(schedule, N) << endl;

	return 0;
}

int maxMeetingCount(vector<Meeting> &schedule, int N) {

	sort(schedule.begin(), schedule.end(), Meeting()); // 가장 빨리 끝나는 회의 순으로 정렬 nlogn

	int count = 0, current_time = -1; // end = 최종 회의가 끝난 현재의 시간, 초기 -1
	for (auto const &meeting : schedule) {

		if (current_time > meeting.start) continue; // 이전 회의랑 겹칠 때
		current_time = meeting.end;
		
		count++; // 개수 증가
	}
	return count;
}