#include "pch.h"
#include <iostream>
using namespace std;

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

typedef struct data
{
	char name[19] = "";
	char number[19] = "";
	char birthday[19] = "";
	char email[19] = "";
	char memo[19] = "";
}Data;

typedef struct node
{
	struct data data;
	struct node * prev = 0;
}Node;



#define MAX_RECORD 50000
#define MAX_FIELD 5

Node * DB[MAX_FIELD][MAX_RECORD];

void log(const char * str) {
	cout << str << endl;
}


unsigned long hashFunction(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_RECORD;
	}

	return hash % MAX_RECORD;
}


void hAdd(FIELD field, int hKey, Data * data) {
	
	Node* p = (Node *) malloc(sizeof(Node));

	memcpy(&(p->data) ,data, sizeof(Data));
	

	p->prev = DB[field][hKey];
	
	DB[field][hKey] = p;

}

int hFind(FIELD field, int hKey, Data * data) {


	

	
}


void InitDB()
{
	log("initDB");
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{	
	log("Add");
	int hashValue[MAX_FIELD] = { 0, };

	hashValue[NAME] = hashFunction(name);
	hashValue[NUMBER] = hashFunction(number);
	hashValue[BIRTHDAY] = hashFunction(birthday);
	hashValue[EMAIL] = hashFunction(email);
	hashValue[MEMO] = hashFunction(memo);

	Data * data = (Data *)malloc(sizeof(Data));
	strcpy(data->name, name);
	strcpy(data->number, number);
	strcpy(data->birthday, birthday);
	strcpy(data->email, email);
	strcpy(data->memo, memo);


	hAdd(NAME, hashValue[NAME], data);
	hAdd(NUMBER, hashValue[NUMBER], data);
	hAdd(BIRTHDAY, hashValue[BIRTHDAY], data);
	hAdd(EMAIL, hashValue[EMAIL], data);
	hAdd(MEMO, hashValue[MEMO], data);

}

int Delete(FIELD field, char* str)
{
	log("Delete");

	hFind()






	return -1;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{	

	log("Change");

	return -1;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = -1;

	return result;
}



int main()
{
	
	char name[] = "asdf";
	char number[] = "1023";
	char birthday[] ="12333" ;
	char email[] = "jewook89@nate.com";
	char memo[] = "jewook";
	Add(name, number, birthday, email, memo);
	Add(name, number, birthday, email, memo);



	return 0;
}