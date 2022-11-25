#include <cstring>
#include <iostream>

using namespace std;
#define SIZE 3000

int cnt_f = 0, cnt_i = 0;

int fib(int n) {  //피보나치
    cnt_f++;      //피보나치 재귀 실행 수
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    else
        return (fib(n - 1) + fib(n - 2));
}

void sumarr(int a[], int b[], int s[]) {  //배열 더하기
    int supp = 0, i;

    for (i = 0; i < SIZE; i++) {  //두 배열을 더해줌
        s[i] = a[i] + b[i] + supp;
        if (s[i] >= 10) {
            s[i] -= 10;
            supp = 1;
        } else
            supp = 0;
    }
}

void printarr(int a[]) {  //배열 출력
    bool flag = false;
    for (int i = SIZE - 1; i >= 0; i--) {
        if (a[i] != 0) flag = true;
        if (flag == true)
            cout << a[i];
    }
    cout << endl;
}
void copyarr(int a[], int b[]) {  //배열 복사
    for (int i = SIZE - 1; i >= 0; i--) {
        b[i] = a[i];
    }
}
int main() {
    int f1[3000] = {0}, f2[3000] = {0}, s[3000] = {0};
    int temp[3000] = {0}, n;
    cin >> n;
    // cout << fib(n) << endl;
    f1[0] = 1;
    for (int i = 0; i < n; i++) {
        cnt_i++;
        sumarr(f1, f2, s);
        copyarr(f2, temp);  // f2->temp
        copyarr(s, f2);     // s->f2
        copyarr(temp, f1);  // temp->f1
    }
    printarr(s);
    cout << "재귀 방식 : " << cnt_f << endl;
    cout << "반복 방식 : " << cnt_i << endl;
}