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
	// �׷��� �Է�

	cin >> vertex_1 >> vertex_2;
	minimumCost(graph, vertex_1, vertex_2);
	// �ּ� ���� �̵� ��� ���ϱ�

	return 0;
}

void minimumCost(vector<vector<Node>> &graph, int origin, int destination) {

	const int size = graph.size();
	p_queue p_que;
	p_que.emplace(origin, 0);

	vector<Node> distance_table(size, { 0, INT32_MAX }); // ���� ������ �ּ� ���� ���� ������ ����
	distance_table[origin] = { origin, 0 };
	vector<bool> visited(size, false); // �湮 Ȯ��
	while (!p_que.empty()) {

		int current = p_que.top().vertex; // ���� ����
		p_que.pop();

		if (visited[current]) continue;
		visited[current] = true;

		for (auto const &g : graph[current]) {

			int temp = distance_table[current].cost + g.cost;
			if (distance_table[g.vertex].cost > temp) {

				distance_table[g.vertex] = { current, temp }; // ���� ����(����)�� ��ǥ ���� ���
				p_que.emplace(g.vertex, temp);
			}
		}
	}
	// ��� ���
	cout << distance_table[destination].cost << endl; 
	// �湮 ��ġ ã��(������)
	int count = 0; // ���Ե� ������ ����
	findRoute(distance_table, origin, destination, destination, count); 
}

void findRoute(vector<Node> &table, int origin, int destination, int current, int &count) {

	count++;
	if (origin == current) { // ���� ����
		
		cout << count << endl << current << ' '; // ������ ������ ��� ���� ���
		return;
	}

	int pre = table[current].vertex; // ���� ���� ����
	findRoute(table, origin, destination, pre, count); // recursion
	cout << current << ' ';
}