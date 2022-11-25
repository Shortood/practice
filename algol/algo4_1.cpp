#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
int cnt = 0;

template <typename itemType>
class PQ {
   private:
    itemType *a;
    int N;

   public:
    PQ(int max) {  //생성자
        a = new itemType[max];
        N = max;
        for (int i = 0; i < max; i++) {
            a[i] = rand() % max + 1;
            // a[i] = i + 1;
        }
    }
    ~PQ() { delete[] a; }  //소멸자

    inline void swap(int i, int j)  //값 바꿔주기
    {
        itemType t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    void MakeHeap(int Root, int LastNode) {  //힙 만들기
        int left, right, parent, rootvalue, son;
        parent = Root;                                    //부모 노드
        left = parent * 2 + 1;                            //왼쪽 자식
        right = left + 1;                                 //오른쪽 자식
        rootvalue = a[Root];                              //부모 노드의 값
        while (left <= LastNode) {                        //자식 노드가 존재
            cnt++;                                        // right left 비교
            if (right <= LastNode && a[right] > a[left])  //더 큰 자식을 비교할 자식으로 선택
                son = right;
            else
                son = left;
            cnt++;                     // root son 비교
            if (rootvalue < a[son]) {  // 만약 부모노드가 자식보다 더 작다면
                a[parent] = a[son];    //값을 바꿔준다
                parent = son;
                left = parent * 2 + 1;
                right = left + 1;
            } else
                break;
        }
        a[parent] = rootvalue;
    }

    void heapsort() {
        int i;
        for (i = N / 2; i >= 1; i--)  //힙 생성
            MakeHeap(i - 1, N - 1);

        for (i = N - 1; i >= 1; i--) {  //힙 정렬
            swap(0, i);
            MakeHeap(0, i - 1);
        }
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << a[i] << " ";
        }
    }
};

int main() {
    int N;
    srand(time(NULL));

    cin >> N;
    PQ<int> pq(N);  //객체 생성

    pq.heapsort();  //힙정렬 실행
    pq.print();
    cout << endl;
    cout << "cnt : " << cnt << endl;
}