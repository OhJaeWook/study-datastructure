#include <iostream>
using namespace std;

#define MAX_N 15
#define MAX_CORE 15

int input[MAX_N][MAX_N] = { 0, };
int n = 0;

struct Core {
	int x;
	int y;
}a[MAX_CORE];
int ai;

Core * core[MAX_CORE];

void myalloc(int x, int y) {
	a[ai].x = x;
	a[ai].y = y;
}


int main(void)
{
	int test_case;
	int T;
	
	freopen("input.txt", "r", stdin);
	/* 아래 코드를 수행하지 않으면 여러분의 프로그램이 제한 시간 초과로 강제 종료 되었을 때,
	출력한 내용이 실제 표준 출력에 기록되지 않을 수 있습니다.
	따라서 안전을 위해 반드시 setbuf(stdout, NULL); 을 수행하시기 바랍니다.
	*/
	setbuf(stdout, NULL);
	scanf("%d", &T);
	/*
	여러 개의 테스트 케이스를 처리하기 위한 부분입니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++) {
			
			scanf("%d", input[i]);

		}


	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}