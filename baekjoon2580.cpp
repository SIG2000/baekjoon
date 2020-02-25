/*
*	beakjoon online judge 2580 : sudoku
*/
#include <iostream>	
#include <vector>
using namespace std;

const int SUDOKU_LINE = 9;
const int SUB_LINE = 3;
int sudoku[SUDOKU_LINE][SUDOKU_LINE];

// sudoku[(1)][(2)] (1) = squares number, (2) = sub square index 
// ex) sudoku[1][5] = 2nd (0 = 1st) square, index = 5

/*

0 1 2	0 1 2	0 1 2
3 4 5	3 4 5	3 4 5
6 7 8	6 7 8	6 7 8

0 1 2	0 1 2	0 1 2
3 4 5	3 4 5	3 4 5
6 7 8	6 7 8	6 7 8

0 1 2	0 1 2	0 1 2
3 4 5	3 4 5	3 4 5
6 7 8	6 7 8	6 7 8

*/

typedef struct position {
	
	int nth, idx;

	position() {}
	position(int nth, int idx) : nth(nth), idx(idx) {}

} position;

inline void makeSudoku(vector<position> &);
bool SolveSudoku(vector<position> &, int);
inline void PrintResult();

int main() {

	vector<position> empty_space;
	// 고정 배열을 쓰는 것이 좋으나 STL 연습을 위해 사용

	makeSudoku(empty_space);
	SolveSudoku(empty_space, 0);
	PrintResult();

	return 0;

}

inline void makeSudoku(vector<position> &empty_space) {

	for (int i = 0; i < SUDOKU_LINE; i += SUB_LINE) {
		for (int j = 0; j < SUDOKU_LINE; j += SUB_LINE) {
			for (int k = 0; k < SUB_LINE; k++) {
				for (int l = 0; l < SUB_LINE; l++) {

					cin >> sudoku[i + k][j + l];

					if (!sudoku[i + k][j + l]) // 입력 값이 0일 때, 빈 공간으로 지정
						empty_space.push_back(position(i + k, j + l));

				}
			}
		}
	}

}

bool SolveSudoku(vector<position> &empty_space, int depth = 0) {

	if (depth >= (int)empty_space.size()) return true; // 빈 공간이 없을 때 종료

	int i, j, nth, idx, current, i_temp, j_temp;

	bool distinct[SUDOKU_LINE];
	fill_n(distinct, SUDOKU_LINE, false);

	nth = empty_space[depth].nth;
	idx = empty_space[depth].idx;

	// h checking
	i_temp = (nth / 3) * 3;
	j_temp = (idx / 3) * 3;
	for (i = i_temp; i < i_temp + SUB_LINE; i++) {
		for (j = j_temp; j < j_temp + SUB_LINE; j++) {
			current = sudoku[i][j];
			if (current) { // if not 'zero'
				distinct[current - 1] = true;
			}
		}
	}

	// v checking
	i_temp = nth % 3;
	j_temp = idx % 3;
	for (i = i_temp; i < SUDOKU_LINE; i+= SUB_LINE) {
		for (j = j_temp; j < SUDOKU_LINE; j+= SUB_LINE) {
			current = sudoku[i][j];
			if (current) { // if not 'zero'
				distinct[current - 1] = true;
			}
		}
	}

	// sub square checking
	for (i = 0; i < SUDOKU_LINE; i++) {
		current = sudoku[nth][i];
		if (current) { // if not 'zero'
			distinct[current - 1] = true;
		}
	}

	for (i = 0; i < SUDOKU_LINE; i++) {
		if (!distinct[i]) {

			sudoku[nth][idx] = i + 1;
			distinct[i] = true;

			if(SolveSudoku(empty_space, depth + 1))
				return true; // 모든 칸을 채웠을 때를 true 반환
			else {
				distinct[i] = false;
				sudoku[nth][idx] = 0;
			}

		}
	}

	return false;

}

inline void PrintResult() {

	for (int i = 0; i < SUDOKU_LINE; i += SUDOKU_LINE / 3) {
		for (int j = 0; j < SUDOKU_LINE; j += SUDOKU_LINE / 3) {
			for (int k = 0; k < SUDOKU_LINE / 3; k++) {
				for (int l = 0; l < SUDOKU_LINE / 3; l++) {
					cout << sudoku[i + k][j + l] << ' ';
				}
			}
			cout << endl;
		}
	}

}