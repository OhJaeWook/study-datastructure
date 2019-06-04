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


typedef struct NODE
{
	char name[19]="";
	char number[19]="";
	char birthday[19]="";
	char email[19]="";
	char memo[19]="";
}Node;

#define MAX_RECORD 50000

Node DB[MAX_RECORD];



void log(const char * str) {
	cout << str << endl;
}


void InitDB()
{
	log("initDB");
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	log("Add");
}

int Delete(FIELD field, char* str)
{
	log("Delete");
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