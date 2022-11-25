#include <cstdlib>
#include <ctime>
#include <iostream>

#define itemMIN -1   //헤드에 최소갑 넣기
#define infoNIL -1   // NULL을 대신해 -1을 삽입
#define red true     //레드 노드
#define black false  //블랙 노드

using namespace std;
int cnt = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;  //연산 횟수

template <typename itemType>
class HashTable {
   private:
    struct node {
        itemType key;       //키 값
        struct node *next;  //다음 노드
        node(itemType v) {  //키값 넣기
            key = v;
            this->next = NULL;
        }
    };
    node *hash[1010];
    int N;

   public:
    HashTable(int max) {  //최대 크기 설정
        N = max;
    }

    void init() {
        for (int i = 0; i < 1009; i++) {  //테이블 초기화
            hash[i] = NULL;
        }
    }
    void insert(itemType v) {            //삽입
        int hashKey = v % 1009;          //넣을 위치 설정
        node *temp = new node(v);        //새 노드 생성
        if (hash[hashKey] == NULL) {     //현재 같은 해쉬값에 값이 하나도 없다면
            hash[hashKey] = temp;        //제일 앞에 넣는다
        } else {                         //이미있다면
            temp->next = hash[hashKey];  //제일 앞에 붙힌다
            hash[hashKey] = temp;
        }
    }
    bool search(itemType v) {
        cnt = 0;
        int hashKey = v % 1009;
        node *temp = hash[hashKey];
        while (temp != NULL) {
            cnt++;
            if (temp->key == v)
                return true;
            else
                temp = temp->next;
        }
        return false;
    }

    void print() {
        if (N > 1009)  //최대크기 제한
            N = 1009;

        node *temp;
        for (int i = 0; i < N; i++) {  // N보다 큰 수는 만들어지지 않는다
            if (hash[i] != NULL) {     //안에 값이 있다면
                // cout << "i= " << i << endl;
                temp = hash[i];
                while (temp->next != NULL) {  //전부 출력
                    cout << temp->key << " ";
                    temp = temp->next;
                }
                cout << temp->key << " " << endl;
            }
        }
    }

    void delete_hash() {
        node *temp;
        for (int i = 0; i < 1009; i++) {
            if (hash[i] != NULL) {
                temp = hash[i];
                if (temp->next != NULL)
                    delete_hash(temp->next);
                delete temp;
            }
        }
    }

    void delete_hash(node *t) {
        if (t->next != NULL)
            delete_hash(t->next);

        delete t;
    }
};

template <typename itemType, typename infoType>
class RBtree {
   private:
    struct node {
        itemType key;   //키 값
        infoType info;  // info 값
        bool tag;
        struct node *l, *r;
        node(itemType k, infoType i, bool tag, struct node *ll, struct node *rr) {
            key = k;  //노드 생성 시 값 넣기
            info = i;
            this->tag = tag;
            l = ll;
            r = rr;
        };
    };
    node *z, *x, *p, *g, *gg, *head;

   public:
    struct node *rotate(itemType k, struct node *y) {  //트리 회전
        // cout << "rotate" << endl;
        struct node *high, *low;
        high = (k < y->key) ? y->l : y->r;  //넣을 값에 따라 high를 다르게 잡는다
        if (k < high->key) {                //트리의 구조에 따라 회전 방향을 정한다
            low = high->l;
            high->l = low->r;
            low->r = high;
        } else {
            low = high->r;
            high->r = low->l;
            low->l = high;
        }
        if (k < y->key)
            y->l = low;
        else
            y->r = low;
        return low;
    }
    RBtree(int max) {
        z = new node(0, infoNIL, black, 0, 0);
        head = new node(0, 0, black, z, z);
    }
    void insert(itemType k, infoType info) {  //삽입
        // cout << "insert" << endl;
        x = head;  //현재노드
        p = head;  //전노드
        g = head;  //전전노드
        while (x != z) {
            gg = g;  //전전전노드
            g = p;
            p = x;
            x = (k < x->key) ? x->l : x->r;
            if (x->l != NULL && x->r != NULL) {
                // cout << x->l->tag << " " << x->r->tag << endl;
                if (x->l->tag && x->r->tag) split(k);  //형재노드가 모두 빨간색일 경우 split
            }
        }
        // cout << "x생성 " << k << endl;
        x = new node(k, info, red, z, z);  //노드 생성
        if (k < p->key)                    //노드 삽입
            p->l = x;
        else
            p->r = x;
        split(k);  //조건 확인
        head->r->tag = black;
    }

    void split(itemType k) {  //조건에 맞지않는 경우 수정
        // cout << "split" << endl;
        x->tag = red;
        x->l->tag = black;
        x->r->tag = black;
        if (p->tag) {
            g->tag = red;
            if (k < g->key != k < p->key) p = rotate(k, g);
            x = rotate(k, gg);
            x->tag = black;
        }
    }

    void print() {  //재귀 사용
        cout << endl;
        print(head);
    }

    void print(struct node *t) {    //재귀 사용
        if (t != z) {               //만약 현재 확인하는 노드가 범위를 벗어나지 않았다면
            print(t->l);            //왼쪽 아래 노드부터 확인
            cout << t->key << " ";  //출력
            print(t->r);            //오른쪽 아래 노드 확인
        }
    }

    void del() {  //재귀 사용
        del(head);
        delete z;
    }

    void del(struct node *t) {  //재귀 사용
        if (t != z) {           //만약 현재 확인하는 노드가 범위를 벗어나지 않았다면
            del(t->l);          //왼쪽 아래 노드부터 확인
            del(t->r);          //오른쪽 아래 노드 확인
            delete t;
        }
    }

    bool RBsearch(itemType v) {              //검색
        struct node *x = head;               // x에 루트 노드를 넣는다
        cnt3 = 0;                            // cnt 초기화
        while (v != x->key) {                //값을 찾을 때까지
            cnt3++;                          //이동 연산 횟수 증가
            x = (v < x->key) ? x->l : x->r;  //비교하는 값에 따라 이동할 위치를 정한다
        }
        return x;  //찾은 노드의 info 값 리턴
    }
};

template <typename itemType>
class tree_234 {  // 234트리
   private:
    struct node {
        itemType key[3];  //키 값
        int no_cnt;
        struct node *t1, *t2, *t3, *t4;
        node() {  //노드와 값들 초기화
            t1 = NULL;
            t2 = NULL;
            t3 = NULL;
            t4 = NULL;
            no_cnt = 0;
            key[0] = 0;
            key[1] = 0;
            key[2] = 0;
        }
    };

   public:
    struct node *head;  //헤드 포인터
    tree_234() {
        head = NULL;
    }

    void inprint() {  //크기대로 출력
        inprint(head);
    }

    void inprint(node *t) {
        if (t != NULL) {
            if (t->t1 != NULL)
                inprint(t->t1);
            if (t->key[0] != 0)
                cout << t->key[0] << endl;
            if (t->t2 != NULL)
                inprint(t->t2);
            if (t->key[1] != 0)
                cout << t->key[1] << endl;
            if (t->t3 != NULL)
                inprint(t->t3);
            if (t->key[2] != 0)
                cout << t->key[2] << endl;
            if (t->t4 != NULL)
                inprint(t->t4);
        }
    }
    void traverse(RBtree<int, int> tbst) {  //재귀 사용
        traverse(head, tbst);               //루트 노드를 넣어 실행
    }

    void traverse(struct node *t, RBtree<int, int> tbst) {  //재귀 사용
        if (t != NULL) {                                    //만약 현재 확인하는 노드가 범위를 벗어나지 않았다면
            if (t->t1 != NULL)
                traverse(t->t1, tbst);
            if (t->t2 != NULL)
                traverse(t->t2, tbst);
            if (t->t3 != NULL)
                traverse(t->t3, tbst);
            if (t->t4 != NULL)
                traverse(t->t4, tbst);
            if (t->key[0] != 0)
                tbst.insert(t->key[0], t->key[0]);  //노드 삽입
            if (t->key[1] != 0)
                tbst.insert(t->key[1], t->key[0]);  //노드 삽입
            if (t->key[2] != 0)
                tbst.insert(t->key[2], t->key[0]);  //노드 삽입
        }
    }
    void del() {  //크기대로 출력
        del(head);
    }

    void del(node *t) {
        if (t != NULL) {
            if (t->t1 != NULL)
                del(t->t1);
            if (t->t2 != NULL)
                del(t->t2);
            if (t->t3 != NULL)
                del(t->t3);
            if (t->t4 != NULL)
                del(t->t4);
            delete t;
        }
    }

    node *separate(node *no, node *pri) {  //현재 노드, 전 노드  노드 분리
        if (no == head) {                  //헤드 분리
            head = new node();
            node *temp = new node();
            head->key[0] = no->key[1];
            head->no_cnt = 1;
            head->t1 = no;
            head->t2 = temp;
            temp->key[0] = no->key[2];
            temp->t1 = no->t3;
            temp->t2 = no->t4;
            no->t3 = NULL;
            no->t4 = NULL;
            no->no_cnt = 1;
            no->key[1] = 0;
            no->key[2] = 0;
            temp->no_cnt = 1;
            return head;
        } else {  //헤드가 아닌 노드 분리
            node *temp = new node();
            if (pri->t1 == no) {  //넣을 자리가 첫번째
                pri->key[2] = pri->key[1];
                pri->key[1] = pri->key[0];
                pri->key[0] = no->key[1];
                pri->t4 = pri->t3;
                pri->t3 = pri->t2;
                pri->t2 = temp;
                temp->key[0] = no->key[2];
            } else if (pri->t2 == no) {  //넣을 자리가 두번째
                pri->key[2] = pri->key[1];
                pri->key[1] = no->key[1];
                pri->t4 = pri->t3;
                pri->t3 = temp;
                temp->key[0] = no->key[2];
            } else if (pri->t3 == no) {  //넣을 자리가 세번째
                pri->key[2] = no->key[1];
                pri->t4 = temp;
                temp->key[0] = no->key[2];
            } else if (pri->t4 == no) {  //오류 처리(나면 안됨)
                cout << "t4 separate error" << endl;
            } else {  //오류 처리(나면 안됨)
                cout << "separate error" << endl;
            }
            //분리후 값과 노드 정리
            no->key[1] = 0;
            no->key[2] = 0;
            no->no_cnt = 1;
            temp->no_cnt = 1;
            pri->no_cnt += 1;
            temp->t1 = no->t3;
            temp->t2 = no->t4;
            no->t3 = NULL;
            no->t4 = NULL;
            return pri;
        }
    }

    void insert(itemType t) {  //삽입
        if (empty()) {         //트리가 비었을때
            head = new node();
            head->key[0] = t;
            head->no_cnt = 1;
        } else {
            struct node *p, *x;
            p = head;  //헤드를 넣는다
            x = head;  //루트 노드를 가리키도록 한다
            while (1) {
                //헤드 분리 확인
                if (x->no_cnt == 3) {      //분리
                    x = separate(x, p);    //들어갈 노드
                    if (x->no_cnt == 3) {  //분리한 후 전노드가 3개가 되었을때 x를 아래로 내려줌
                        if (t < x->key[0]) {
                            x = x->t1;
                        } else if (t < x->key[1]) {
                            x = x->t2;
                        } else if (t < x->key[2]) {
                            x = x->t3;
                        } else
                            x = x->t4;
                    }
                }

                if (head->no_cnt == 3) {    //분리
                    x = separate(head, p);  //들어갈 노드
                    //뒤노드보다 작으면 앞노드로
                }

                p = x;                    // p포인터가 x포인터를 따라가도록 한다
                if (x->no_cnt == 1) {     // 1, 2번 노드 존재 가능
                    if (x->t1 != NULL) {  //아래 노드 존재
                        if (t < x->key[0])
                            x = x->t1;
                        else
                            x = x->t2;
                    } else {  //아래 노드 없음
                        if (t < x->key[0]) {
                            x->key[1] = x->key[0];
                            x->key[0] = t;
                            x->no_cnt = 2;
                            return;
                        } else {
                            x->key[1] = t;
                            x->no_cnt = 2;
                            return;
                        }
                    }
                } else if (x->no_cnt == 2) {  // 1, 2, 3번 노드 존재가능
                    if (t < x->key[0]) {      //작은 값은 무조건 존재
                        if (x->t1 != NULL) {  //아래 노드 존재
                            x = x->t1;
                        } else {  //아래 노드 없음
                            x->key[2] = x->key[1];
                            x->key[1] = x->key[0];
                            x->key[0] = t;
                            x->no_cnt = 3;
                            return;
                        }
                    } else if (t < x->key[1]) {
                        if (x->t2 != NULL) {  //아래 노드 존재
                            x = x->t2;
                        } else {  //아래 노드 없음
                            x->key[2] = x->key[1];
                            x->key[1] = t;
                            x->no_cnt = 3;
                            return;
                        }
                    } else {  //들어갈 위치가 3번째
                        if (x->t3 != NULL) {
                            x = x->t3;
                        } else {
                            x->key[2] = t;
                            x->no_cnt = 3;
                            return;
                        }
                    }
                } else if (x->no_cnt == 0) {  //오류 처리(나면 안됨)
                    cout << "0 갯수에러" << endl;
                    return;
                }
            }
        }
    }

    bool empty() {
        return head == NULL;
    }
};

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
    tree_234<int> tree;
    RBtree<int, int> T3(N);
    BST<int, int> T1(N);  // t1객체 생성
    BST<int, int> T2(N);  // t2객체 생성
    HashTable<int> hash(N);
    hash.init();  //초기화
    for (int i = 0; i < N; i++) {
        a = rand() % N + 1;  //랜덤 수 생성
        // cout << a << " ";
        T1.BSTinsert(a, a);  //정상 노드는 info의 값이 key값과 같다
        m[i] = a;            //값 저장
        tree.insert(a);
        hash.insert(a);  //삽입
    }
    tree.traverse(T3);  // 234트리를 레드블랙트리로 변환

    // T3.print(); //레드블랙 트리 출력
    // cout << endl;
    T1.traverse(T2);  //값 inorder 순으로 넣기
    T1.print();       // inorder 출력

    for (int i = 0; i < N; i++) {  //저장한 값들을 찾는다
        if (T1.BSTsearch(m[i])) cnt2 += cnt;
        if (T2.BSTsearch(m[i])) cnt5 += cnt;  //만약 정상적으로 찾았다면 횟수를 더한다
        if (T3.RBsearch(m[i])) cnt4 += cnt3;  //만약 정상적으로 찾았다면 횟수를 더한다
        if (hash.search(m[i])) cnt6 += cnt;
    }
    cout << endl;
    cout << "T1 = " << cnt2 / N << " T2 = " << cnt5 / N << " T3 = " << cnt4 / N << " Hash " << cnt6 / N << endl;
    // hash.print();  //출력
    //  tree.inprint();
    delete[] m;        //동적할당 해제
    T1.delete_node();  //노드들 삭제
    T2.delete_node();
    hash.delete_hash();
    tree.del();
    T3.del();
}
