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
	// 1�� ���ô� 0, �������� ���Ѵ�

	// queue�� ���� push �Ǿ��ִ� �� Ȯ��

	for (i = 0; i < M; i++) {
		cin >> begin >> edge;
		graph.insert(make_pair(begin, edge));
	}
	// ���� ����Ʈ ����

	find_route(graph, elapsedTime);
	// �̵� �ð� ���

	print_route(elapsedTime);
	// ��� ���

	return 0;
}

void find_route(multimap<int, Edge> &graph, vector<int> &elapsed) {

	const int size = (int) elapsed.size();
	vector<int> cycle(size, 0);
	vector<bool> is_exist(size, false);

	queue<int> routeQue;
	routeQue.push(FIRST_CITY);

	// node �� cycle ��� ��� �۾��� �� negative cycle�� �����Ѵ�.
	while (!routeQue.empty()) {

		int current_city = routeQue.front();
		routeQue.pop();
		is_exist[current_city - 1] = false;

		if (cycle[current_city - 1] >= size + 1) {
			elapsed[FIRST_CITY - 1] = INT32_MAX;
			return;
		}
		// ����ؼ� �۾����ٸ� ù ��° ���ÿ� �ִ��� �Է��ϰ� ����

		// ���� ���� ����
		// ----------------------------------------------------------------------
		using map_iter = multimap<int, Edge>::iterator;
		pair<map_iter, map_iter> pair_iter = graph.equal_range(current_city);
		map_iter iter;

		for (iter = pair_iter.first; iter != pair_iter.second; iter++) {

			int temp = elapsed[iter->first - 1] + iter->second.elapsed;
			int arr_idx = iter->second.arrive - 1;
			
			// Ż�� ���Ǻ��� �۾��� �� ���� ��ġ�� �ð��� -1�� �����ϰ� ��ȯ

			if (elapsed[arr_idx] > temp) {
				elapsed[arr_idx] = temp;

				if (!is_exist[arr_idx]) {

					routeQue.push(iter->second.arrive);
					is_exist[arr_idx] = true;
				}
				// ť�� ��� ���� ���� �� ����
			}
			// �� ���� �ð� ����
		}

		cycle[current_city - 1]++;

		// ----------------------------------------------------------------------
		// ���� ���ÿ��� �� �� �ִ� ��� �뼱 �˻�
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