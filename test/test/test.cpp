// test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>    
using namespace std;


/*
	2차원 배열 순회 방식
	1. 그냥
	2. 지그재그
	3. 대각선

*/

struct node {
	int v;
} a[10][10];


void init(node  arr[][10]) {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			arr[i][j].v = i;

		}
	}

}

void zigzag(arr)


//void pswap(int* pA, int* pB)
//{
//	int temp = *pA;
//	*pA = *pB;
//	*pB = temp;
//}
//
//int* pA, a = 5, b = 10;
//pA = &a;
//cout << "*pA = " << *pA << " a = " << a << "\n";
//cout << "pA = " << pA << " &a = " << &a << "\n";
//pswap(pA, &a);
//cout << "*pA = " << *pA << " a = " << a << "\n";
//cout << "pA = " << pA << " &a = " << &a << "\n";
//a = b;
//cout << "*pA = " << *pA << " a = " << a << "\n";
//cout << "pA = " << pA << " &a = " << &a << "\n";


int main()
{



}