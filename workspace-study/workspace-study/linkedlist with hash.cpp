#include "pch.h"
#include <iostream>
using namespace std;

#define MAX_TABLE 100000
#define LEN 32

struct node {
	node * prev;
	char key[LEN + 1];
	char value[LEN + 1];
}a[MAX_TABLE + 5];

node * ht[MAX_TABLE];
int ai;

inline int mystrcmp(char * a, char* b) {
	while (*a++ == *b++) {
		if (*a == '\0' && *b == '\0') {
			return 0;
		}
	}
	return 1;
}


inline void mystrcpy(char * dst, char* src) {

	while (*src) {
		*dst++ = *src;
		*src++;
	}
	*dst = '\0';

}
node * myalloc(char * key, char * value) {

	mystrcpy(a[ai].key, key);
	mystrcpy(a[ai].value, value);
	a[ai].prev = nullptr;

	return &a[ai++];
}



unsigned int myhash(char * str) {

	int h = 0;
	while (*str) {
		cout << (*str);
		h +=(*str++);
	}

	return h % MAX_TABLE;
}

void insert(char * key, char * value) {

	int k = myhash(key);

	node *p = myalloc(key, value);

	p->prev = ht[k];

	ht[k] = p;

}

int get(char * key, char * value) {

	int k = myhash(key);
	int count =0 ;
	for (node * p = ht[k]; p != nullptr; p = p->prev) {
		if (mystrcmp(p->key, key) == 0) {
			mystrcpy(value, p->value);
			count++;
		}
	}
	return count;
}

int del(char * key) {
	
	int k = myhash(key);

	node ** pp = &ht[k];
	int count = 0;
	for (node *p = ht[k]; p != nullptr; p = p->prev) {
		if (mystrcmp(p->key, key) == 0) {
			(*pp) = p->prev;

			count++;
		}
		else {
			pp = &p->prev;
		}
	}

	return count;
}



int main() {

	char  dst[] = "12";
	char  src[] = "vjd";

	mystrcpy(dst, src);

	cout << dst << endl;
	cout << src << endl;


	char key[] = "asdfsadf";
	char value[] = "100";

	insert(key, value);
	insert(key, value);

	char skey[] = "asdfsadf";
	char svalue[] = "";
	int scount = get(skey, svalue);
	cout << scount << endl;
	cout << svalue << endl;


	int dcount = del(skey);
	int scount1 = get(skey, svalue);

}