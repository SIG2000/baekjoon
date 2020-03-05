/*
*	baekjoon online judge : 1197
*	시작 위치는 가장 먼저 들어온 값으로 고정
*/
#include <iostream>	
#include <vector>
#include <queue>
using namespace std;

struct Edge {

	int destination;
	int distance;

	Edge() {}
	Edge(int dest, int dis) : destination(dest), distance(dis) {}

	bool operator()(const Edge& a, const Edge& b) {
		return a.distance > b.distance;
	}
};

using p_queue = priority_queue<Edge, vector<Edge>, Edge>;

int minSpanningTree(vector<vector<Edge>> &, int);

int main() {

	ios::sync_with_stdio(false);

	int V, E; // V = node, E = edge
	cin >> V >> E;

	// edge 저장
	vector<vector<Edge>> graph(V + 1);
	int origin, destination, distance;
	for (int i = 0; i < E; i++) {

		cin >> origin >> destination >> distance;
		graph[origin].emplace_back(destination, distance);
		graph[destination].emplace_back(origin, distance);
		// 무향 그래프
	}

	// 결과 출력, 가장 마지막에 입력된 시작 위치를 시작 위치로
	cout << minSpanningTree(graph, origin) << endl;

	return 0;
}

int minSpanningTree(vector<vector<Edge>> &graph, int FIRST) {

	size_t size = graph.size();
	unsigned int weight = 0, node = 0;

	vector<bool> visited(size, false);
	// 방문 여부

	p_queue Que; // 가장 작은 거리 지정 우선 순위 큐

	int current = FIRST;
	while (node < size - 2) {

		for (const auto &G : graph[current]) {

			if (visited[current]) break;  // 방문한 정점이면 바로 루프 탈출
			Que.emplace(G);
		}
		visited[current] = true;

		while (true) {
			
			auto &G = Que.top();
			if (!visited[G.destination]) {

				weight += G.distance; // 트리 대신 가중치 합 반환
				current = G.destination;

				Que.pop();
				break;
			}
			Que.pop();
		} // 방문 하지 않은 정점 중 가장 작은 가중치 저장
		node++;
	}

	return weight;
}