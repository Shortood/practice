#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

template <typename itemType>
class List
{
public:
    List()
    { //헤드 포인터 초기화
        head = NULL;
        z = NULL;
    }
    ~List()
    { //메모리 초기화
        while (!empty())
        {
            z = head;
            head = head->next;
            delete z;
        }
    }
    void insert(int v) //노드 추가
    {
        if (empty()) //첫 노드 추가
        {
            head = new node;
            head->key = v;
            head->next = NULL;
            head->prior = NULL;
        }
        else
        {
            z = head;
            node *newnode = new node; //노드 생성
            newnode->key = v;         //키 삽입
            if (head->next == NULL)   //노드가 헤드하나만 있는 경우
            {
                head->next = newnode;
                head->prior = newnode; // head의 prior은 항상 마지막 노드를 가리킴
                newnode->prior = head;
                newnode->next = NULL;
                if (head->key > newnode->key) //만약 삽입될 노드의 키값이 더 작다면 바꿔준다
                {
                    int temp = newnode->key;
                    newnode->key = head->key;
                    head->key = temp;
                }
            }
            else
            { //노드가 두개이상 있을 경우

                if (v > head->key) //삽입할 값이 제일 작은 경우가 아닐 경우
                {
                    z = head;
                    while (z != NULL)
                    {
                        if (z->key < v)
                            z = z->next;
                        else
                            break;
                    }
                    if (z != NULL)
                    { //삽입될 위치가 맨뒤가 아니라면
                        z->prior->next = newnode;
                        newnode->prior = z->prior;
                        z->prior = newnode;
                        newnode->next = z;
                    }
                    else
                    {                    //맨뒤 삽입
                        z = head->prior; //마지막 노드를 가리키도록
                        z->next = newnode;
                        head->prior = newnode;
                        newnode->prior = z;
                        newnode->next = NULL;
                    }
                }
                else
                { //제일 앞에 삽입되는 경우
                    newnode->prior = head->prior;
                    head->prior = newnode;
                    newnode->next = head;
                    head = newnode;
                }
            }
        }
    }
    bool compare(int x) //이미 같은 수가 존재하는지 확인
    {
        z = head;
        while (z != NULL)
        {
            if (z->key == x) //찾았다면 true 리턴
                return true;
            if (z->key > x) //찾는 수가 z의 키값보다 커진다면 없다는 뜻
                return 0;
            z = z->next;
        }
        return 0;
    }

    int empty()
    {
        return (head == NULL);
    }

    void print() //출력
    {
        z = head;
        while (z != NULL)
        {
            cout << z->key << " ";
            z = z->next;
        }
        cout << endl;
    }

private:
    struct node
    {
        itemType key;
        struct node *next, *prior; //더블 링크드 리스트
    };
    struct node *head, *z;
};

int main()
{
    int m, n, x;
    srand(time(NULL));
    clock_t start, end;

    start = clock();
    List<int> a;     // a집단
    List<int> b;     // b집단
    List<int> uni;   //합집합
    List<int> inter; //교집합
    cin >> m >> n;

    for (int i = 0; i < m; i++)
    {
        x = rand() % m + 1; // 1부터 m까지 랜덤을 생성
        // cout << "insert a " << x << endl;
        a.insert(x); // a리스트에 x추가

        if (!uni.compare(x))
        { //만약 합집합 리스트에 x값이 없다면
            // cout << "insert uni " << x << endl;
            uni.insert(x); //합집합 리스트에 추가
        }
    }

    for (int i = 0; i < n; i++)
    {
        x = rand() % n + 1;
        // cout << "insert b " << x << endl;
        b.insert(x); // b 리스트에 추가

        if (!uni.compare(x))
        { //만약 합집합 리스트에 x값이 없다면
            // cout << "insert uni " << x << endl;
            uni.insert(x); //합집합 리스트에 추가
        }

        if (a.compare(x) && !inter.compare(x))
        { // a에 같은 값이 존재하고 교집합 리스트에 추가되어 있지 않은 값이라면
            // cout << "insert inter " << x << endl;
            inter.insert(x); //교집합 리스트에 추가
        }
    }
    //리스트 값 출력
    end = clock();
    /*
    cout << "A = ";
    a.print();
    cout << "B = ";
    b.print();
    cout << "U = ";
    uni.print();
    cout << "X = ";
    inter.print();
*/
    cout << "time =" << (double)(end - start) / CLOCKS_PER_SEC << endl;
}
