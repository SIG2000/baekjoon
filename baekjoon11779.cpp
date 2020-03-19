/*
*	baekjoon online judge : 11779
*	Dijkstra + recursion
*/
#include <iostream>	
#include <vector>
#include <queue>
using namespace std;

struct Node {

	int vertex, cost;

	Node() {}
	Node(int vertex, int cost) : vertex(vertex), cost(cost) {}
	bool operator()(const Node &a, const Node &b) { return a.cost > b.cost; }
};

typedef priority_queue <Node, vector<Node>, Node> p_queue;

void minimumCost(vector<vector<Node>> &, int, int);
void findRoute(vector<Node> &, int, int, int, int&);

int main() {

	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	
	int vertex_1, vertex_2, cost;
	vector<vector<Node>> graph(n + 1);
	for (int i = 0; i < m; i++) {

		cin >> vertex_1 >> vertex_2 >> cost;
		graph[vertex_1].emplace_back(vertex_2, cost);
	}
	// 그래프 입력

	cin >> vertex_1 >> vertex_2;
	minimumCost(graph, vertex_1, vertex_2);
	// 최소 비용과 이동 경로 구하기

	return 0;
}

void minimumCost(vector<vector<Node>> &graph, int origin, int destination) {

	const int size = graph.size();
	p_queue p_que;
	p_que.emplace(origin, 0);

	vector<Node> distance_table(size, { 0, INT32_MAX }); // 현재 정점의 최소 비용과 이전 정점을 저장
	distance_table[origin] = { origin, 0 };
	vector<bool> visited(size, false); // 방문 확인
	while (!p_que.empty()) {

		int current = p_que.top().vertex; // 현재 정점
		p_que.pop();

		if (visited[current]) continue;
		visited[current] = true;

		for (auto const &g : graph[current]) {

			int temp = distance_table[current].cost + g.cost;
			if (distance_table[g.vertex].cost > temp) {

				distance_table[g.vertex] = { current, temp }; // 이전 정점(현재)과 목표 지점 비용
				p_que.emplace(g.vertex, temp);
			}
		}
	}
	// 비용 출력
	cout << distance_table[destination].cost << endl; 
	// 방문 위치 찾기(역추적)
	int count = 0; // 포함된 도시의 개수
	findRoute(distance_table, origin, destination, destination, count); 
}

void findRoute(vector<Node> &table, int origin, int destination, int current, int &count) {

	count++;
	if (origin == current) { // 종료 조건
		
		cout << count << endl << current << ' '; // 도시의 개수와 출발 도시 출력
		return;
	}

	int pre = table[current].vertex; // 이전 정점 저장
	findRoute(table, origin, destination, pre, count); // recursion
	cout << current << ' ';
}