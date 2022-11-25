#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int insertKg = 0, quickKg = 0, heapKg = 0;
int n;
template <typename itemType>
inline void swap(itemType a[], int i, int j)
{
    itemType t = a[i];
    a[i] = a[j];
    a[j] = t;
}

template <typename itemType>
void insertion(itemType a[], int N) //삽입정렬
{
    int i, j;
    itemType v;
    for (i = 2; i <= N; i++)
    {
        v = a[i];
        j = i;
        while (a[j - 1] > v)
        {
            // cout << "insertKg + 2* " << v << " + " << a[j - 1] << endl;
            insertKg += 2 * v;    //작은 무게를 두번 더한다
            insertKg += a[j - 1]; //큰 무게를 한 번 더한다
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

template <typename itemType>
int partition(itemType b[], int l, int r)
{
    int i, j;
    itemType v;
    if (r > l)
    {
        v = b[l];
        i = l;
        j = r + 1;
        for (;;)
        {
            while (i + 1 < n && b[++i] < v)
                ;
            while (b[--j] > v)
                ;

            if (i >= j)
                break;
            if (b[i] < b[j]) //아래에 swap에서 더 작은 무게를 두번 하고 큰 무게를 한 번 더한다
            {
                // cout << "quickKg + 2* " << b[i] << " + " << b[j] << endl;
                quickKg += 2 * b[i];
                quickKg += b[j];
            }
            else
            {
                // cout << "quickKg + 2* " << b[j] << " + " << b[i] << endl;
                quickKg += 2 * b[j];
                quickKg += b[i];
            }
            swap(b, i, j);
        }

        if (b[j] < b[l]) //아래의 swap에서 더 작은 값을 두번 더하고 큰 값을 한 번 더한다
        {
            // cout << "quickKg + 2* " << b[j] << " + " << b[l] << endl;
            heapKg += 2 * b[j];
            heapKg += b[l];
        }
        else
        {
            // cout << "quickKg + 2* " << b[l] << " + " << b[j] << endl;
            heapKg += 2 * b[l];
            heapKg += b[j];
        }
    }
    swap(b, j, l);
    return j;
}

template <typename itemType>
void quicksort(itemType b[], int l, int r)
{
    int j;
    if (r > l)
    {
        j = partition(b, l, r);
        quicksort(b, l, j - 1);
        quicksort(b, j + 1, r);
    }
}

void MakeHeap(int c[], int root, int lastnode)
{
    int parent, left, right, son, rootvalue;
    parent = root;
    rootvalue = c[root];
    left = 2 * parent + 1;
    right = left + 1;

    while (left <= lastnode)
    {
        if (right <= lastnode && c[right] > c[left])
            son = right;
        else
            son = left;
        if (rootvalue < c[son])
        {
            // cout << "Heap + 2* " << rootvalue << " + " << c[son] << endl;
            heapKg += 2 * rootvalue; //더 작은 무게를 2번 더하고 큰 무게를 한번 더한다
            heapKg += c[son];
            c[parent] = c[son];
            parent = son;
            left = parent * 2 + 1;
            right = left + 1;
        }
        else
            break;

        c[parent] = rootvalue;
    }
}

template <typename itemType>
void HeapSort(itemType c[], int n)
{
    int i;

    for (i = n / 2; i > 0; i--)
        MakeHeap(c, i - 1, n - 1);

    for (i = n - 1; i > 0; i--)
    {
        if (c[0] < c[i]) //두 무게 중 더 작은 무게를 2번 더하고 큰 무게를 한번 더한다
        {
            // cout << "Heap + 2* " << c[0] << " + " << c[i] << endl;
            heapKg += 2 * c[0];
            heapKg += c[i];
        }
        else
        {
            // cout << "Heap + 2* " << c[i] << " + " << c[0] << endl;
            heapKg += 2 * c[i];
            heapKg += c[0];
        }
        swap(c, 0, i);
        MakeHeap(c, 0, i - 1);
    }
}

int main()
{
    srand(time(NULL));

    int *a, *b, *c; // a 삽입 b 퀵 c힙
    cin >> n;
    a = new int[n + 1];
    b = new int[n];
    c = new int[n];

    for (int i = 0; i < n; i++)
    {
        a[i + 1] = rand() % 1000;
        b[i] = a[i + 1];
        c[i] = a[i + 1];
    }
    a[0] = -1;

    insertion(a, n); //삽입정렬

    quicksort(b, 0, n - 1); //퀵 정렬

    HeapSort(c, n); //힙 정렬

    //각각 정렬 되었는지 확인
    /*
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;

    for (int i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << endl;

    for (int i = 0; i < n; i++)
        cout << c[i] << " ";

    cout << endl;
    */
    //각각 옮긴 무게 출력
    cout << "InsertionKg " << insertKg << endl;
    cout << "QuickKg " << quickKg << endl;
    cout << "HeapKg " << heapKg << endl;

    delete[] a;
    delete[] b;
    delete[] c;
}