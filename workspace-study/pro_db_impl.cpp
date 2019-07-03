
typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// 5개에 해당하는 해쉬를 가지고 있고
// 변경 될때 그 모든 해쉬를 다 변경해줌
// 삭제 될때도 마찬가지

#define MAX_PRO_SIZE 20
#define MAX_PRO_COUNT 5
#define MAX_RECORD 50000

struct Node {

	char field[MAX_PRO_COUNT][MAX_PRO_SIZE];
	
	Node * next[MAX_PRO_COUNT];
	Node * prev[MAX_PRO_COUNT];

}a[MAX_RECORD];
int ai = 0;

void mystrcpy(char * src, char * dst) {

	while (*src) {
		*dst = *src;
		*src++;
		*dst++;
	}

	*dst = '\0';
}

int mystrcmp(char * a, char *b) {

	while (*a++ == *b++) {
		if (*a == '\0' && *b == '\0') {
			return 0;
		}
	}
	return 1;

}

Node * myalloc(char* name, char* number, char* birthday, char* email, char* memo) {
	
	mystrcpy(name, a[ai].field[NAME]);
	mystrcpy(number, a[ai].field[NUMBER]);
	mystrcpy(birthday, a[ai].field[BIRTHDAY]);
	mystrcpy(email, a[ai].field[EMAIL]);
	mystrcpy(memo, a[ai].field[MEMO]);

	for (int i = 0; i < 5; i++) {
		a[ai].next[i] = nullptr;
		a[ai].prev[i] = nullptr;
	}

	return &a[ai++];
}

// record 갯수 : 50,000


#define MAX_TABLE 10

unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

Node * HEAD[MAX_PRO_COUNT][MAX_TABLE];

void hAdd(FIELD field, const char * str, Node * p) {
	
	int k = hash(str);

	p->next[field] = HEAD[field][k];
	
	if (HEAD[field][k] != nullptr) {

		*HEAD[field][k]->prev = p;
	}


	HEAD[field][k] = p;

	// p->prev[field] = nullptr;

}

void hDelete(FIELD field, char * str) {

	int k = hash(str);

	Node *cur = HEAD[field][k];

	
	if (mystrcmp(cur->field[field], str)) {





	}
	// p->prev[field] = nullptr;

}



void InitDB()
{

}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	Node * p = myalloc(name, number, birthday, email, memo);

	hAdd(NAME, p->field[NAME], p);
	hAdd(NUMBER, p->field[NUMBER], p);
	hAdd(BIRTHDAY, p->field[BIRTHDAY], p);
	hAdd(EMAIL, p->field[EMAIL], p);
	hAdd(MEMO, p->field[MEMO], p);
	

}

int Delete(FIELD field, char* str)
{
	// 다 지워버리는거임
	
	return -1;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	return -1;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = -1;

	return result;
}


int main() {

	char fieldTest1[MAX_PRO_COUNT][MAX_PRO_SIZE] = { "ohjewook","01084142234","891003","jewook89@nate.com","오재욱" };
	char fieldTest3[MAX_PRO_COUNT][MAX_PRO_SIZE] = { "ohjewook","01084142234","891003","jewook89@nate.com","오재욱" };
	char fieldTest2[MAX_PRO_COUNT][MAX_PRO_SIZE] = { "leeyeonkyung","01090204521","890621","yk2020@nate.com","이연경" };

	Add(fieldTest1[NAME], fieldTest1[NUMBER], fieldTest1[BIRTHDAY], fieldTest1[EMAIL], fieldTest1[MEMO]);
	Add(fieldTest2[NAME], fieldTest2[NUMBER], fieldTest2[BIRTHDAY], fieldTest2[EMAIL], fieldTest2[MEMO]);
	Add(fieldTest3[NAME], fieldTest3[NUMBER], fieldTest3[BIRTHDAY], fieldTest3[EMAIL], fieldTest3[MEMO]);

	char deleted[] = "ohjawook";
	Delete(NAME, deleted);


}