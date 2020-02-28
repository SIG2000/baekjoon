/*
*	baekjoon online judge : 1753
*/
#include <iostream>	
#include <queue>
#include <vector>
#include <map>
using namespace std;

const int MAX_INT = 2147483647;

typedef struct Route {

	int origin;
	int destination;
	int distance;

	Route& operator()(int orig, int dest, int d) {

		origin = orig;
		destination = dest;
		distance = d;

		return *this;

	}

	friend istream& operator>> (istream& in, Route& route) {

		cin >> route.origin >> route.destination >> route.distance;
		return in;

	}

} Route;

class Compare { // function object
public:
	bool operator()(const Route& a, const Route& b) {
		return a.distance > b.distance;
	}
};

typedef priority_queue<Route, vector<Route>, Compare> p_queue;

void minimum_route(vector<int> &, multimap<int, Route> &, p_queue &);
inline void printRoute(vector<int> &, int);

int main() {

	ios::sync_with_stdio(false);

	Route route;
	p_queue routeQue;
	int root, node, stand, i;

	cin >> root >> node;
	cin >> stand;

	vector<int> distance_table;
	multimap<int, Route> graph_table;

	// 간선 입력
	// ----------------------------------------------------
	for (i = 0; i < node; i++) {

		cin >> route;
		graph_table.insert(make_pair(route.origin, route));

	}
	// ----------------------------------------------------

	// 초기 거리 지정
	// ----------------------------------------------------
	i = 0;
	while (++i < stand) {
		distance_table.push_back(MAX_INT);
		routeQue.push(route(0, i, MAX_INT));
	}

	distance_table.push_back(0);
	routeQue.push(route(0, i, 0));

	while (++i <= root) {
		distance_table.push_back(MAX_INT);
		routeQue.push(route(0, i, MAX_INT));
	}
	// ----------------------------------------------------

	// 최단 경로 찾기
	minimum_route(distance_table, graph_table, routeQue);

	// 경로 출력
	printRoute(distance_table, root);

	return 0;

}

void minimum_route(vector<int> &distance_table, multimap<int, Route> &graph_table, p_queue &routeQue) {

	int current_stand, temp;
	Route route;

	typedef multimap<int, Route>::iterator map_iter; 
	map_iter iter = graph_table.begin();

	pair<map_iter, map_iter> pair_iter;

	vector<bool> visited(distance_table.size());
	fill(visited.begin(), visited.end(), false);

	while (!routeQue.empty()) {

		current_stand = routeQue.top().destination;
		routeQue.pop();
		// 가장 가까운 정점 뽑기

		if (!visited[current_stand - 1]) {

			visited[current_stand - 1] = true;
			//------------------------------------------------------------------ 
			// 해당 정점을 방문 하지 않았을 때
			pair_iter = graph_table.equal_range(current_stand);

			for (iter = pair_iter.first; iter != pair_iter.second; iter++) {
				
				temp = iter->second.distance + distance_table[current_stand - 1];

				if (temp < 0) continue; // infinity + constrant = infinity

				if (distance_table[iter->second.destination - 1] > temp) {
					distance_table[iter->second.destination - 1] = temp;

					route = iter->second;
					route.distance = temp;
					routeQue.push(route);

				}
				// 더 작은 비용일 때 갱신
			}
			// 현재 기준 정점에서 출발하는 노드를 우선 순위 큐에 삽입
			//------------------------------------------------------------------
		}
	}
}

inline void printRoute(vector<int> &distance_table, int root) {

	for (int i = 0; i < root; i++) {

		if (distance_table[i] == MAX_INT) cout << "INF" << '\n';
		else cout << distance_table[i] << '\n';

	}
}

// <int, int>가 아닌 <int, Route>로 지정하여 메모리 2배 증가
// 가변 배열 사용하여 시간 2배, 메모리 소폭 증가
// 시간 복잡도 O((V + E)logE), V = 정점, E = 간선