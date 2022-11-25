#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int cnt = 0, cnt2 = 0;

template <typename itemType>
inline void swap(itemType a[], int i, int j) //값 바꿔주기
{
    itemType t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void MakeHeap(int a[], int root, int lastnode) //힙 생성
{
    int parent, left, right, son, rootvalue;
    parent = root;         //부모 인덱스
    rootvalue = a[root];   //부모 노드 값
    left = 2 * parent + 1; //왼쪽 자식 인덱스
    right = left + 1;      //오른쪽 자식 인덱스

    while (left <= lastnode)
    {
        cnt++;                                       //오른쪽 왼쪽 비교
        if (right <= lastnode && a[right] > a[left]) //오른쪽 자식 값이 왼쪽 자식 값보다 크면
            son = right;                             //비교할 자식은 오른쪽 자식
        else
            son = left;         //아니면 왼쪽 자식
        cnt++;                  // root son 비교
        if (rootvalue < a[son]) //만약 자식의 값이 부모보다 크면
        {
            cnt2++;                //이동 연산
            a[parent] = a[son];    //값을 바꿔준다
            parent = son;          //부모 인덱스를 자식으로 바꿔준다
            left = parent * 2 + 1; //자식 인덱스도 바꿔준다
            right = left + 1;
        }
        else
            break; //만약 크지 않다면 이미 정렬 되었으므로 나간다

        a[parent] = rootvalue; //마지막 자식의 값을 처음 부모 노드의 값으로 바꿔준다
    }
}

template <typename itemType>
void HeapSort(itemType a[], int n) //힙 정렬
{
    int i;

    for (i = n / 2; i > 0; i--)    //제일 오른쪽 제일 자식노드 부터 하기 위해 n/2부터 시작
        MakeHeap(a, i - 1, n - 1); //부모 노드가 최소 하나는 포함되기 위해 i-1부터 힙을 만든다

    for (i = n - 1; i > 0; i--) //최대 노드로 만들어진 힙을 정렬한다
    {
        cnt2++;                // swap 이동
        swap(a, 0, i);         //가장 위에 있는 노드가 가장 큰 값이므로 마지막 노드와 바꾼다
        MakeHeap(a, 0, i - 1); //마지막 노드는 정렬되었으므로 뺴고 다시 힙을 만든다
    }
}

int main()
{
    srand(time(NULL));
    int n;
    int *a;
    cin >> n;
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        // a[i] = rand() % 1000;
        a[i] = i; //worst case
        //a[i] = n - i; // best case
        // cout << a[i] << " ";
    }

    cout << endl
         << "Heap" << endl;
    HeapSort(a, n); //힙정렬
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl
         << "cnt " << cnt << endl;   //비교연산
    cout << "cnt2 " << cnt2 << endl; //자료이동 연산
    delete[] a;
}