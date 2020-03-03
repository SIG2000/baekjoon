/*
*	baekjoon online judge : 1753
*	INF = INT32_MAX
*/
#include <iostream>	
#include <queue>	
#include <vector>	
#include <unordered_map>
using namespace std;

using Edge = struct Edge {

	int destination;
	int distance;

	bool operator()(const Edge &a, const Edge &b) const {
		return a.distance > b.distance;
	}
};

inline istream& operator>>(istream& in, Edge& edge) {

	cin >> edge.destination >> edge.distance;
	return in;
}

using p_queue = priority_queue<Edge, vector<Edge>, Edge>;

void minimumRoute(vector<int> &, unordered_multimap<int, Edge> &, int);
inline void printeRoute(vector<int> &);

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M, i, stand, origin; // stand = standard node
	cin >> N >> M >> stand;

	// 간선 입력
	unordered_multimap<int, Edge> graph;
	graph.reserve(M);
	Edge edge;
	for (i = 0; i < M; i++) {

		cin >> origin >> edge;
		graph.insert({ origin, edge });
	}

	// 초기 거리 지정
	vector<int> distance_table(N + 1, INT32_MAX);
	distance_table[stand] = 0;

	// 최단 경로 찾기
	minimumRoute(distance_table, graph, stand);

	// 경로 출력
	printeRoute(distance_table);

	return 0;
}

void minimumRoute(vector<int> &distance, unordered_multimap<int, Edge> &graph, int stand) {

	p_queue edgeQue;
	const int size = static_cast<int>(distance.size());

	edgeQue.push({ stand, 0 }); // 시작 위치

	int i;
	for (i = 0; i < stand; i++) edgeQue.push({ i, INT32_MAX });
	for (++i; i < size; i++) edgeQue.push({ i, INT32_MAX });
	// 나머지 위치에 infinity

	vector<bool> visited(size, false);

	while (!edgeQue.empty()) {

		int current_stand = edgeQue.top().destination;
		edgeQue.pop();
		// 가까운 정점 뽑기
		if (!visited[current_stand]) {
			visited[current_stand] = true;
			// ----------------------------------------------------------------------------------
			// pair_iter = pair<unordered_multimap<int, Route>::iterator, unordered_multimap<int, Route>::iterator>
			auto pair_iter = graph.equal_range(current_stand);
			for (auto iter = pair_iter.first; iter != pair_iter.second; iter++) {

				int temp = iter->second.distance + distance[current_stand];

				if (temp < 0) continue; // infinity + constrant = infinity

				int dest = iter->second.destination;
				if (distance[dest] > temp) {
					distance[dest] = temp;

					edgeQue.push({ dest, temp });
				}
				// 더 작은 비용이면 갱신
			}
			// 현재 기준 정점에서 출발하는 노드를 우선 순위 큐에 삽입
			// ----------------------------------------------------------------------------------
		}
	}
}

inline void printeRoute(vector<int> &distance) {

	for (auto iter = distance.begin() + 1; iter != distance.end(); iter++) {

		if (*iter == INT32_MAX) cout << "INF" << '\n';
		else cout << *iter << '\n';
	}
}