#include <iostream>

using namespace std;

struct node *x, *z;  //노드

struct node {
    char info;           //값
    struct node *l, *r;  //노드 포인터
};

template <typename itemType>
class Queue {
   private:
    itemType *queue;       //포인트를 이용한 배열 생성
    int tail, size, head;  //끝부분, 크기, 앞부분

   public:
    Queue(int max = 100) {
        queue = new itemType[max];  //배열 동적 할당
        tail = 0;                   //끝부분과, 앞부분 초기화
        head = 0;
        size = max;  //사이즈 설정
    }
    ~Queue() {
        delete queue;  //동적할당 해제
    }
    inline void put(itemType v) {   //삽입
        queue[tail++] = v;          //뒷부분에 노드 삽입
        if (tail > size) tail = 0;  //만약 뒷부분이 배열 크기를 벗어나면 제일 앞으로 간다
    }
    inline itemType get() {  //앞부분 노드를 리턴
        itemType t = queue[head++];
        if (head > size) head = 0;  //만약 앞부분이 배열 크기를 벗어나면 앞으로 간다
        return t;
    }
    inline int empty() {  //비어있는지 확인
        return head == tail;
    }
};

Queue<node *> queue(50);  //큐 객체 생성

void visit(node *t) {  //값 출력
    cout << t->info << " ";
}

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
    itemType *stack;
    int p;

   public:
    Stack(int max = 100) {
        stack = new itemType[max];  //배열 동적할당
        p = 0;
    }
    ~Stack() {
        delete stack;  //동적할당 해제
    }
    inline void push(itemType v) {  //푸시
        stack[p++] = v;             //현재 들어갈 위치에 노드 삽입
    }
    inline itemType pop() {  //나와야 할 위치의 노드 팝
        return stack[--p];
    }
    inline int empty() {  //비어있는지 확인
        return !p;
    }
};

int main() {
    char c;
    Stack<node *> stack(50);  //객체 생성
    z = new node;             //노드 동적할당
    z->l = z;                 //범위를 확인하기 위한 노드 생성
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
    levelOrderTraverse(x);  //함수 호출
}
