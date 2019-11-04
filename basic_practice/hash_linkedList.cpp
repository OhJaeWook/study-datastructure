#include <iostream>
using namespace std;

// Hash + linked list

#define MAX_TABLE 4000
void mstrcpy(char * dst, char * src) {
	while(*src) {
		*dst++=*src++;
	}
	*dst = '\0';
}

int mstrcmp(char * a, char * b) {
	while(*a) {
		if(*a != *b) return 1;
		*a++;*b++;
	}
	if(*a != *b) return 1;
	return 0;
}


struct HashNode {
	char key[10];
	int userId;
	int index = -1;
	HashNode * next;
} hashNodes[10000];
int ni = 0;

HashNode *ht[MAX_TABLE];

HashNode * myAlloc(char *key, int userId) {

	HashNode * newNode = &hashNodes[ni];

	newNode->userId = userId;
	newNode->index = ni;
	mstrcpy(newNode->key, key);
	ni++;
	return newNode;
}


unsigned long hashf(const char *str) {
	unsigned long hash = 5381;
	int c;

	while(c = *str++) {
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}



void add(char *key, int userId) {

	unsigned long h = hashf(key);

	HashNode * start = ht[h];

	HashNode * newNode = myAlloc(key, userId);

	if(start == 0) {
		
		ht[h] = newNode;
		/*
		start->index = newNode->index;
		start->userId = newNode->userId;
		mstrcpy(start->key, newNode->key);
		*/
		return;
	}

	newNode->next = start->next;
	start->next = newNode;

}

void find(char *key, int userId) {

	unsigned long h = hashf(key);

	HashNode * cur = ht[h];

	while(1) {
		if(cur == 0)
			break;


		if((!mstrcmp(cur->key, key)) && (cur->userId == userId)) {

			cout << "key : " << cur->key << " userId : " << cur->userId <<endl;
			return;
		}

		cur = cur->next;
	}

	cout << "Not found"<<endl;
}

// hashTable 은 메모리를 가지고 있는게 구현하기 편한줄 알았는데 전혀 아니다.
// 메모리가 중복으로 되고 구현도 지저분해진다.
// hashTable 은 포인터로 해서 가지고 있고 Node를 다들 정적메모리할당시켜 한개씩 연결하면 끝

int main() {

	char test[10] = "jewook";
	char test1[10] = "jewook1";

	add(test, 1);
	add(test, 2);
	add(test, 3);
	add(test, 4);

	find(test, 1);
	find(test, 10);
	find(test1, 1);


}



