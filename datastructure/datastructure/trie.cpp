/*
[5052��] ��ȭ��ȣ ��� :: https://www.acmicpc.net/problem/5052

[����]

��ȭ��ȣ ����� �־�����. �̶�, �� ����� �ϰ����� �ִ��� �������� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
��ȭ��ȣ ����� �ϰ����� �����Ϸ���, �� ��ȣ�� �ٸ� ��ȣ�� ���ξ��� ��찡 ����� �Ѵ�.
���� ���, ��ȭ��ȣ ����� �Ʒ��� ���� ��츦 �����غ���

�����ȭ: 911
���: 97 625 999
����: 91 12 54 26
�� ��쿡 �����̿��� ��ȭ�� �� �� �ִ� ����� ����. ��ȭ�⸦ ��� ������ ��ȣ�� ó�� �� �ڸ��� ������ ���� �ٷ� �����ȭ�� �ɸ��� �����̴�. ����, �� ����� �ϰ����� ���� ����̴�.

[�Է�]
ù° �ٿ� �׽�Ʈ ���̽��� ���� t�� �־�����. (1 �� t �� 50) �� �׽�Ʈ ���̽��� ù° �ٿ��� ��ȭ��ȣ�� �� n�� �־�����. (1 �� n �� 10000) ���� n���� �ٿ��� ��Ͽ� ���ԵǾ� �ִ� ��ȭ��ȣ�� �ϳ��� �־�����. ��ȭ��ȣ�� ���̴� ���� 10�ڸ��̸�, ��Ͽ� �ִ� �� ��ȭ��ȣ�� ���� ���� ����.

[���]
�� �׽�Ʈ ���̽��� ���ؼ�, �ϰ��� �ִ� ����� ��쿡�� YES, �ƴ� ��쿡�� NO�� ����Ѵ�.


���� �Է� 1
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346

���� ��� 1
NO
YES


[Ǯ�� ����]

1. �Է� N���� ����ó ,
��ȭ��ȣ ��Ϲ迭 ����
�׿� ���ÿ� Trie �ڷᱸ���� �Է�

2.��ȭ��ȣ ����� ���ư��鼭 �̰��� ���ξ����� Ȯ��
���������� ���ξ��� ��찡 ������ YES
�ݴ��� ���� NO

*/
#include "pch.h"
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <algorithm>


const int TrieNode = 10; // ����

typedef struct Trie{

	Trie *next[TrieNode] = {NULL,};
	bool finish = false;
	bool nextChild = false;

	bool insert(const char * key) {

		if (*key == '\0') {
			finish = true;

			nextChild ? 0 : 1;
		}

		int nextKey = *key - '0';

		if (!next[nextKey])
			next[nextKey] = new Trie;

		nextChild = true;

		bool get = next[nextKey]->insert(key + 1);

		return !finish && get;

	}
} TRIE;

int main()
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n;
		scanf("%d", &n);

		// Ʈ������ ��Ʈ ����
		Trie *root = new Trie;

		bool chk = true;

		for (int i = 0; i < n; i++)
		{
			char phone[11];
			scanf("%s", phone);

			// �ϰ����� ���ٸ�
			if (chk && root->insert(phone) == 0)
				chk = false;
		}

		if (chk)
			printf("YES\n");
		else
			printf("NO\n");

		// Ʈ���� �Ҹ�
		delete root;
	}

	return 0;
}



