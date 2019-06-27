
/*

Map�� �־��� ���� 100 x 100
������ ������, ������ ������, ���� ID�� ���������� ���� 5�� ���ض�
������ ������ ����, ������ ������ ���� ID�� ���� ��
MAP�� Y,X 2�����迭

1. void Init(int Map_size)

2. void AddHouse(int bid, int price, int rating, int y, int x)

3. int reserve(int bid, int cday, int night)
- ���޹��� ���Ұ� ������ �������� �Ǵ��ϴ� �Լ�
- üũ�� ��¥�� ���� ������ ����ŭ���� ������ ������ �����ϰ� return 1
- ���� �Ϸ�� ������ ������ 0

4. int cancel(int bid, int cday)
- ��Ҵ� cday���� ���� 3~6�� ���Ұ� ������ִٷ��� 3�Ͽ��� ������ ��Ұ��� 4�Ͽ� ��Ұ� ������ return 0
- ��� �����ϸ� ����� ������ ����ϰ� return 1
- ��Ұ� �Ұ��� �ϸ� return 0

5. int seach(int opt, int cday, int night, int y, int x, int top[5])
- opt == 0�̸�  �ش� y,x����
- opt == 1�̸� ��� ���� 1ĭ�� �˻� ���� ��� (1,1)�� �ɼ� 0�̸� (0,0)~(2,2)
- �ش� ������ ������ ������ ������ �����̸� ���� �켱������ ���� top5 ��ȯ
- ���������� �߰��� ������ŭ return , ex) 2�� �ۿ� ������ return 2
- int answer[5]���٤Ӱ� ���� ID�� ������� ����

*/

// testcase ������ ��Ȱ���ϴ� ��

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

