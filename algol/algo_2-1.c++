#include <iostream>

using namespace std;
// 20 30 * 45 3 * + 10 * 9 +
template <typename itemType> //템플릿 형식 사용
class Stack1
{
private:
    itemType *stack;
    int p;

public:
    Stack1(int max = 100)
    {
        stack = new itemType[max]; //배열 동적할당
        p = 0; //p초기화
    }
    ~Stack1() { delete stack; } 
    inline void push(int v)
    {
        stack[p++] = v; //값을 넣고 p증가
    }
    inline itemType pop()
    {
        return stack[--p]; //p값을 뺀 후 값 리턴
    }
    inline int empty()
    {
        return !p; //p가 0이면 비었다는 뜻
    }
};

int main()
{
    char c; //받아오는 값을 저장
    Stack1<int> acc(50); //클래스 객체 생성
    int x; //받아오는 수 저장
    while ((c = cin.get()) != '\n') //\n가 아닐동안 한 단어씩 받아옴
    {
        x = 0; //x 초기화
        while (c == ' ') //띄어쓰기라면 한 번더 받는다
            cin.get(c);
        if (c == '+') //+라면
            x = acc.pop() + acc.pop();
        if (c == '*')  //*라면
            x = acc.pop() * acc.pop();

        while (c >= '0' && c <= '9') //수를 전부 받을 때까지
        {
            x = 10 * x + (c - '0');
            cin.get(c);
        }
        acc.push(x); //수 푸시
    }
    cout << acc.pop() << '\n';
}