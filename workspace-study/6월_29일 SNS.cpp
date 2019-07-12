#include <iostream>
using namespace std;

/*
����ڴ� SNS�� �޽��� ����
����ڰ� FOLLOW�� ���ؼ� �ٸ� ������� message�� ���� ����
message�� �ִ�10���� �ؽ��±� + time���� �����ȴ�.
01:23:45 #xxxx #yyyy #zzzz ...

1) void init()

2) void addMessage(int msgID, int userID, char msgData[])
userID�� messageID�� SNS�� �ø���. msgData�� �ø��ð��� hashtag�� �����ȴ�.
msgData[]���̴� �ִ� 200 message�߰��� ���Ͻð� �Ǵ� �����Ǵ� �ð������� ȣ��

3) void followUser(int User1, int User2)
User1�� ����ڰ� User2�� follow�ϰ�
User1�� ����ڴ� User2������� message�� �� �� �ִ�.

4) int findHashtagMsg(char hashTag[], int msgID[])
���� hashTag�� ������ �޼��� ID�� �켱������ ���� 5�� ����
�ֱ� message�� �켱, ���Ͻð��̸� ���� UserID�� �켱

5) int findUserMsg(int userID, int msgID[])
User �ڽŰ� User�� follow�ϴ� �ٸ� ������� �޼���


<��������>
message id : 1 ~ 1,000,000
user id : 1 ~ 999
hash tag : #watch #time ~
tag �ִ���̴� #���� 9����
����� 1��� �ִ� 100�� message ����
��ü hashTag�� �ִ� 5000��
�Լ� ȣ�� Ƚ���� 50000 ����


follow����� 2���� �迭 ����
boolean follow[USER_MAX][USER_MAX]

struct User{
int msg[5]	// ������ best 5���� ����	// ������ msg������ ����
}user[1000]

struct Message {
	int time
	char messageBody[200];
}


1. ���۷��� hashTable ����� ������

2. �켱������ ���� msgID�� �����ϴ� ��� ������


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
	char key[MAX_KEY + 1];		// hashtag Ű��
	int msgID;					// �� �ش� �޽����� �ε���
	Node *next;					// ���� hashNode
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

// 1ȸ ȣ�� �ʱ�ȭ
void init() {
	// follow �ʱ�ȭ
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
	// 1. �Ǹ������� �ְ� �θ���� ���ϸ鼭 �ö󰣴�.
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

// message �߰�
void addMessage(int msgID, int userID, char msgData[]) {

	m[msgID].userID = userID;

	strcpy(m[msgID].data, msgData);

	m[msgID].time = (msgData[0] - 48) * 100000 + (msgData[1] - 48) * 10000 +
		(msgData[3] - 48) * 1000 + (msgData[4] - 48) * 100 +
		(msgData[6] - 48) * 10 + (msgData[7] - 48) * 1;

	// userID�� �������� heap���ٰ� �־��ش�.
	userInsertTop5(msgID, userID);

	// �� hashTag���� hashTable�� �ٿ��ش�.
	char tempHashTag[9] = {};
	bool copying = false;
	int tempHashIdx = 0;

	// �ð��� ���ֱ�
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

//���� hashTag�� ������ �޼��� ID�� �켱������ ���� 5�� ����
//�ֱ� message�� �켱, ���Ͻð��̸� ���� UserID�� �켱
int findHashtagMsg(char hashTag[], int msgID[]) {
	return HashFind(hashTag, msgID);
}

//User �ڽŰ� User�� follow�ϴ� �ٸ� ������� �޼���
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