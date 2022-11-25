#include <iostream>
using namespace std;

const int N = 10000;

int main() // O(N^1/2) //에라토스테네스의 공식 이용
{
    int i, j, a[N + 1];
    int cnt = 0; //곱셈연산회수
    for (a[1] = 0, i = 2; i <= N; i++)
        a[i] = 1;

    for (i = 2; i * i <= N; i++) // N의 제곱근 까지만 반복
    {
        cnt++; //i*i에서 곱셈 연산 이용
        if (a[i] != 0) //아직 소수가 아니라고 판명나지 않았다면
        {
            cnt++; //j=i*i에서 이용
            for (j = i * i; j <= N; j += i) 
            { // i*i부터 N까지 j의 배수들을 모두 소수가 아니라고 판명
                a[j] = 0;
            }
        }
    }
    for (i = N; i >= 2; i--)
        if (a[i])
        { //소수 출력
            cout << i << endl;
            cout << "cnt: " << cnt << endl;
            break;
        }
    cout << endl;
}
