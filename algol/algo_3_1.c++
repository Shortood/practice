#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int cnt = 0, cnt2 = 0; //비교연산 수, 자료이동 수

template <typename itemType>
void insertion(itemType a[], int N)
{
    int i, j;
    itemType v;
    for (i = 2; i <= N; i++)
    {
        v = a[i];
        j = i;
        while (a[j - 1] > v)
        {
            a[j] = a[j - 1];
            j--;
            cnt++;  // a[j-1] 비교연산
            cnt2++; // 자료이동
        }
        cnt++; // while문 나오기전 비교
        a[j] = v;
    }
}

int main()
{
    srand(time(NULL));
    int n;
    int *a;
    cin >> n;
    a = new int[n + 1];
    for (int i = 1; i <= n; i++)
    {
        //a[i] = rand() % 1000; // 1000 이하의 수 랜덤 입력
        //a[i] = i; //best case
        a[i] = n - i; //worst case
        // cout << a[i] << " ";
    }
    a[0] = -1;       //무조건 제일 작은 값을 가지고 비교할 수
    insertion(a, n); //삽입 정렬 실행
    cout << endl
         << "insertion" << endl;
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << "cnt " << cnt << endl;   //비교 연산 출력
    cout << "cnt2 " << cnt2 << endl; //자료이동
    delete[] a;
}