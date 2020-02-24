/*
	최적화 1회
*/
#include <iostream>	
#include <vector>
using namespace std;

int nQueen(vector<vector<int>> &, int, int, int &);

int main() {

	int N, count = 0;
	cin >> N;

	vector<int> col(N);
	vector<vector<int>> chessBoard(N);
	for (int i = 0; i < N; i++) {
		chessBoard[i] = col;
	}

	nQueen(chessBoard, 0, N, count);
	cout << count << endl;

	return 0;

}

int nQueen(vector<vector<int>> &board, int x, int N, int &count) { // N = Ymax = count of queen

	int i, j = 0;
	bool is_putatble = true;

	if (x >= N) return 1;

	for (i = 0; i < N; i++) { // col[0] ~ col[N - 1]

		for (j = 1; j <= x; j++) { // 자신의 위쪽과 대각선들을 모두 비교

			is_putatble = false;

			if (board[x - j][i]) break; // 같은 행에 놓여져 있을 때

			if (x - j > -1 && i - j > -1) {
				if (board[x - j][i - j]) break; // 왼쪽 위 대각선에 놓여져 있을 때
			}

			if (x - j > -1 && i + j < N) {
				if (board[x - j][i + j]) break; // 왼쪽 아래 대각선에 놓여져 있을 때
			}

			is_putatble = true;

		}

		if (is_putatble) {

			board[x][i]++; // 현재 자리에 퀸 배치
			count += nQueen(board, x + 1, N, count);
			board[x][i]--; // 다른 경우의 수를 찾기 위해 퀸 회수

		}

	}

	return 0;

}