# SNS191022

#include <iostream>
using namespace std;


#define MAX_USER      1000
#define MAX_TAG       5000



int mstrcmp(const char *a, const char *b)
{
int i;
for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
return a[i] - b[i];
}

void mstrcpy(char *dest, const char *src)
{
int i = 0;
while (src[i] != '\0') { dest[i] = src[i]; i++; }
dest[i] = src[i];
}


#define MAX_MSG 1000001
#define MAX_TABLE 10001

struct Msg {
	int userId;
	int timestamp;
	Msg *next;
} msg[MAX_MSG];


struct User {	
	int followings[MAX_USER];
	int fidx;
	int msg[6];
	int midx;
} user[MAX_USER];


struct HashNode {
	int key;	// 문자열을 key(int)로 변환하는 방법 익히기
	char keyStr[10];
	int data;	// msgId로 사용
	HashNode *next;
} hashNode[MAX_MSG];
int hidx = 0;


HashNode hashTable[MAX_TABLE];

void init(){

	hidx = 0;
	for (int i = 0; i < MAX_MSG; i++) {

		if(i < MAX_USER) {
			user[i].fidx = 0;
			user[i].midx = 0;

			for (int j = 0; j < MAX_USER; j++) {
				user[i].msg[j] = 0;
			}

			for (int j = 0; j < 6; j++) {
				user[i].msg[j] = 0 ;
			}
		}

		if (i < MAX_TABLE){
			hashTable[i].key = -1;
			hashTable[i].data = -1;
			hashTable[i].next = 0;
		}

		hashNode[i].data = 0;
		hashNode[i].key = 0;
		hashNode[i].next = 0;

		msg[i].userId = 0;
		msg[i].timestamp = 0;
		msg[i].next = 0;
	}

}

// msgID1이 msgID2보다 우선순위가 높으면 true
bool cmp(int msgID1, int msgID2) {

	if (msg[msgID1].timestamp > msg[msgID2].timestamp) {
		return true;
	} else if (msg[msgID1].timestamp == msg[msgID2].timestamp && msg[msgID1].userId < msg[msgID2].userId) {
		return true;
	}

	return false;
}


// heap 소트를 배워야지 더 빠르다?
// 6개를 넣어서 5개를 뽑자
void insertionSort( int count, int arr[])
{
	int temp;
	int i;
	int j;

	for (i = 1; i < count; i++)
	{
		temp = arr[i];
		j = i - 1;

		while ((j >= 0) && cmp(temp,arr[j]))
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
}




int hashFunction(int key) {

	unsigned long hash = 5381;

	hash = (((hash << 5) + hash) + key) % MAX_TABLE;
	
	return hash;
}


void addUserMsg(int userID, int msgID) {

	// 현재 유저의 우선순위 높은 메세지 5개와 지금 메시지를 보내고 삽입정렬한다.

	// 맨마지막에 삽입

	if (user[userID].midx > 4) {
		user[userID].msg[5] = msgID;
	} else {
		user[userID].msg[user[userID].midx++] = msgID;
	}

	insertionSort(6, user[userID].msg);

}


void addTagHash(char keyStr[],int key, int msgId) {

	int h = hashFunction(key);

	HashNode * cur = &hashTable[h];


	// 처음 테이블에 세길때
	if (cur->key == -1) {
		cur->key = key;
		mstrcpy(cur->keyStr, keyStr);
		cur->data = msgId;
		return;
	}

	HashNode * newNode = &hashNode[hidx++];
	newNode->data = msgId;
	newNode->key = key;
	mstrcpy(newNode->keyStr, keyStr);
	newNode->next = cur->next;
	cur->next = newNode;
	
	return;
}



void createMessage(int msgID, int userID, char msgData[])
{

	// 시간 저장
	int time = 0;
	time += ((msgData[0] - '0') * 10 + (msgData[1] - '0')) * 3600;
	time += ((msgData[3] - '0') * 10 + (msgData[4] - '0')) * 60;
	time += ((msgData[6] - '0') * 10 + (msgData[7] - '0')) * 1;


	msg[msgID].userId = userID;
	msg[msgID].timestamp = time;

	addUserMsg(userID, msgID);

	int idx = 9;
	
	int key = 0;
	int idxWeight = 1;

	char dummyTagStr[10] = "#";


	while (1) {
		
		if (msgData[idx] == '#') {

		}

		if (msgData[idx] >= 'a' && msgData[idx] <= 'z') {
			key += (msgData[idx] - 'a');
			key *= idxWeight;
			dummyTagStr[idxWeight] = msgData[idx];
			idxWeight++;
		}

		if (msgData[idx] == ' ') {

			dummyTagStr[idxWeight] = '\0';
			addTagHash(dummyTagStr,key, msgID);
			idxWeight = 1;
			key = 0;

		}

		if (msgData[idx] == '\0') {
			dummyTagStr[idxWeight] = '\0';
			addTagHash(dummyTagStr,key, msgID);
			idxWeight = 1;
			key = 0;
			break;
		}
		idx++;
	}


}

int getTagKey(char msgData[]) {

	int idx = 0;
	int key = 0;
	int idxWeight = 1;

	if (mstrcmp(msgData, "#fobwdoj") == 0)
		int check = 1;


	while (1) {

		if (msgData[idx] >= 'a' && msgData[idx] <= 'z') {
			key += (msgData[idx] - 'a');
			key *= idxWeight;
			idxWeight++;
		}

		if (msgData[idx] == '\0') {
			break;
		}
		idx++;
	}

	return key;
}


void followUser(int userID1, int userID2)
{
	user[userID1].followings[user[userID1].fidx++] = userID2;
}

int searchByHashtag(char tagName[], int retIDs[])
{	
	int searchedMsgIds[5000] = { 0, };
	int searchIdx = 0;

	int key = getTagKey(tagName);

	int h = hashFunction(key);

	HashNode *cur = &hashTable[h];

	while (1) {
		if (cur->key == key && (mstrcmp(cur->keyStr ,tagName) ==0)) {
			searchedMsgIds[searchIdx++] = cur->data;
		}

		if (cur->next == 0)
			break;

		cur = cur->next;
	}
	
	insertionSort(searchIdx, searchedMsgIds);

	for (int i = 0; i < searchIdx; i++) {

		if (i > 4) {
			break;
		}
		retIDs[i] = searchedMsgIds[i];
	}

	return searchIdx>5? 5: searchIdx;
}

int getMessages(int userID, int retIDs[])
{
	int searchedMsgIds[5000] = { 0, };
	int searchIdx = 0;

	// user 메세지 먼저 넣고

	for (int i = 0; i < user[userID].midx; i++) {
		searchedMsgIds[searchIdx++] = user[userID].msg[i];
	}

	// following 중인애들꺼를 몽땅 다 넣고 정렬

	for (int i = 0; i < user[userID].fidx; i++) {

		for (int j = 0; j < user[user[userID].followings[i]].midx; j++) {
			searchedMsgIds[searchIdx++] = user[user[userID].followings[i]].msg[j];
		}
	}
	
	insertionSort(searchIdx, searchedMsgIds);

	for (int i = 0; i < searchIdx; i++) {

		if (i > 4) {
			break;
		}
		retIDs[i] = searchedMsgIds[i];
	}

	return searchIdx > 5 ? 5 : searchIdx;

}

/*
int main() {

	init();
	
	char testString[50] = "01:12:34 #watch #work";

	char testString1[50] = "01:12:34 #game";
	char testString2[50] = "01:12:34 #dinner #watch";
	char testString3[50] = "01:12:37 #dog #eat";
	
	createMessage(1, 111, testString);
	createMessage(5, 222, testString1);
	createMessage(3, 333, testString2);
	createMessage(9, 333, testString3);

	

	int retIDs[5] = { 0, };
	char tagString[10] = "#watch";
	cout << "search : "<<searchByHashtag(tagString, retIDs);


	cout << "getMessages : " << getMessages(111, retIDs);

	followUser(111, 333);

	cout << "getMessages : " << getMessages(111, retIDs);


}
*/
