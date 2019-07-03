#include <iostream>

#define MAX_DATA 5
struct Node {
	char data[MAX_DATA];
	Node * next;
	Node * prev;
};

void mystrcpy(char * src, char * dst) {

	while (*src) {
		*dst = *src;
		*dst++;
		*src++;
	}

	*dst = '\0';
}

Node * HEAD;

Node * TAIL;

void insert(int isFrontInsert, char * data) {

	Node* n = (Node*)malloc(sizeof(Node));

	mystrcpy(data, n->data);

	if (HEAD == nullptr && TAIL == nullptr) {
		HEAD = n;
		TAIL = n;
	}

	if (isFrontInsert == 1) {

		n->next = HEAD;
		(*HEAD).prev = n;
		HEAD = n;
	}

	if (isFrontInsert == 0) {

		(*TAIL).next = n;
		n->prev = TAIL;
		TAIL = n;
		
	}
}

void printFront() {
	printf("print from front--------------\n");
	int count = 0;
	for(Node * p = HEAD ; ; p = p->next)
	{
		printf("%d 번째 : ",count++);
		printf("%s \n", p->data);

		if (p == TAIL)
			return;
	}

}

void printBack() {

	printf("print from back--------------\n");
	int count = 0;
	for (Node * p = TAIL; ; p = p->prev)
	{
		printf("%d 번째 : ", count++);
		printf("%s \n", p->data);

		if (p == HEAD)
			return;
	}

}

int main() {

	char data[4][5] = { "test","sss","vvv","bbbb"};
	insert(1, data[0]);

	insert(1, data[1]);

	insert(0, data[2]);

	insert(0, data[3]);

	printFront();

	printBack();

}