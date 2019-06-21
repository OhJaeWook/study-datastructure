#include <stdio.h>


/*

입력  첫 번째 줄에 가로, 세로의 크기를 나타내는 n이 입력된다.(n은 30이하의 자연수) 두 번째 줄부터 n줄에 걸쳐서 n개의 0과 1이 공백으로 구분되어 입력된다.

출력  첫째 줄에 두더지 굴의 수를 출력한다. 둘째 줄부터 각 두더지 굴의 크기를 내림 차순으로 한 줄에 하나씩 출력한다.
7 
0 1 1 0 1 0 0 
0 1 1 0 1 0 1
1 1 1 0 1 0 1
0 0 0 0 1 1 1
0 1 0 0 0 0 0
0 1 1 1 1 1 0
0 1 1 1 0 0 0

3 
9
8
7

*/

#define MAX_N 30
#define DIRECTION 4

int doduziGul[MAX_N][MAX_N] = {0,};
int doduziCount;
int size[MAX_N] = { 0, };

int dx[DIRECTION] = { -1 , 0 , 1 , 0 };
int dy[DIRECTION] = { 0 , 1 , 0 , -1 };
int GulIndex = 2;

void dfs(int x, int y) {

	size[doduziCount]++;
	doduziGul[x][y] = GulIndex;

	for (int i = 0; i < DIRECTION; i++) {

		if ((x + dx[i] >= 0 && x + dx[i] < MAX_N) && (y + dy[i] >= 0 && y + dy[i] < MAX_N)) {

			if (doduziGul[x + dx[i]][y + dy[i]] == 1) {
				dfs(x + dx[i], y + dy[i]);
			}
		}
	}
	return;

}

int main(void)
{
	int test_case;
	int T;

	setbuf(stdout, NULL);

	freopen("input_두더지.txt", "r", stdin);
	scanf("%d", &T);

	int N;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &doduziGul[i][j]);
				printf("%d", doduziGul[i][j]);
			}
			printf("\n");
		}


		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {

				if (doduziGul[i][j] == 1) {
					dfs(i, j);
					doduziCount++;
					GulIndex++;
				}
			}
			printf("\n");
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d", doduziGul[i][j]);
			}
			printf("\n");
		}
	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
