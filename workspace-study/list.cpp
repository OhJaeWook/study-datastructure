#define NULL 0

#include <malloc.h>
#include <stdio.h>

struct ID {
	int id;
	ID * next;
};

ID * HEAD = NULL;

void insert(int id) {

	ID * n = (ID *)malloc(sizeof(ID));
	n->id = id;
	n->next = NULL;

	if (HEAD == NULL) {

		HEAD = n;
	}
	else {

		n->next = HEAD;
		HEAD = n;
	}
}

void remove(int id) {

	ID * cur = HEAD;
	ID * pp = HEAD;

	if (HEAD->id == id) {
		HEAD = cur->next;
		return;
	}

	while (cur->id != id) {
		pp = cur;
		cur = cur->next;
	}

	pp->next = cur->next;

}


void showAll() {

	ID * cur = HEAD;

	while (cur != NULL) {
		printf("%d -> ", cur->id);
		cur = cur->next;
	}
	printf("NULL \n");
}

void init() {

	HEAD = NULL;

}

int main() {
	
	init();
	insert(10);
	insert(11);
	insert(12);
	insert(13);
	showAll();
	remove(12);
	showAll();

}

