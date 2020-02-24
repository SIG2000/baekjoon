/*
	����ȭ 1ȸ
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

		for (j = 1; j <= x; j++) { // �ڽ��� ���ʰ� �밢������ ��� ��

			is_putatble = false;

			if (board[x - j][i]) break; // ���� �࿡ ������ ���� ��

			if (x - j > -1 && i - j > -1) {
				if (board[x - j][i - j]) break; // ���� �� �밢���� ������ ���� ��
			}

			if (x - j > -1 && i + j < N) {
				if (board[x - j][i + j]) break; // ���� �Ʒ� �밢���� ������ ���� ��
			}

			is_putatble = true;

		}

		if (is_putatble) {

			board[x][i]++; // ���� �ڸ��� �� ��ġ
			count += nQueen(board, x + 1, N, count);
			board[x][i]--; // �ٸ� ����� ���� ã�� ���� �� ȸ��

		}

	}

	return 0;

}