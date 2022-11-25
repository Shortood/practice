#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

template <typename itemType>
class Stack
{
public:
    Stack()
    { // 헤드와 z포인터 초기화
        head = NULL;
        z = NULL;
    }
    ~Stack()
    { //헤드와 z포인터 초기화
        if (head != NULL)
        {
            while (head != NULL)
            {
                z = head;
                head = head->next;
                delete z;
            }
        }
        z = NULL;
    }                //이미 전부 팝 되었으므로 delete X
    void push(int v) //푸시
    {
        if (empty()) //만약 비어있다면
        {            //헤드 추가
            head = new node;
            head->key = v;
            head->next = NULL;
        }
        else //아니라면 새 노드 추가후 새 노드를 헤드로 해준다
        {
            z = new node;
            z->key = v;
            z->next = head;
            head = z;
        }
    }
    int gettop() //팝되는 값 리턴
    {
        return head->key;
    }
    int pop() //팝
    {
        z = head;          // z는 헤드
        int tmp = z->key;  // z의 키값을 보관
        head = head->next; //헤드를 다음 노드로 옮겨준다
        delete z;          //노드 삭제
        return tmp;        //삭제한 노드 값 리턴
    }
    int empty() // head가 없다면 비어있다
    {
        return (head == NULL);
    }

private:
    struct node
    {
        itemType key;      //키값
        struct node *next; //다음 노드를 가리킴
    };
    struct node *head, *z; //헤드 포인터와 임시 포인터
};

template <typename itemType>
class Tree
{
private:
    struct node
    {
        ~node() //메모리 초기화
        {
            if (this->left != NULL)
                delete this->left;
            if (this->right != NULL)
                delete this->right;
        }
        itemType key;
        struct node *left, *right;
    };
    struct node *head, *z;

public:
    Tree()
    { //헤드 포인터 초기화
        head = NULL;
        z = NULL;
    }
    ~Tree()
    { //메모리 초기화
        if (this->head != NULL)
            delete head;
    }

    void insertItem(int v) //트리 노드 추가
    {
        if (empty()) //노드가 하나도 없다면
        {
            head = new node; //헤드에 바로 만든다
            head->left = NULL;
            head->right = NULL;
            head->key = v;
        }
        else
            insert(head, v);
    }

    void insert(node *&tree, int v) //포인터 참조를 이용해 노드 추가
    {

        if (tree == NULL) //노드를 추가할 위치가 비어있다면
        {
            tree = new node; //추가한다
            tree->key = v;
            tree->left = NULL;
            tree->right = NULL;
        }

        if (tree->key == v) //만약 이미 값이 있다면 함수는 중복되어선 안된다
        {                   //추가하지 않는다
        }
        else if (v < tree->key) //들어올 값이 작다면 왼쪽에 노드 추가
            insert(tree->left, v);
        else //크다면 오른쪽에 노드 추가
            insert(tree->right, v);
    }

    void getStack(Stack<int> &stk) //스택을 추가
    {
        if (!empty()) //노드가 하나라도 있다면
            getStack(head, stk);
    }

    void getStack(node *tree, Stack<int> &stk) //참조를 통해 값을 바로 넣는다
    {
        if (tree != NULL) //재귀를 이용 큰 수부터 넣는다
        {
            getStack(tree->right, stk);
            stk.push(tree->key);
            getStack(tree->left, stk);
        }
    }

    int empty()
    {
        return (head == NULL);
    }
};

int main()
{
    int m, n, x;
    srand(time(NULL));

    Tree<int> a; // a집단
    Tree<int> b; // b집단

    cin >> m >> n;
    cout << "insert a ";
    for (int i = 0; i < m; i++)
    {
        x = rand() % m + 1; // 1부터 m까지 랜덤을 생성
        cout << x << " ";
        a.insertItem(x); // a리스트에 x추가
    }
    cout << endl
         << "insert b ";
    for (int i = 0; i < n; i++)
    {
        x = rand() % n + 1;
        cout << x << " ";
        b.insertItem(x); // b 리스트에 추가
    }
    cout << endl;
    Stack<int> stka; // a 집합을 보관하는 스택
    Stack<int> stkb; // b 집합을 보관하는 스택
    //합집합
    a.getStack(stka);                      // a스택에 a트리의 값들을 푸시한다
    b.getStack(stkb);                      // b스택에 b트리의 값들을 푸시한다
    cout << "Union" << endl;               //합집합
    while (!stka.empty() || !stkb.empty()) //두 스택에 값이 있을 동안
    {
        if (stka.gettop() == stkb.gettop()) //두 값이 같다면
        {                                   //하나만 출력
            cout << stka.pop() << " ";
            stkb.pop();
        }
        else if (stka.gettop() < stkb.gettop()) // a보다 b값이 크다면
            cout << stka.pop() << " ";          // a 값만 출력
        else
            cout << stkb.pop() << " "; // b값만 출력

        if (stka.empty() && !stkb.empty()) // b 스택만 값이 남았을 때
        {
            while (!stkb.empty()) // b 스택 전부 팝
            {
                cout << stkb.pop() << " ";
            }
        }
        else if (stkb.empty() && !stka.empty()) // a 스택만 값이 남았을때
        {
            while (!stka.empty()) // a 스택 전부 팝
            {
                cout << stka.pop() << " ";
            }
        }
    }
    cout << endl
         << "inter" << endl; //교집합
    a.getStack(stka);        // a스택에 a트리의 값들을 푸시한다
    b.getStack(stkb);        // b스택에 b트리의 값들을 푸시한다

    while (!stka.empty() && !stkb.empty()) //하나라도 비면 그만 둔다
    {
        if (stka.gettop() == stkb.gettop()) //두 값이 갔다면 교집합이므로 출력
        {
            cout << stka.pop() << " ";
            stkb.pop();
        }
        else if (stka.gettop() > stkb.gettop()) // b스택의 값이 더 작다면
        {                                       // b 스택만 팝
            stkb.pop();
        }
        else //아니면 a 스택만 팝
            stka.pop();
    }
    cout << endl;
}
