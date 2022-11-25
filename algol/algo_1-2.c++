#include <iostream>

using namespace std;

const int N = 500;

int main() // O(N^2)
{
    int i, j, a[N + 1];
    for (a[1] = 0, i = 2; i <= N; i++) //배열 초기화
        a[i] = 1;

    for (i = 2; i <= N / 2; i++)
        for (j = 2; j <= N / i; j++)
            a[i * j] = 0;//약수가 있는 수들 확인

    for (i = 1; i <= N; i++)
        if (a[i]) //소수 출력
            cout << i << ' ';

    cout << endl;
}


/*
int main()// O(N^1/2) //에라토스테네스의 공식 이용
{
    int i, j, a[N + 1];

    for (a[1] = 0, i = 2; i <= N; i++)
        a[i] = 1;

    for (i = 2; i * i <= N; i++) //N의 제곱근 까지만 반복
    {
        if (a[i] != 0) //아직 소수가 아니라고 판명나지 않았다면
        {
            for (j = i * i; j <= N; j += i) //i*i부터 N까지 j의 배수들을 모두 소수가 아니라고 판명
                a[j] = 0;
        }
    }
    
    for (i = 1; i <= N; i++)
        if (a[i]) //소수 출력
            cout << i << ' ';

    cout << endl;
}
*/