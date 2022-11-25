#include <iostream>

using namespace std;

struct node *x, *z;  //노드

struct node {
    char info;           //값
    struct node *l, *r;  //노드 포인터
};

template <typename itemType>
class Stack {
   private:
    itemType *stack;  //포인트를 이용한 배열 생성
    int p;            //현재 들어가거나 나올 위치

   public:
    Stack(int max = 100) {          //생성자
        stack = new itemType[max];  //동적할당
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

void visit(node *t) {  //값 출력
    cout << t->info << " ";
}

void traverse(struct node *t) {  //재귀 사용
    if (t != z) {                //만약 현재 확인하는 노드가 범위를 벗어나지 않았다면
        cout << "(";
        traverse(t->l);  //왼쪽 아래 노드부터 확인
        visit(t);        //출력
        traverse(t->r);  //오른쪽 아래 노드 확인
        cout << ")";
    }
}

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
    traverse(x);  //함수 실행
}
