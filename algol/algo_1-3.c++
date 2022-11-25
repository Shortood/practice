#include <iostream>

using namespace std;

struct node
{
    int key;
    struct node *next;
};

int main()
{
    int i, N, M;
    struct node *t, *x;
    cin >> N >> M;

    t = new node;
    t->key = 1;
    x = t;
    for (i = 2; i <= N; i++)
    { // i번째 노드의 키 값에 i넣기 N까지
        t->next = new node;
        t = t->next;
        t->key = i;
    }
    t->next = x; //한 바퀴 돌도록 함 t는 마지막
    int cnt = 0; //while loop 수
    while (t != t->next) // 1개 남기 전
    {
        cnt++;
        
        for (i = 1; i < M; i++) // t가 M-1만큼 이동
            t = t->next;
        cout << t->next->key << ' ';
        x = t->next;       // x를 t다음
        t->next = x->next; // t의 다음 값 삭제
        delete x;
    }
    cout << t->key << endl;
    cout << "cnt " << cnt << endl;
}
