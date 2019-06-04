
#include<iostream>

using namespace std;



int checkCorrect(double mid , double val) {
	return (mid*(mid + 1) / 2 == val) ? 1:0;
}

int isHigh(double mid, double res) {
	double resMid=(mid*(mid + 1) / 2);
	if (resMid > res) {
		return 1;
	}
	else {
		return 0;
	}
}

int valueOfDecimal(double v) {
	int count = 0;
	while (v > 1) {

		v = (v / 10);
		count++;
	}
	return count;
}

int maxOfDec(int dec) {

	int max = 1;
	for (int i = 0; i <= dec; i++) {

		max = max * 10;
	}
	return max - 1;
}

void checkMinMax(double r, double& min, double& max) {

	double start = 1;

	while ( start * (start + 1) / 2  <  r ) {
		start = start * 10;
	}

	min = start / 10;

	max = start;
}


double find(double r) {
	
	double min = 1;
	double max = 1;

	checkMinMax(r, min, max);
	double mid = ((max - min)/2 )+ min;

	while ( checkCorrect(mid,r) == 0 ) {

		if (min == mid || max == mid) {
			return -1;
		}

		if (isHigh(mid, r)) {
			max = mid;
		}else {
			min = mid;
		}
		mid = ((max - min)/2) + min;
	}

	return mid;
}


int main(int argc, char** argv)
{
	int test_case;
	int t = 0;
	freopen("input_test.txt", "r", stdin);
	cin >> t;
	
	for (test_case = 1; test_case <= t; ++test_case)
	{
		double param;
		cin >> param;
		double res = find(param);
		int resInt = res;

		/*
		double min = 1;
		double max = 1;
		checkMinMax(param, min, max);
		*/
		//cout << min <<" "<< max << endl;

		cout << "#" << test_case << " " << resInt << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}