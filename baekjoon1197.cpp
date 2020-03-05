/*
*	baekjoon online judge : 1197
*	���� ��ġ�� ���� ���� ���� ������ ����
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

	// edge ����
	vector<vector<Edge>> graph(V + 1);
	int origin, destination, distance;
	for (int i = 0; i < E; i++) {

		cin >> origin >> destination >> distance;
		graph[origin].emplace_back(destination, distance);
		graph[destination].emplace_back(origin, distance);
		// ���� �׷���
	}

	// ��� ���, ���� �������� �Էµ� ���� ��ġ�� ���� ��ġ��
	cout << minSpanningTree(graph, origin) << endl;

	return 0;
}

int minSpanningTree(vector<vector<Edge>> &graph, int FIRST) {

	size_t size = graph.size();
	unsigned int weight = 0, node = 0;

	vector<bool> visited(size, false);
	// �湮 ����

	p_queue Que; // ���� ���� �Ÿ� ���� �켱 ���� ť

	int current = FIRST;
	while (node < size - 2) {

		for (const auto &G : graph[current]) {

			if (visited[current]) break;  // �湮�� �����̸� �ٷ� ���� Ż��
			Que.emplace(G);
		}
		visited[current] = true;

		while (true) {
			
			auto &G = Que.top();
			if (!visited[G.destination]) {

				weight += G.distance; // Ʈ�� ��� ����ġ �� ��ȯ
				current = G.destination;

				Que.pop();
				break;
			}
			Que.pop();
		} // �湮 ���� ���� ���� �� ���� ���� ����ġ ����
		node++;
	}

	return weight;
}