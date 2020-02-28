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

	// ���� �Է�
	// ----------------------------------------------------
	for (i = 0; i < node; i++) {

		cin >> route;
		graph_table.insert(make_pair(route.origin, route));

	}
	// ----------------------------------------------------

	// �ʱ� �Ÿ� ����
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

	// �ִ� ��� ã��
	minimum_route(distance_table, graph_table, routeQue);

	// ��� ���
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
		// ���� ����� ���� �̱�

		if (!visited[current_stand - 1]) {

			visited[current_stand - 1] = true;
			//------------------------------------------------------------------ 
			// �ش� ������ �湮 ���� �ʾ��� ��
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
				// �� ���� ����� �� ����
			}
			// ���� ���� �������� ����ϴ� ��带 �켱 ���� ť�� ����
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

// <int, int>�� �ƴ� <int, Route>�� �����Ͽ� �޸� 2�� ����
// ���� �迭 ����Ͽ� �ð� 2��, �޸� ���� ����
// �ð� ���⵵ O((V + E)logE), V = ����, E = ����