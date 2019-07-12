#include <iostream>
using namespace std;

/*
사용자는 SNS에 메시지 전송
사용자간 FOLLOW를 통해서 다른 사용자의 message를 볼수 있음
message는 최대10개의 해쉬태그 + time으로 구성된다.
01:23:45 #xxxx #yyyy #zzzz ...

1) void init()

2) void addMessage(int msgID, int userID, char msgData[])
userID가 messageID를 SNS에 올린다. msgData는 올린시간과 hashtag로 구성된다.
msgData[]길이는 최대 200 message추가는 동일시간 또는 증가되는 시간순으로 호출

3) void followUser(int User1, int User2)
User1의 사용자가 User2를 follow하고
User1의 사용자는 User2사용자의 message를 볼 수 있다.

4) int findHashtagMsg(char hashTag[], int msgID[])
동일 hashTag를 가지는 메세지 ID를 우선순위에 따라 5개 리턴
최근 message가 우선, 동일시간이면 작은 UserID가 우선

5) int findUserMsg(int userID, int msgID[])
User 자신과 User가 follow하는 다른 사용자의 메세지


<제약조건>
message id : 1 ~ 1,000,000
user id : 1 ~ 999
hash tag : #watch #time ~
tag 최대길이는 #포함 9글자
사용자 1명당 최대 100개 message 전송
전체 hashTag는 최대 5000개
함수 호출 횟수는 50000 이하


follow관계는 2차원 배열 간선
boolean follow[USER_MAX][USER_MAX]

struct User{
int msg[5]	// 유저별 best 5개만 유지	// 삭제시 msg에서도 삭제
}user[1000]

struct Message {
	int time
	char messageBody[200];
}


1. 레퍼런스 hashTable 사용방법 익히기

2. 우선순위에 따라 msgID를 저장하는 방법 익히기


*/
#define MAX_KEY 9
#define MAX_TABLE 4096
#define MAX_TAG 5000
#define MAX_MESSAGE 1000000
#define MAX_DATA_LENGTH 200
#define MAX_USER 1000


struct Message {
	int time;
	int userID;
	char data[MAX_DATA_LENGTH];
}m[MAX_MESSAGE];

struct Node{
	char key[MAX_KEY + 1];		// hashtag 키값
	int msgID;					// 그 해당 메시지의 인덱스
	Node *next;					// 다음 hashNode
}a[MAX_TAG];
int ai;

struct User {
	int priorityFives[7];
	int size;
}u[MAX_USER];

bool f[1000][1000] = {false,};


Node *hashTable[MAX_TABLE];

Node* myHashNode(int msgID, char* key) {
	a[ai].msgID = msgID;
	strcpy(a[ai].key, key);

	a[ai].next = nullptr;
	return &a[ai++];

}

bool isHigherThanTarget(int targetMsgId, int sourceMsgId) {

	if (m[targetMsgId].time < m[sourceMsgId].time) {
		return true;
	}
	else if ((m[targetMsgId].time == m[sourceMsgId].time) && (
		(m[targetMsgId].userID > m[sourceMsgId].time))) {
		return true;
	}
	return false;
}


unsigned long myhash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

void HashAdd(char *hashTagString, int msgID ) {


	long hashIdx = myhash(hashTagString);

	Node * sourceNode = myHashNode(msgID, hashTagString);

	if (hashTable[hashIdx] == nullptr) {
		hashTable[hashIdx] = myHashNode(msgID, hashTagString);
		return;
	}

	Node * prev = hashTable[hashIdx];
	Node * current = hashTable[hashIdx];

	while (current) {

		if (isHigherThanTarget(current->msgID, sourceNode->msgID)) {

			if (prev == current) {
				hashTable[hashIdx] = sourceNode;
				sourceNode->next = current;
				
			} else {
				prev->next = sourceNode;
				sourceNode->next = current;
			}
			return;
		}
		prev = current;
		current = current->next;
	}
	return;

}

int HashFind(char *hashTagString, int msgID[]) {

	int count = 0;

	int key = myhash(hashTagString);

	
	if (hashTable[key] == nullptr) {
		return 0;
	}

	Node * current = hashTable[key];

	while (current!=nullptr && count < 5) {
		if (strcmp(current->key, hashTagString) == 0) {
			msgID[count] = current->msgID;
			count++;
		}

		current = current->next;
	}

	return count;

}

// 1회 호출 초기화
void init() {
	// follow 초기화
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			f[i][j] = false;

			if (i != 0 && j != 0 && i == j){
				f[i][j] = true;
			}
		}
	}
	memset(hashTable, 0, sizeof(hashTable));
}


#define MAX_SIZE 7

int heapSize = 0;

void heapInit()
{
	heapSize = 0;
}
void heapInit(int size)
{
	heapSize = size;
}

int heapPush(int *heap, int value)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	heap[heapSize] = value;

	int current = heapSize;
	// 1. 맨마지막에 넣고 부모노드와 비교하면서 올라간다.
	while (current > 0 && isHigherThanTarget(heap[(current - 1) / 2], heap[current]))
	{
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

int heapPop(int *heap, int *value)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0];
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = isHigherThanTarget(heap[current * 2 + 2], heap[current * 2 + 1]) ? current * 2 + 1 : current * 2 + 2;
		}

		if (isHigherThanTarget(heap[child], heap[current]))
		{
			break;
		}

		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
	return 1;
}


void userInsertTop5(int msgID, int userID) {

	heapInit(u[userID].size);
	heapPush(u[userID].priorityFives, msgID);
	u[userID].size++;

}

// message 추가
void addMessage(int msgID, int userID, char msgData[]) {

	m[msgID].userID = userID;

	strcpy(m[msgID].data, msgData);

	m[msgID].time = (msgData[0] - 48) * 100000 + (msgData[1] - 48) * 10000 +
		(msgData[3] - 48) * 1000 + (msgData[4] - 48) * 100 +
		(msgData[6] - 48) * 10 + (msgData[7] - 48) * 1;

	// userID를 기준으로 heap에다가 넣어준다.
	userInsertTop5(msgID, userID);

	// 각 hashTag마다 hashTable에 붙여준다.
	char tempHashTag[9] = {};
	bool copying = false;
	int tempHashIdx = 0;

	// 시간부 없애기
	for (int i = 0; i < 8; i++) {
		*msgData++;
	}

	while (*msgData) {

		if (*msgData == '#') {
			tempHashIdx = 0;
			copying = true;
		}

		if (copying == true && *msgData==' ') {
			copying = false;
			
			// temp init
			tempHashTag[tempHashIdx] = '\0';

			HashAdd(tempHashTag,msgID);

			printf("%s",tempHashTag);
		}

		if (copying) {
			tempHashTag[tempHashIdx] = *msgData;
			tempHashIdx++;
		}

		*msgData++;
	}
	
	tempHashTag[tempHashIdx] = '\0';

	HashAdd(tempHashTag, msgID);
	printf("%s", tempHashTag);

}

void followUser(int User1, int User2) {
	f[User1][User2] = true;
}

//동일 hashTag를 가지는 메세지 ID를 우선순위에 따라 5개 리턴
//최근 message가 우선, 동일시간이면 작은 UserID가 우선
int findHashtagMsg(char hashTag[], int msgID[]) {
	return HashFind(hashTag, msgID);
}

//User 자신과 User가 follow하는 다른 사용자의 메세지
int findUserMsg(int userID, int msgID[]) {

	int tempMessage[5000] = {0,};

	heapInit();
	int best5[5] = {};
	int tempMessageHeapSize = 0;

	for (int i = 0; i < 1000; i++) {

		if (f[userID][i] == true) {
			
			int j = 0;
			heapInit(u[i].size);
			while (u[i].priorityFives[j] != 0) {
				
				heapPop(u[i].priorityFives, &best5[j]);
				
				j++;
			}

			for (int k = 0; k < j; k++) {
				heapPush(u[i].priorityFives, best5[k]);
			}

			heapInit(tempMessageHeapSize);

			for (int k = 0; k < j; k++) {
				heapPush(tempMessage, best5[k]);
			}

			tempMessageHeapSize = heapSize;

		}
	}

	int count = 0;
	while(count < 5) {
		
		heapPop(tempMessage, &msgID[count]);

		if (msgID[count] != 0) {
			count++;
		} else {
			
			break;
		}
	}
	
	return count;
}



int main(int argc, char* argv[])
{
	init();

	char msgData[MAX_DATA_LENGTH + 1] = "10:10:12 #watch";
	addMessage(1, 2, msgData);

	char msgData1[MAX_DATA_LENGTH + 1] = "10:10:13 #watch";
	addMessage(2, 2, msgData1);

	char msgData2[MAX_DATA_LENGTH + 1] = "10:10:14 #watch";
	addMessage(3, 2, msgData2);

	char msgData3[MAX_DATA_LENGTH + 1] = "10:10:20 #watch";
	addMessage(4, 2, msgData3);

	char msgData4[MAX_DATA_LENGTH + 1] = "10:10:19 #watch";
	addMessage(5, 2, msgData4);

	char msgData5[MAX_DATA_LENGTH + 1] = "10:10:17 #watch";
	addMessage(6, 2, msgData5);

	char msgData6[MAX_DATA_LENGTH + 1] = "10:10:18 #watch";
	addMessage(7, 2, msgData6);

	char msgDataForMe[MAX_DATA_LENGTH + 1] = "10:10:50 #time";
	addMessage(8, 1, msgDataForMe);

	followUser(1, 2);

	int msgID[5] = {};
	char watch[MAX_DATA_LENGTH + 1] = "#watch";
	int count = findHashtagMsg(watch, msgID);

	int msgID2[5] = {};
	int count2 = findUserMsg(1, msgID2);

	return 0;
}