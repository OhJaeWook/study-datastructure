
/*

Map에 주어진 숙소 100 x 100
가격이 낮은순, 평점이 높은순, 숙소 ID가 높은순으로 최종 5를 구해라
가격이 같으면 평점, 평점이 같으면 숙소 ID가 높은 순
MAP은 Y,X 2차원배열

1. void Init(int Map_size)

2. void AddHouse(int bid, int price, int rating, int y, int x)

3. int reserve(int bid, int cday, int night)
- 전달받은 숙소가 예약이 가능한지 판단하는 함수
- 체크인 날짜로 부터 숙박일 수만큼까지 예약이 없으면 예약하고 return 1
- 만약 하루라도 예약이 있으면 0

4. int cancel(int bid, int cday)
- 취소는 cday에만 가능 3~6일 숙소가 예약되있다러도 3일에만 예약이 취소가능 4일에 취소가 들어오면 return 0
- 취소 가능하면 예약된 일정을 취소하고 return 1
- 취소가 불가능 하면 return 0

5. int seach(int opt, int cday, int night, int y, int x, int top[5])
- opt == 0이면  해당 y,x에만
- opt == 1이면 모든 방향 1칸을 검색 예를 들어 (1,1)에 옵션 0이면 (0,0)~(2,2)
- 해당 지역의 숙소중 예약이 가능한 숙소이며 위에 우선순위에 따라 top5 반환
- 최종적으로 발견한 갯수만큼 return , ex) 2개 밖에 없으면 return 2
- int answer[5]에다ㅣ가 숙소 ID를 순서대로 삽입

*/

// testcase 끝난뒤 재활용하는 법

#include <iostream>
using namespace std;
#define MAX_M 101
#define MAX_HOUSE 40001
#define MAX_SCHEDULE 100

struct Node {
	int price = 0;
	int rating = 0;
	int next = 0;
	int sch[MAX_SCHEDULE];
	bool isVisited = false;

}a[MAX_HOUSE];

int map[MAX_M][MAX_M];

int map_size = 0;

void Init(int Map_size) {

	map_size = Map_size;

	for (int i = 0; i < MAX_HOUSE; i++) {
		a[i].next = 0;
		a[i].rating = 0;
		a[i].price = 0;

		for(int  j = 0; j < MAX_SCHEDULE ;j++){
			a[i].sch[j] = 0;
		}
	}

	for (int i = 0; i <= Map_size; i++) {
		for (int j = 0; j <= Map_size; j++) {
			map[i][j] = 0;
		}
	}

}

bool isPriorityHigh(int target, int source) {

	if (a[target].price > a[source].price) {
		return true;
	}
	else if ((a[target].price == a[source].price)
		&& (a[target].rating < a[source].rating)) {
		return true;
	}
	else if ((a[target].price == a[source].price)
		&& (a[target].rating == a[source].rating)
		&& (target < source)) {
		return true;
	}

	return false;
}



void insertAsPriority(int bid, int y, int x) {

	// 처음이면 HEAD에 연결하고 RETURN
	if (map[y][x] == 0) {
		map[y][x] = bid;
		return;
	}

	// 아니면 prev를 저장하고 prev와 연결해준다
	int start = map[y][x];
	int prev = start;
	int pprev;


	while(1){

		if (isPriorityHigh(prev, bid)) {
			break;
		}
		
		if (a[prev].next == 0) {
			a[prev].next = bid;
			return;
		}
		pprev = prev;
		prev = a[prev].next;
	}

	if (prev == start) {
		map[y][x] = bid;
	}
	else {
		a[pprev].next = bid;
	}

	a[bid].next = prev;

	return;
}

void AddHouse(int bid, int price, int rating, int y, int x) {

	a[bid].price = price;
	a[bid].rating = rating;
	
	insertAsPriority(bid, y, x);

}
void testPrint(int y, int x) {

	int c = map[y][x];

	while (c != 0) {
		printf("[bid :%d , price : %d , rating %d ] -> ",c, a[c].price, a[c].rating);
		c = a[c].next;
		printf("\n");
	}
	printf("END");

}


int reserve(int bid, int cday, int night) {

	for (int i = cday; i < cday + night; i++) {
		if (a[bid].sch[i] != 0) {
			return 0;
		}
	}

	a[bid].sch[cday] = 1;

	for (int i = cday + 1 ; i <= cday + night; i++) {
		a[bid].sch[i] = 2;
	}

	return 1;
}

int cancel(int bid, int cday) {

	if (a[bid].sch[cday] == 1) {

		int i = cday;

		while(a[bid].sch[i] == 2){
			a[bid].sch[cday] = 0;
			i++;
		}
		return 1;
	}

	return 0;
}

int isAvailable(int cday, int night, int bid) {

	for (int i = cday; i < cday + night; i++) {
		if (a[bid].sch[i] != 0) {
			return 0;
		}
	}

	return 1;
}

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}

// 최소힙이다.
int heapPush(int value)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("꽉 찼어요!");
		return 0;
	}

	// 맨마지막에 삽입
	heap[heapSize] = value;

	int current = heapSize;

	// 비어있지않고 맨마지막 보다 부모의 크기가 크다면
	while (current > 0 && isPriorityHigh(heap[(current - 1) / 2], heap[current]))
	{
		// 바꿔준다
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

int heapPop(int *value)
{
	// size가 0보다 작으면
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0];
	heapSize = heapSize - 1;

	// 제일 마지막에 있는 애를 제일 위로 올린다.
	heap[0] = heap[heapSize];

	int current = 0;

	// 왼쪽 자식으로 확인시 전체 힙사이즈를 넘어가지 않는선에서 계속 진행한다.
	while (current * 2 + 1 < heapSize)
	{
		int child;

		// 오른쪽 자식이 힙사이즈와 같다면 없는거니까 왼쪽에로 하고
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = isPriorityHigh(heap[current * 2 + 2], heap[current * 2 + 1]) ? current * 2 + 1 : current * 2 + 2;
		}


		// 만약에 자식노드보다 내 우선순위가 높은순간 그만둔다
		if (isPriorityHigh(heap[child], heap[current]))
		{
			break;
		}

		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
	return 1;
}

int search(int opt, int cday, int night, int y, int x, int top[5]) {
	int count = 0;

	if (opt == 0) {
		
		int current = map[y][x];

		while (current != 0) {

			if(isAvailable(cday, night, current)){
				top[count] = current;
				count++;
			}
			current = a[current].next;
		}

	}
	else if(opt == 1) {
		
		int min_y = y - 1 < 0 ? 0 : y - 1;
		int min_x = x - 1 < 0 ? 0 : x - 1;

		int max_y = y + 1 > map_size ? map_size : y + 1;
		int max_x = x + 1 > map_size ? map_size : x + 1;

		int mostPickBid = 0;
		
		for (int i = min_y; i <= max_y; i++) {
			for (int j = min_x; j <= max_x; j++) {

				if (map[i][j] !=0 && isAvailable(cday, night ,map[i][j])) {
					heapPush(map[i][j]);
				}
			}
		}

		while (1) {
			if (heapSize == 0 || count == 5) {
				break;
			}


			int value;

			heapPop(&value);

			top[count] = value;
			count++;

			if (a[value].next != 0) {
				heapPush(a[value].next);
			}
			
		}
	}

	return count;
}








int main() {

	Init(3);
	
	AddHouse(1, 100, 3, 1, 1);
	AddHouse(2, 300, 3, 1, 1);
	AddHouse(3, 400, 3, 1, 1);
	AddHouse(4, 100, 5, 1, 1);
	AddHouse(5, 100, 4, 1, 1);


	AddHouse(6, 300, 3, 2, 2);
	AddHouse(7, 50, 5, 2, 2);/*
	AddHouse(8, 500, 3, 2, 2);*/

	AddHouse(9, 500, 5, 3, 3);
	AddHouse(10, 200, 4, 3, 3);



	testPrint(1, 1);
	
	printf("%d \n", reserve(2, 2, 3));
	printf("%d \n", reserve(2, 3, 4));
	printf("%d \n", reserve(2, 6, 1));
	

	printf("%d \n", cancel(2, 2));
	printf("%d \n", cancel(2, 5));
	printf("%d \n", cancel(2, 6));
	/*
	heapPush(1);
	heapPush(2);
	heapPush(3);
	heapPush(4);
	heapPush(5);

	int value;

	heapPop(&value);
	cout << value << endl;
	heapPop(&value);
	cout << value << endl;
	heapPop(&value);

	if (a[value].next != 0) {
		heapPush(a[value].next);
	}

	cout << value << endl;
	heapPop(&value);
	cout << value << endl;
	heapPop(&value);
	cout << value << endl;

	*/
	/*
	int top[5];

	int result = search(0, 4, 7, 1, 1, top);

	for (int i = 0; i < result; i++) {
		cout << top[i] << " " ;
	}
	cout << " result :" << result << endl;
	*/


	int top[5];

	int result = search(1, 4, 7, 3, 3, top);

	for (int i = 0; i < result; i++) {
		cout << top[i] << " ";
	}
	cout << " result :" << result << endl;

}



