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
	/* �Ʒ� �ڵ带 �������� ������ �������� ���α׷��� ���� �ð� �ʰ��� ���� ���� �Ǿ��� ��,
	����� ������ ���� ǥ�� ��¿� ��ϵ��� ���� �� �ֽ��ϴ�.
	���� ������ ���� �ݵ�� setbuf(stdout, NULL); �� �����Ͻñ� �ٶ��ϴ�.
	*/
	setbuf(stdout, NULL);
	scanf("%d", &T);
	/*
	���� ���� �׽�Ʈ ���̽��� ó���ϱ� ���� �κ��Դϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++) {
			
			scanf("%d", input[i]);

		}


	}
	return 0; //��������� �ݵ�� 0�� �����ؾ� �մϴ�.
}