#include "pch.h"
#include <iostream>
using namespace std;

#define MAX 10

typedef struct trie {
	bool end;
	struct trie * next[MAX];
} Node;

Node * newNode() {
	Node * node = (Node*)malloc(sizeof(Node));
	node->end = 0;
	
	for (int i = 0; i < MAX; i++) {
		node->next[i] = 0;
	}
	return node;
}

void insert(const char * key, Node * root) {

	int len = strlen(key);
	Node * now = root;
	for(int i = 0; i< len ; i++){
		if (!now->next[key[i] - '0']) {
			now->next[key[i] - '0'] = newNode();
		}
		now = now->next[key[i] - '0'];
	}
	now->end = 1;

	return;
}

void showAll(char* number, Node* now, int depth) {
	
	if (now->end) printf("%s\n", number);

	for (int i = 0; i < MAX; i++) {
		
		if (now->next[i]) {
			number[depth] = i + '0';
			number[depth + 1] = 0;
			showAll(number, now->next[i], depth + 1);
		}
	}
}



int main() {

	int tc = 0;
	scanf("%d", &tc);

	while (tc--) {
		int n;
		scanf("%d", &n);

		Node * root = newNode();

		while (n--) {
			char key[20];
			scanf("%s", key);
			insert(key,root);
		}

		char tmp[20];
		showAll(tmp, root, 0);

		cout << "asdfsdf" << endl;
	}

}