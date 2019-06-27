
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

#include <stdio.h>
#define MAX_M 101
#define MAX_HOUSE 40001
#define MAX_SCHEDULE 100
struct Node {
	int price;
	int rating;
	int next;
	int sch[MAX_SCHEDULE];
	bool isExist;
}a[MAX_HOUSE];

int map[MAX_M][MAX_M];


void Init(int Map_size) {
	for (int i = 0; i < MAX_HOUSE; i++) {
		a[i].next = 0;
		a[i].rating = 0;
		a[i].price = 0;
		a[i].isExist = false;
	}
}

void insertAsPriority(int bid, int y, int x) {


	if (map[y][x] == 0) {
		map[y][x] = bid;
		return;
	}

	int start = map[y][x];
	int prev = start;


	while(1){

		if (a[prev].price > a[bid].price) {
			break;
		}
		else if((a[prev].price == a[bid].price)
			&&(a[prev].rating < a[bid].rating) ){
			break;
		}
		else if ((a[prev].price == a[bid].price)
			&& (a[prev].rating == a[bid].rating)
			&& (prev < bid)) {
			break;
		}


		if (a[prev].next == 0) {
			a[prev].next = bid;
			return;
		}
		
		prev = a[prev].next;
	}

	a[bid].next = prev;
	
	if (prev == start) {
		map[y][x] = bid;
	}

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
	}
	printf("END");

}


int reserve(int bid, int cday, int night) {

	return 1;
}

int cancel(int bid, int cday) {

	return 1;
}

int seach(int opt, int cday, int night, int y, int x, int top[5]) {

	return 1;
}

int main() {
	AddHouse(10, 100, 3, 1, 1);
	AddHouse(11, 300, 3, 1, 1);
	AddHouse(12, 400, 3, 1, 1);
	AddHouse(13, 100, 5, 1, 1);

	testPrint(1, 1);

}

