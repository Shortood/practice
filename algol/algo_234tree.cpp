#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <typename itemType>
class tree_234 {
   private:
    struct node {
        itemType key[3];  //키 값
        int no_cnt;
        struct node *t1, *t2, *t3, *t4;
        node() {
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
    void print() {
        print(head);
    }

    void print(node *t) {
        if (t != NULL) {
            cout << t->key[0] << " " << t->key[1] << " " << t->key[2] << endl;
            print(t->t1);
            print(t->t2);
            print(t->t3);
            print(t->t4);
        }
    }

    void inprint() {
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
    node *separate(node *no, node *pri) {  //현재 노드, 전 노드
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
        } else {
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
            } else if (pri->t4 == no) {
                cout << "t4 separate error" << endl;
            } else {
                cout << "separate error" << endl;
            }
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

    void insert(itemType t) {
        if (empty()) {  //트리가 비었을때
            head = new node();
            head->key[0] = t;
            head->no_cnt = 1;
        } else {
            struct node *p, *x;
            p = head;  //헤드를 넣는다
            x = head;  //루트 노드를 가리키도록 한다
            while (1) {
                //헤드 분리 확인
                if (x->no_cnt == 3) {    //분리
                    x = separate(x, p);  //들어갈 노드
                    if (x->no_cnt == 3) {
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
                } else if (x->no_cnt == 0) {
                    cout << "0 갯수에러" << endl;
                    return;
                }
            }
        }
    }

    bool
    empty() {
        return head == NULL;
    }
};

int main() {
    int N, a, *m;
    srand(time(NULL));
    cin >> N;
    m = new int[N];
    tree_234<int> tree;
    for (int i = 0; i < N; i++) {
        a = rand() % N + 1;  //랜덤 수 생성
        m[i] = a;            //값 저장
        tree.insert(a);
        // tree.print();
    }
    cout << "-----" << endl;
    // tree.print();
    cout << "-----" << endl;
    tree.inprint();
    delete[] m;  //동적할당 해제
}