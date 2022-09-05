#include <iostream>
#include <string>

using namespace std;

//14891
string s[4];
int isrotate[4] = { 0 };

//3번 오른쪽  7번 왼쪽

void init() {
	for (int i = 0; i < 4; i++) {
		isrotate[i] = 0;
	}
}
void move(int t, int isro) {
	if (isro == 1) {//시계
		s[t] = s[t].substr(7) + s[t].substr(0, 7);
	}
	else if (isro == -1) {//반시계
		s[t] = s[t].substr(1, 7) + s[t].substr(0, 1);
	}
}

void Right(int n, int t) {//시계 n=톱니번호
	if (n >= 3)return;
	if (s[n][2] != s[n + 1][6]) {//다음꺼 극 다르면
		isrotate[n + 1] = t * -1;
		Right(n + 1, t*-1);
	}
}

void Left(int n, int t) {//반시계 
	if (n <= 0) return;
	if (s[n][6] != s[n - 1][2]) {//다음꺼 극 다르면
		isrotate[n - 1] = t * -1;
		Left(n - 1, t*-1);
	}
}

void check(int top, int t) {//톱니번호, 방향
	isrotate[top] = t;
	Right(top, t);
	Left(top, t);

	for (int i = 0; i < 4; i++) {
		move(i, isrotate[i]);
	}
}


int main() {
	
	int k;
	int mix1,mix2;
	for (int i = 0; i< 4; i++) {
		cin >> s[i];
	}

	cin >> k;

	for (int i = 0; i < k; i++) {
		cin >> mix1 >> mix2;
		init();
		check(mix1 - 1, mix2);
	}

	int result = 0, bo = 1;

	for (int i = 0; i < 4; i++) {
		result += bo * (s[i][0]-'0');
		//cout << s[i][0] << " " << result << " " << bo << endl;
		bo *= 2;
	}
	cout << result;

}