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
};

inline istream& operator>>(istream& in, Edge& edge) {

	cin >> edge.arrive >> edge.elapsed;
	return in;
}

void findRoute(multimap<int, Edge> &, vector<int> &);
inline void printRoute(vector<int> &);

int main() {

	ios::sync_with_stdio(false);

	int begin, N, M, i; // N = node, M = edge
	cin >> N >> M;

	multimap<int, Edge> graph;
	vector<int> elapsed(N + 1, INT32_MAX);
	elapsed[FIRST_CITY] = 0; // ���� ��� 0, ������ ������ �Ÿ� infinity

	Edge edge;
	for (i = 0; i < M; i++) {
		cin >> begin >> edge;
		graph.insert(make_pair(begin, edge));
	}	// graph ����

	findRoute(graph, elapsed);
	// �ִ� ��� ã��
	printRoute(elapsed);
	// ��� ���
	return 0;
}

void findRoute(multimap<int, Edge> &graph, vector<int> &elapsed) {

	const int size = static_cast<int>(elapsed.size()) + 1;
	vector<int> cycle(size, 0); // �� ��� �� ����Ŭ
	vector<bool> is_exist(size, false); // �� ��� �� ť�� ���� ���� ����

	queue<int> nodeQue;
	nodeQue.push(FIRST_CITY);

	while (!nodeQue.empty()) {

		int current_city = nodeQue.front(); 
		nodeQue.pop();
		is_exist[current_city] = false; 

		if (cycle[current_city] >= size) {
			// size��ŭ ��ȸ�Ͽ����� ����ؼ� ������ �� ù ��° ���ÿ� �ִ� �ְ� ����
			elapsed[FIRST_CITY] = INT32_MAX;
			return;
		}

		// -----------------------------------------------------------------------------
		// pair<multimap<int, Edge>::iterator, multimap<int, Edge>::iterator>
		auto pair_iter = graph.equal_range(current_city); 
		for (auto iter = pair_iter.first; iter != pair_iter.second; iter++) {

			int temp = elapsed[iter->first] + iter->second.elapsed;
			int arrive = iter->second.arrive;

			if (elapsed[arrive] > temp) {
				elapsed[arrive] = temp;

				if (!is_exist[arrive]) {

					nodeQue.push(arrive);
					is_exist[arrive] = true;
				}
				// ť�� ��� ���� ���� �� ����
			}
		}

		cycle[current_city]++;
		// -----------------------------------------------------------------------------
	}
}

inline void printRoute(vector<int> &elapsed) {

	if (elapsed[FIRST_CITY] == INT32_MAX) {
		// ������ ���� ������ ���ư� �� �ִ��� �ֵ��� ����
		cout << NOT_FOUND_OR_PAST << endl; 
	}
	else {
		for (auto i = elapsed.begin() + 2; i < elapsed.end(); i++) {

			if (*i == INT32_MAX) cout << NOT_FOUND_OR_PAST << endl;
			else cout << *i << endl;
		}
	}
}
