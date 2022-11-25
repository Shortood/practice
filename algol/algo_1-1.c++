#include <iostream>

using namespace std;

class InputNum {
public:
    InputNum() {//수 입력 
        cout << "Enter number";
        cin >> _num;
    }

    int GetValue() const { return _num; } //수 리턴
    void SubtractInput() //입력 받았던 수에서 새로 입력받은 수 빼기
    {
        InputNum aNum; // get a number from user //새로운 수 입력받기
        _num = _num - aNum.GetValue();
    }
private:
    int _num;
};

int main()
{
    InputNum num;
    cout << "The value is " << num.GetValue() << endl; //입력받은 수 출력
    num.SubtractInput(); //빼기
    cout << "Now the value is " << num.GetValue() << endl; //뺀 수 출력
}