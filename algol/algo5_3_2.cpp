#include <iostream>

using namespace std;

struct node *x, *z;

struct node {
    char info;           //값
    struct node *l, *r;  //왼쪽 아래 노드, 오른쪽 아래 노드
    struct node *next;   //스택에서 사용할 다음 노드를 가리키는 포인터
    struct node *qnext;  //큐에서 사용할 다음 노드를 가리키는 포인터
};

void visit(node *t) {  //값 출력
    cout << t->info << " ";
}

template <typename itemType>
class Queue {
   private:
    node *head, *z;  //헤드포인터, 임시포인터

   public:
    Queue() {
        head = NULL;  //헤드 초기화
    }
    ~Queue() {
    }
    inline void put(itemType v) {  //삽입
        if (empty()) {             //만약 큐가 비어있다면
            head = v;              //헤드에 값을 바로 넣는다
            head->qnext = NULL;
        } else {       //아니라면
            z = head;  // z포인터를 통해 가장 마지막에 값을 추가한다
            while (z->qnext != NULL) {
                z = z->qnext;
            }
            z->qnext = v;
        }
    }
    inline itemType get() {
        node *temp = head;
        head = head->qnext;  //헤드의 값을 임시 노드를 사용해 출력하고 헤드를 이동시킨다
        return temp;
    }
    inline int empty() {  //비었는지 확인
        return head == NULL;
    }
};

Queue<node *> queue;  //큐 객체 생성

void levelOrderTraverse(struct node *t) {
    queue.put(t);                        //큐에 노드 삽입
    while (!queue.empty()) {             //큐가 비어있지 않으면
        t = queue.get();                 //노드를 가져온다
        visit(t);                        //값 출력
        if (t->l != z) queue.put(t->l);  //왼쪽 노드가 있다면 삽입
        if (t->r != z) queue.put(t->r);  //오른쪽 노드가 있다면 삽입
    }
}

template <typename itemType>
class Stack {
   private:
    node *head, *z;  //가장 앞을 가리키는 포인터, 임시 포인터

   public:
    Stack() {
        head = NULL;  //헤드 초기화
    }
    ~Stack() {
        head == NULL;  //헤드 초기화
    }
    inline void push(itemType v) {  //푸시
        if (empty()) {              //만약 스택이 비어있다면
            head = v;               //바로 헤드에 노드를 넣는다
            head->next = NULL;
        } else {
            v->next = head;  //아니면 새로운 노드를 헤드로 만들고 연결시킨다
            head = v;
        }
    }
    inline itemType pop() {
        z = head;
        if (!empty()) {         //하나라도 있을 때
            head = head->next;  //헤드를 다음 노드를 가리키도록 하고
            return z;           //리턴 시킨다
        }
        return NULL;  //아니면 값을 리턴시키지 않는다
    }

    inline int empty() {  //비어있는지 확인
        return head == NULL;
    }
};

void clear(struct node *t) {  //메모리 초기화
    if (t != z) {             //존재하는 모든 노드 동적 해제
        clear(t->l);
        delete t;
        clear(t->r);
    }
}

int main() {
    char c;
    Stack<node *> stack;  //객체 생성
    z = new node;         //노드 동적할당
    z->l = z;             //범위를 확인하기 위한 노드 생성
    z->r = z;
    while ((c = cin.get()) != '\n') {   //한 줄 입력 받기
        while ((c == ' ')) cin.get(c);  //공백은 받지 않도록
        x = new node;                   //새로운 노드에 값 입력
        x->info = c;
        x->l = z;
        x->r = z;
        if (c == '+' || c == '*') {  //연산자가 나오면 팝 노드 연결
            x->r = stack.pop();
            x->l = stack.pop();
        }
        stack.push(x);  //숫자면 푸시
    }

    levelOrderTraverse(x);  //함수 실행
    clear(x);               //노드들 모두 동적할당 해제
    delete z;               //마지막 노드 동적할당 해제
}
