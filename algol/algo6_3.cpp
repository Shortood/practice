#include <cstdlib>
#include <ctime>
#include <iostream>

#define itemMIN -1
#define infoNIL -1

using namespace std;
int t_level;  //레벨을 저장하는 변수
template <typename itemType, typename infoType>
class BST {
   private:
    struct node {
        itemType key;   //키 값
        infoType info;  // info 값
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr) {
            key = k;  //노드 생성시 값 넣기
            info = i;
            l = ll;
            r = rr;
        };
    };
    struct node *head, *z;

   public:
    BST(int max) {
        z = new node(0, infoNIL, 0, 0);     //마지막 노드를 z에 넣는다
        head = new node(itemMIN, 0, z, z);  //헤드를 생성
    }
    ~BST() {
        delete_node(head);  //노드들 삭제
        delete z;           // z노드 삭제
    }

    infoType BSTsearch(itemType v) {         //검색
        struct node *x = head->r;            // x에 루트 노드를 넣는다
        z->key = v;                          // z노드에 v값을 저장
        while (v != x->key) {                //값을 찾을 때까지
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

    void MaxMinLvl(int &min, int &max) {  //최대값 최소값 레벨 출력
        MaxMinLvl(head->r, 1, min, max);
    }

    void MaxMinLvl(struct node *t, int level, int &min, int &max) {
        if (t->key < min) min = t->key;                       //현재 확인하는 노드의 값이 min값보다 작으면 값을 저장
        if (t->key > max) max = t->key;                       //현재 확인하는 노드의 값이 max값보다 크면 값을 저장
        if (level > t_level) t_level = level;                 //제일 아래 레벨 저장
        if (t->l != z) MaxMinLvl(t->l, level + 1, min, max);  //자식 노드로 재귀 실행
        if (t->r != z) MaxMinLvl(t->r, level + 1, min, max);
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
    int N, a, min, max;

    srand(time(NULL));
    cin >> N;
    BST<int, int> T1(N);

    for (int i = 0; i < N; i++) {
        a = rand() % N + 1;  //랜덤 수 생성
        // cout << a << " ";
        T1.BSTinsert(a, a);  //정상 노드는 info의 값이 key값과 같다
    }
    min = a;  //마지막 값을 최대, 최소값에 미리 넣는다
    max = a;
    T1.MaxMinLvl(min, max);  //최대 최소 레벨 확인
    cout << endl             //출력
         << t_level << " " << min << " " << max << endl;
}