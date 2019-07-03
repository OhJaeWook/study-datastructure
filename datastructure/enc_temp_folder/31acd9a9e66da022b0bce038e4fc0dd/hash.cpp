#include "pch.h"
#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX_TABLE 20

typedef struct node{
	char value[7];
	struct node * prev = 0;
}Node;

Node a[20000];

int arrCount = 0;

Node* myalloc() {
	return &a[arrCount++];
}


Node* hTable[MAX_TABLE];

unsigned int myhash(const char * keyString) {

	int hSalt = 123;

	int len = strlen(keyString);

	for (int i = 0; i < len; i++) {
		hSalt += keyString[i] + i ^ i;
	}

	return (hSalt) % MAX_TABLE;

}

void insert(char * keyString) {
	Node* p = myalloc();

	strncpy(p->value ,keyString,8);

	int key = myhash(p->value);

	p->prev = hTable[key];

	hTable[key] = p;
}

int isExist(const char * keyString) {

	int key = myhash(keyString);

	for (Node * pp = hTable[key]; pp != NULL; pp = pp->prev) {

		if (!strncmp(pp->value, keyString, 7)) {
			cout << "found" << endl;
			return 1;
		}
	}
	cout << "no found"<<endl;
	return 0;
}


int main(void) {

	char keyString[] = "police1";
	
	insert(keyString);
	
	char keyString2[] = "ironman";

	insert(keyString2);

	isExist("police1");
	isExist("policer");
	isExist("ironman");

	system("pause");
}

