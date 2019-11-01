#include <iostream>
using namespace std;

#define MAX_DIR 10000

struct Dir {
	int index;
	int parentIndex;
	char name[7];
	Dir * next;
	Dir * prev;
	Dir * childList;
}dir[MAX_DIR];

int dirIndex = 0;

int mstrcpy(char dst[], char src[]) {

	while (*src) {
		*dst++ = *src++;
	}
	*dst = '\0';

	return 0;
}

Dir * myAlloc(char name[]) {

	mstrcpy(dir[dirIndex].name, name);
	dir[dirIndex].index = dirIndex;
	dir[dirIndex].next = 0;
	dir[dirIndex].childList = 0;

	return &dir[dirIndex++];
}

// a가 b보다 사전순서상 우선순위가 높다면 true
bool cmp(char a[], char b[]) {

	while (1) {

		// a가 b보다 짧다
		if (*a == 0 && *b != 0) {
			return true;
		}
		// a가 b보다 길다
		else if (*a != 0 && *b == 0) {
			return false;
		}

		if (*a == *b) {

		}
		else if (*a < *b) {
			return true;
		}
		else if (*a > *b) {
			return false;
		}

		*a++;
		*b++;

	}

}

void add(Dir* parentDir, Dir * newDir) {

	newDir->parentIndex = parentDir->index;

	if (parentDir->childList == 0) {

		parentDir->childList = newDir;
		return;
	}

	Dir * prev = parentDir->childList;
	Dir * cur = parentDir->childList;


	while (1) {

		// cur이 없으면 바로 넣음
			if (cur == 0) {
				prev->next = newDir;
				newDir->prev = prev;

			break;
		}

		// 새로운 dir의 이름이 현재 dir의 이름보다 우선순위가 높다면
		if (cmp(newDir->name, cur->name)) {

			// 첫번째보다 우선순위가 높은경우
			if (cur == prev) {

				newDir->next = prev;
				prev->prev = newDir;
				
				parentDir->childList = newDir;

				break;
			}
			// 이외의 경우
			else {

				// 새로운 
				newDir->next = cur;
				newDir->prev = prev;
				prev->next = newDir;
				cur->prev = newDir;

				break;
			}
		}

		prev = cur;
		cur = cur->next;
	}
}


void printList(Dir * p) {

	Dir * cur = p->childList;
	while (1) {

		if (cur == 0) {
			break;
		}
		cout << cur->name;

		if (cur->next != 0)
			cout << "->";

		cur = cur->next;
	}
	cout << endl;
}

// testCode
void printListMore(Dir * p) {

	Dir * cur = p->childList;
	while (1) {

		if (cur == 0) {
			break;
		}
		cout << cur->name;

		char prevString[10];
		char nextString[10];


		cout << " [ prev ] : ";
			
		if (cur->prev == 0) {
			cout << "NULL";
		}
		else {
			cout << cur->prev->name;
		}

		cout << " [ next ] : "; 
		if (cur->next == 0) {
			cout << "NULL";
		}
		else {
			cout << cur->next->name;
		}
		cout << endl;
		if (cur->next != 0)
			cout << "->";

		cur = cur->next;
	}
	cout << endl;
}


int main() {

	char testString1[10] = "a";
	char testString2[10] = "bee";
	char testString3[10] = "aac";
	char testString4[10] = "cddd";

	char rootString[5] = "/";

	Dir * root = myAlloc(rootString);

	Dir *newDir1 = myAlloc(testString1);
	Dir *newDir2 = myAlloc(testString2);
	Dir *newDir3 = myAlloc(testString3);
	Dir *newDir4 = myAlloc(testString4);

	add(root, newDir1);
	printList(root);
	add(root, newDir2);
	printList(root);
	add(root, newDir3);
	printList(root);
	add(root, newDir4);

	printList(root);
	printListMore(root);

	cout << "check :" << cmp(testString1, testString3) << endl;
	cout << "check :" << cmp(testString3, testString4) << endl;


	return 1;
}
