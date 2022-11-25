#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
int cnt = 0, cnt2 = 0;
int n;
template <typename itemType>
inline void swap(itemType a[], int i, int j) //자료 바꾸기
{
    itemType t = a[i];
    a[i] = a[j];
    a[j] = t;
}

template <typename itemType>
int partition(itemType a[], int l, int r) //교환 할 수 찾고 바꾸기
{
    int i, j;
    itemType v; //키 값
    cnt++;      // r>l 비교
    if (r > l)
    {
        v = a[l];  //제일 왼쪽 값을 키 값으로
        i = l;     // i의 초기값을 제일 왼쪽 인덱스로 설정
        j = r + 1; // j의 초기값을 제일 오른쪽 인덱스에서 한칸 옆으로 설정
        for (;;)
        {                                   //값이 범위를 벗어나지 않도록 함
            while (i + 1 < n && a[++i] < v) //키 값보다 큰 값을 만날 때까지 i값 증가
                cnt++;                      //비교연산 수 증가
            while (a[--j] > v)              //키 값보다 작은 값을 만날 때까지 i값 증가
                cnt++;                      //비교연산 수 증가
            cnt++;                          // i<=j 비교
            if (i >= j)                     //만약 i가 j보다 커지면 역전했으므로
                break;                      //나간다
            swap(a, i, j);                  // a[i]와 a[j]값을 바꿔준다
            cnt2++;                         // swap 이동 연산
        }
    }
    swap(a, j, l); //키값과 a[j]값을 바꿔준다.
    cnt2++;        // swap 이동 연산
    return j;      //다음 퀵정렬 기준이 되는 인덱스 리턴
}

template <typename itemType>
void quicksort(itemType a[], int l, int r)
{
    int j;
    cnt++;     // r>l 비교
    if (r > l) //아직 오른쪽 인덱스가 왼쪽 인덱스 보다 오른쪽에 있다면
    {
        j = partition(a, l, r); //교환할 수 찾기
        quicksort(a, l, j - 1); //구간 나눠서 퀵정렬 실행
        quicksort(a, j + 1, r);
    }
}

int main()
{
    srand(time(NULL));

    int *a;
    cin >> n;
    a = new int[n]; // a배열 동적할당
    for (int i = 0; i < n; i++)
    {
        //a[i] = rand() % 1000;
        a[i] = i; //worst case
        // cout << a[i] << " ";
    }

    quicksort(a, 0, n - 1); //퀵정렬 실행
    cout << endl;
    cout << "quick" << endl;
    for (int i = 0; i < n; i++) //정렬된 값 출력
        cout << a[i] << " ";
    cout << endl;
    cout << "cnt " << cnt << endl;   //비교 연산 출력
    cout << "cnt2 " << cnt2 << endl; //자료이동 출력
    delete[] a;
}