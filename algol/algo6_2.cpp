#include <cstdlib>
#include <ctime>
#include <iostream>

#define itemMIN -1  //헤드에 최소갑 넣기
#define infoNIL -1  // NULL을 대신해 -1을 삽입

using namespace std;

int cnt = 0, cnt2 = 0;  //연산 횟수

template <typename itemType, typename infoType>
class BST {
   private:
    struct node {
        itemType key;   //키 값
        infoType info;  // info 값
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr) {
            key = k;  //노드 생성 시 값 넣기
            info = i;
            l = ll;
            r = rr;
        };
    };
    struct node *head, *z;  //헤드 포인터, 마지막 노드를 카리키는 포인터

   public:
    BST(int max) {
        z = new node(0, infoNIL, 0, 0);     //마지막 노드를 z에 넣는다
        head = new node(itemMIN, 0, z, z);  //헤드를 생성
    }
    ~BST() {
    }

    infoType BSTsearch(itemType v) {         //검색
        struct node *x = head->r;            // x에 루트 노드를 넣는다
        z->key = v;                          // z노드에 v값을 저장
        cnt = 0;                             // cnt 초기화
        while (v != x->key) {                //값을 찾을 때까지
            cnt++;                           //이동 연산 횟수 증가
            x = (v < x->key) ? x->l : x->r;  //비교하는 값에 따라 이동할 위치를 정한다
        }

        return x->info;  //찾은 노드의 info 값 리턴
    }

    void BSTinsert(itemType v, infoType info) {  //삽입
        struct node *p, *x;
        p = head;                            //헤드를 넣는다
        x = head->r;                         //루트 노드를 가리키도록 한다
        while (x != z) {                     // x가 마지막 노드에 갈 때까지
            p = x;                           // p포인터가 x포인터를 따라가도록 한다
            x = (v < x->key) ? x->l : x->r;  //비교하는 값에 따리 이동할 노드를 정한다
        }
        x = new node(v, info, z, z);  //새 노드를 생성하고 값을 넣는다
        if (v < p->key)               //넣을 노드의 값을 부모 노드와 비교해
            p->l = x;                 //노드를 넣는다
        else
            p->r = x;
    }

    void traverse(BST<int, int> tbst) {  //재귀 사용
        traverse(head->r, tbst);         //루트 노드를 넣어 실행
    }

    void traverse(struct node *t, BST<int, int> tbst) {  //재귀 사용
        if (t != z) {                                    //만약 현재 확인하는 노드가 범위를 벗어나지 않았다면
            traverse(t->l, tbst);                        //왼쪽 아래 노드부터 확인
            // cout << "insert " << t->key << " in T2" << endl;  //출력
            tbst.BSTinsert(t->key, t->info);  //노드 삽입
            traverse(t->r, tbst);             //오른쪽 아래 노드 확인
        }
    }

    void print() {  //재귀 사용
        print(head->r);
    }

    void print(struct node *t) {    //재귀 사용
        if (t != z) {               //만약 현재 확인하는 노드가 범위를 벗어나지 않았다면
            print(t->l);            //왼쪽 아래 노드부터 확인
            cout << t->key << " ";  //출력
            print(t->r);            //오른쪽 아래 노드 확인
        }
    }
    void delete_node() {  //노드들 삭제
        delete_node(head);
        delete z;
    }
    void delete_node(struct node *t) {
        if (t->info != infoNIL) {
            delete_node(t->l);
            delete_node(t->r);
            delete t;
        }
    }
};

int main() {
    int N, a, *m;
    srand(time(NULL));
    cin >> N;
    m = new int[N];
    BST<int, int> T1(N);  // t1객체 생성
    BST<int, int> T2(N);  // t2객체 생성
    for (int i = 0; i < N; i++) {
        a = rand() % N + 1;  //랜덤 수 생성
        // cout << a << " ";
        T1.BSTinsert(a, a);  //정상 노드는 info의 값이 key값과 같다
        m[i] = a;            //값 저장
    }
    cout << endl;
    T1.traverse(T2);  //값 inder 순으로 넣기
    // T2.print();       //값 출력

    for (int i = 0; i < N; i++) {             //저장한 값들을 찾는다
        if (T2.BSTsearch(m[i])) cnt2 += cnt;  //만약 정상적으로 찾았다면 횟수를 더한다
    }

    cout << endl
         << cnt2 / N << endl;
    
    delete[] m;        //동적할당 해제
    T1.delete_node();  //노드들 삭제
    T2.delete_node();
}