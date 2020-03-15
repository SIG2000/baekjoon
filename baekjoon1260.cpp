/*
*	baekjoon online judge 1260
*/
#include <iostream>	
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

using Graph = vector<vector<int>>;

struct Compare_1 { // stack은 내림차순
	bool operator()(int a, int b) { return a > b; }
};

struct Compare_2 { // queue는 오름차순
	bool operator()(int a, int b) { return a < b; }
};

void bfs(Graph &, int);
void dfs(Graph &, int);

int main() {

	ios::sync_with_stdio(false);

	int N, M, begin;
	cin >> N >> M >> begin;

	// 간선 입력
	int vertex_1, vertex_2;
	Graph graph(N + 1);
	for (int i = 0; i < M; i++) {

		cin >> vertex_1 >> vertex_2;
		graph[vertex_1].emplace_back(vertex_2);
		graph[vertex_2].emplace_back(vertex_1); // 양방향
	}
	// ----------------------------------------------------
	
	dfs(graph, begin); // dfs 수행 결과 출력
	cout << endl;
	bfs(graph, begin); // bfs 수행 결과 출력

	return 0;
}

void dfs(Graph &graph, int begin) {

	stack<int> stack_;
	stack_.emplace(begin);

	vector<bool> visited((int)graph.size() + 1, false); // 방문 여부
	while (!stack_.empty()) {
		
		int current_v = stack_.top(); // 현재 정점
		if (visited[current_v]) {

			stack_.pop();
			continue;
		}
		visited[current_v] = true;
		cout << current_v << ' ';
		stack_.pop();
		
		sort(graph[current_v].begin(), graph[current_v].end(), Compare_1()); // 큰 정점(역순)
		for (const auto vertex : graph[current_v])
			stack_.emplace(vertex);
	}
}

void bfs(Graph &graph, int begin) {

	queue<int> que_;
	que_.emplace(begin);

	vector<bool> visited((int)graph.size() + 1, false); // 방문 여부
	while (!que_.empty()) {

		int current_v = que_.front(); // 현재 정점
		if (visited[current_v]) {

			que_.pop();
			continue;
		}
		visited[current_v] = true;
		cout << current_v << ' ';
		que_.pop();

		sort(graph[current_v].begin(), graph[current_v].end(), Compare_2()); // 작은 정점
		for (const auto vertex : graph[current_v])
			que_.emplace(vertex);
	}
}
