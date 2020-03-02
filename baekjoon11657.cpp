#include <iostream>	
#include <vector>	
#include <queue>
#include <map>
using namespace std;

const int NOT_FOUND_OR_PAST = -1;
const int FIRST_CITY = 1;

using Edge = struct Edge {

	int arrive;
	int elapsed;

	friend istream& operator>>(istream& in, Edge& edge) {
		cin >> edge.arrive >> edge.elapsed;
		return in;
	}
};

void find_route(multimap<int, Edge> &, vector<int> &);
inline void print_route(vector<int> &);

int main() {

	ios::sync_with_stdio(false);

	int N, M, i, begin;
	Edge edge;
	cin >> N >> M;

	multimap<int, Edge> graph;

	vector<int> elapsedTime(N, INT32_MAX);
	elapsedTime[FIRST_CITY - 1] = 0;
	// 1번 도시는 0, 나머지는 무한대

	// queue에 현재 push 되어있는 지 확인

	for (i = 0; i < M; i++) {
		cin >> begin >> edge;
		graph.insert(make_pair(begin, edge));
	}
	// 인접 리스트 생성

	find_route(graph, elapsedTime);
	// 이동 시간 계산

	print_route(elapsedTime);
	// 결과 출력

	return 0;
}

void find_route(multimap<int, Edge> &graph, vector<int> &elapsed) {

	const int size = (int) elapsed.size();
	vector<int> cycle(size, 0);
	vector<bool> is_exist(size, false);

	queue<int> routeQue;
	routeQue.push(FIRST_CITY);

	// node 번 cycle 결과 계속 작아질 때 negative cycle이 존재한다.
	while (!routeQue.empty()) {

		int current_city = routeQue.front();
		routeQue.pop();
		is_exist[current_city - 1] = false;

		if (cycle[current_city - 1] >= size + 1) {
			elapsed[FIRST_CITY - 1] = INT32_MAX;
			return;
		}
		// 계속해서 작아진다면 첫 번째 도시에 최댓값을 입력하고 종료

		// 현재 기준 도시
		// ----------------------------------------------------------------------
		using map_iter = multimap<int, Edge>::iterator;
		pair<map_iter, map_iter> pair_iter = graph.equal_range(current_city);
		map_iter iter;

		for (iter = pair_iter.first; iter != pair_iter.second; iter++) {

			int temp = elapsed[iter->first - 1] + iter->second.elapsed;
			int arr_idx = iter->second.arrive - 1;
			
			// 탈출 조건보다 작아질 때 시작 위치의 시간을 -1로 지정하고 반환

			if (elapsed[arr_idx] > temp) {
				elapsed[arr_idx] = temp;

				if (!is_exist[arr_idx]) {

					routeQue.push(iter->second.arrive);
					is_exist[arr_idx] = true;
				}
				// 큐에 들어 있지 않을 때 저장
			}
			// 더 빠른 시간 저장
		}

		cycle[current_city - 1]++;

		// ----------------------------------------------------------------------
		// 현재 도시에서 갈 수 있는 모든 노선 검사
	}
}

inline void print_route(vector<int> &elapsed) {

	if (elapsed[FIRST_CITY - 1] == INT32_MAX) cout << NOT_FOUND_OR_PAST << endl;
	else {
		vector<int>::iterator iter;

		for (iter = elapsed.begin() + 1; iter != elapsed.end(); iter++) {

			if (*iter == INT32_MAX) cout << NOT_FOUND_OR_PAST << endl;
			else cout << *iter << endl;
		}
	}
}