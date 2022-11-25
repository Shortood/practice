#include <iostream>
//20 30 * 45 3 / + 10 * 9 -
using namespace std;

template <typename itemType>
class Stack2
{
public:
    Stack2()
    {// 헤드와 z포인터 초기화
        head = NULL;
        z = NULL;
    }
    ~Stack2()
    {//헤드와 z포인터 초기화
        head = NULL;
        z = NULL;
    }//이미 전부 팝 되었으므로 delete X
    void push(int v) //푸시
    {
        if (empty()) //만약 비어있다면
        { //헤드 추가
            head = new node;
            head->key = v;
            head->next = NULL;
        }
        else//아니라면 새 노드 추가후 새 노드를 헤드로 해준다
        {
            z = new node;
            z->key = v;
            z->next = head;
            head = z;
        }
    }

    int pop() //팝
    {
        z = head; //z는 헤드
        int tmp = z->key; //z의 키값을 보관
        head = head->next; //헤드를 다음 노드로 옮겨준다
        delete z; //노드 삭제
        return tmp; //삭제한 노드 값 리턴
    }
    int empty() //head가 없다면 비어있다
    {
        return (head == NULL);
    }

private:
    struct node
    {
        itemType key; //키값
        struct node *next; //다음 노드를 가리킴
    };
    struct node *head, *z; //헤드 포인터와 임시 포인터
};

int main()
{
    char c; //받아오는 값을 저장
    Stack2<int> acc;//클래스 객체 생성
    int x;//받아오는 수 저장
    while ((c = cin.get()) != '\n') //\n가 아닐동안 한 단어씩 받아옴
    {
        x = 0; //x 초기화
        while (c == ' ')//띄어쓰기라면 한 번더 받는다
            cin.get(c);
        if (c == '+') //+라면
            x = acc.pop() + acc.pop();
        if (c == '*') //*라면
            x = acc.pop() * acc.pop();
        if (c == '-') //-라면
        { //나중에 팝되는 수에서 먼저 팝되는 수를 빼야함
            int first = acc.pop(), second = acc.pop();
            x = second - first;
        }
        if (c == '/')
        {//나중에 팝되는 수에서 먼저 팝되는 수를 나눠야함
            int first = acc.pop(), second = acc.pop();
            x = second / first;
        }

        while (c >= '0' && c <= '9') //수를 전부 받을 때까지
        {
            x = 10 * x + (c - '0');
            cin.get(c);
        }
        acc.push(x); //수 푸시
    }
    cout << acc.pop() << '\n'; //결과 팝
}
// 6135