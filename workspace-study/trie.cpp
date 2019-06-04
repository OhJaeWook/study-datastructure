#include <iostream>
using namespace std;

#define MAX_NEXT 26
#define MAX_NODE 300000
#define INTEGER_OF_A 97
#define MAX_STRING 12
#define MAX_PREFIX 8
#define MAX_RESULT 5


struct trie {
	int end;
	int count;
	trie * next[MAX_NEXT];
}a[MAX_NODE];

int ai = 0;
trie * root;

struct ResultNode {
	int count;
	char resultWord[MAX_STRING];

	ResultNode * next;
	ResultNode * prev;
};

ResultNode * HEAD;
ResultNode * TAIL;
int resultNodeCount = 0;


trie * myalloc() {

	a[ai].end = 0;
	
	for(int i =0; i < MAX_NODE ; i++){
		a[ai].next[i] = nullptr;
	}

	trie * newnode = &a[ai];

	ai++;
	return newnode;

}


void init() {
	root = myalloc();
//	resultWord = (ResultNode*)malloc(5 * sizeof(ResultNode *));
	for (int i = 0; i < MAX_RESULT; i++) {
	//	resultWord[i].resultWord = "";
	}


}

void mystrcpy(char * src, char * dst) {

	while (*src) {
		*dst = *src;
		*dst++;
		*src++;
	}

	*dst = '\0';
}

void append(char *dst, char c) {
	char *p = dst;
	while (*p != '\0') p++; // 문자열 끝 탐색
	*p = c;
	*(p + 1) = '\0';
}

void appendn(char *dst, char c, int idx) {
	char *p = dst;
	while (idx--) p++; // 문자열 끝 탐색
	*p = c;
	*(p + 1) = '\0';
}


void mystrncpy(int idx, char *src, char* dst) {
	
	//dst에서 idx만큼 가고 src만큼 복사한다
	while (idx--) {
		*dst++;
	}

	while (*src) {
		*dst = *src;
		*dst++;
		*src++;
	}

	*dst = '\0';
}

int mystrlen(char * a) {
	int idx = 0;
	while (*a) {
		*a++;
		idx++;
	}
	return idx;
}

int mystrcmp(char * a, char* b) {

	while (*a++ == *b++) {

		if (*a == '\0' && *b == '\0') {
			return 0;
		}
	}
	return 1;
}



int mystrcmp2(char * a, char* b) {

	while (*a++ > *b++) {
		return 1;
	}
	return 0;
}

void showAll() {

	ResultNode *p = HEAD;

	for (ResultNode *p = HEAD; ; p = p->next) {

		printf("%s %d \n", p->resultWord, p->count);

		if (p == TAIL) {
			return;
		}

	}

}


void searchWord(char * word){

	trie * cur = root;

	while (*word) {
		cout << *word << endl;
		if (cur->next[*word - INTEGER_OF_A] == nullptr) {
			cur->next[*word - INTEGER_OF_A] = myalloc();
			
		}
		cur = cur->next[*word - INTEGER_OF_A];
		*word++;
	}

	cur->count++;
	cur->end = 1;
	cout << *word << endl;
}

int isPriorityHighLeft(char * p1, int p1_count, char* p2, int p2_count) {


	if (p1_count > p2_count)
		return 1;

	if (p1_count == p2_count) {
		
		while(*p1++ == *p2++) {

		}
		if (*p1 == '\0' || *p1 < *p2) {
			return 1;
		}

	}
	return 0;

}

void insert(char * word, int count) {

	ResultNode * n = (ResultNode *)malloc(sizeof(ResultNode));

	mystrcpy(word, n->resultWord);
	n->count = count;
	printf("%s %d \n", word, count);

	if (HEAD == nullptr && TAIL == nullptr) {
		HEAD = n;
		TAIL = n;
		resultNodeCount++;
		return;
	}

	int isInsert = 0;

	for (ResultNode *p = TAIL; ; p = p->prev) {
		if (isPriorityHighLeft(p->resultWord,p->count,n->resultWord,n->count)) {
			// p가 크면
			// 삽입
			if (resultNodeCount < 5 && p != TAIL) {
				n->prev= (p->next)->prev;
				(p->next)->prev = n;
				n->next = p->next;
				p->next = n;
				isInsert = 1;
				resultNodeCount++;
			}

			if (resultNodeCount < 5 && p == TAIL) {
				p->next = n;
				n->prev = p;
				TAIL = n;
				isInsert = 1;
				resultNodeCount++;
			}

		}
		else {
			if (p == HEAD) {
				p->prev = n;
				n->next = p;
				HEAD = n;

				isInsert = 1;
				resultNodeCount++;
			}
		}

		if (resultNodeCount > 5) {
			// 삭제

		}
		if (isInsert == 1)
			return;
	}

}


void dfs(trie * cur,char * currentResultWord, int idx) {

	// 실행되는 부분
	if (cur->end == 1) {
		
		printf("찾은 문자열 : %s \n", currentResultWord);

		insert(currentResultWord, cur->count);
	}
	
	// 반복 시킬 부분
	for (int i = 0; i < MAX_NEXT; i++) {

		if (cur->next[i] != nullptr) {
			
			char c = i + 'a';
			appendn(currentResultWord, c,idx);
			dfs(cur->next[i], currentResultWord, mystrlen(currentResultWord));
		}
	}
}



int autoComplete(char prefix[MAX_PREFIX + 1], char *retWord[MAX_RESULT] ) {
	
	// 1. prefix로 진행

	trie * cur = root;

	char cpyPrefix[MAX_PREFIX +1 ] = "";

	mystrcpy(prefix, cpyPrefix);
	printf("%s", cpyPrefix);

	while (*prefix) {

		if (cur->next[*prefix - INTEGER_OF_A] == nullptr) {
			return 0;
		}

		cur = cur->next[*prefix - INTEGER_OF_A];

		*prefix++;

	}
	
	dfs(cur, cpyPrefix,mystrlen(cpyPrefix));

	showAll();

	return resultNodeCount;
}


int main() {

	init();

	char  test[] = "abced";

	char test2[] = "15";

	cout << mystrcmp(test, test2)<< endl;

	cout << test << test2 << endl;

	//mystrcpy(test, test2);
	cout << test << endl;
	cout << test2 <<endl;


	char  testa1[] = "date";
	char  testa2[] = "data";
	char  testa3[] = "baa";
	char  testa4[] = "ccc";
	char  testa5[] = "ab";
	char  testa6[] = "abc";
	char  testa7[] = "ze";
	char  testa8[] = "zebb";
	char  testa9[] = "zea";

	char testz[7][MAX_STRING] = { "data","date","bnb","env","datb","datc","datc" };
	/*
	searchWord(testa1);
	searchWord(testa2);
	searchWord(testa3);
	*/
	for (int i = 0; i < 7; i++) {
		searchWord(testz[i]);
	}
	/*
	searchWord(testa4);
	searchWord(testa5);
	searchWord(testa6);
	searchWord(testa7);
	searchWord(testa8);
	searchWord(testa9);
	*/

	//  위에꺼까지 해서 확인

	//isPriorityHighLeft(testa5, 1, testa4,1 );

	char searchWord[] = "da";

	char *retWord[MAX_RESULT];

	for (int i = 0; i < MAX_RESULT; i++) {

		retWord[i] =(char *) malloc(MAX_STRING * sizeof(char*));

	}

	cout << autoComplete(searchWord, retWord);


}
