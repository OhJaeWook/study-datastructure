#include <stdio.h>
#include <malloc.h>

#define MAX 200000
#define NULL 0

struct ID {
	int  id;
	ID * next;
};

struct Person {
	int L;
	int R;
};

ID * priority[MAX];
Person person[MAX];
int visitedChair[MAX];



void insertPriority(int availableChairCount, int id ) {

	ID * n = (ID *)malloc( sizeof(ID));
	
	n->id = id;
	n->next = NULL;
	
	
	if (priority[availableChairCount] == NULL) {

		priority[availableChairCount] = n;
		return;
		
	}

	n->next = priority[availableChairCount];

	priority[availableChairCount] = n;

}

int calculateAvailableChair(int L, int R, int M) {
	return L + (M - R) + 1;
}

void setChairAsPriority(int pri) {
	
	


}



int main(void)
{
	int test_case;
	int T;
	
	setbuf(stdout, NULL);
	freopen("input_[H1907] 의자 제공하기.txt", "r", stdin);
	scanf("%d", &T);
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N, M;
		scanf("%d %d", &N, &M);

		// init()

		for (int i = 0; i < N; i++) {
			int L, R;
			scanf("%d %d", &L, &R);

			person[i].L = L;
			person[i].R = R;

			// 가능한 자리수를 구한다음에 priority에 id를 넣어준다
			int CountAvailableChair = calculateAvailableChair(L, R, M);

			insertPriority(CountAvailableChair, i);

		}

		for (int i = 1; i <= M; i++) {



		}

	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}