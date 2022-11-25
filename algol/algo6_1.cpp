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
            key = k;  //노드 생성 후 값 입력
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
        delete_node(head);  //동적할당 해제
        delete z;
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

    void delete_node(struct node *t) {  //노드들 삭제
        if (t->info != infoNIL) {
            delete_node(t->l);
            delete_node(t->r);
            delete t;
        }
    }
};

int main() {
    int N, a;
    srand(time(NULL));
    cin >> N;             //갯수 입력
    int *m = new int[N];  //배열 동적할당
    BST<int, int> T1(N);  // bst 객체 생성

    for (int i = 0; i < N; i++) {
        a = rand() % N + 1;  //랜덤 수 생성
        // cout << a << " ";
        T1.BSTinsert(a, a);  //정상 노드는 info의 값이 key값과 같다
        m[i] = a;            // 값저장
    }

    for (int i = 0; i < N; i++) {             //저장한 값들을 찾는다
        if (T1.BSTsearch(m[i])) cnt2 += cnt;  //만약 정상적으로 찾았다면 횟수를 더한다
    }
    cout << endl
         << cnt2 / N << endl;  //출력
    delete[] m;                //동적할당 해제
}