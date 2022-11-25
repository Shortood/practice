#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

template <typename itemType>
inline void swap(itemType a[], int i, int j)  //자료 바꾸기
{
    itemType t = a[i];
    a[i] = a[j];
    a[j] = t;
};

class Node {
   private:
    string str;
    int cnt;

   public:
    Node() : str(""), cnt(0);
    Node(string& str) : str(str), cnt(0){};
    ~Node(){};
    void addCnt() { cnt++; };
    int getCnt() { return cnt; };
};

class Vector {
   private:
    int start, cnt, max;
    Node* array;

   public:
    Vector() : start(0), cnt(0), max(32) {
        array = new Node[max];
    }
    ~Vector() {
        delete[] array;
    }

    void push_back(string& str) {
        if (cnt < max)
            array[cnt++] = 1;
        else {
            max += 32;
            Node* temp_one = new Node[max + 32];
            Node* temp_two = array;

            for (int i = 0; i < cnt; i++) {
                temp_one[i] = temp_two[i];
            }

            array = temp_one;
            delete[] temp_two;
        }
    }

    int* at(int n) {
        if (n < cnt)
            return array + n;
        else
            return NULL;
    };
};

template <typename itemType>
int partition(itemType a[], int l, int r) {
    int i, j;    //교환 할 수 찾고 바꾸기
    itemType v;  //키 값
    cnt++;       // r>l 비교
    if (r > l) {
        v = a[l];                            //제일 왼쪽 값을 키 값으로
        i = l;                               // i의 초기값을 제일 왼쪽 인덱스로 설정
        j = r + 1;                           // j의 초기값을 제일 오른쪽 인덱스에서 한칸 옆으로 설정
        for (;;) {                           //값이 범위를 벗어나지 않도록 함
            while (i + 1 < n && a[++i] < v)  //키 값보다 큰 값을 만날 때까지 i값 증가
                cnt++;                       //비교연산 수 증가
            while (a[--j] > v)               //키 값보다 작은 값을 만날 때까지 i값 증가
                cnt++;                       //비교연산 수 증가
            cnt++;                           // i<=j 비교
            if (i >= j)                      //만약 i가 j보다 커지면 역전했으므로
                break;                       //나간다
            swap(a, i, j);                   // a[i]와 a[j]값을 바꿔준다
            cnt2++;                          // swap 이동 연산
        }
    }
    swap(a, j, l);  //키값과 a[j]값을 바꿔준다.
    cnt2++;         // swap 이동 연산
    return j;       //다음 퀵정렬 기준이 되는 인덱스 리턴
}

template <typename itemType>
void quicksort(itemType a[], int l, int r) {
    int j;
    cnt++;      // r>l 비교
    if (r > l)  //아직 오른쪽 인덱스가 왼쪽 인덱스 보다 오른쪽에 있다면
    {
        j = partition(a, l, r);  //교환할 수 찾기
        quicksort(a, l, j - 1);  //구간 나눠서 퀵정렬 실행
        quicksort(a, j + 1, r);
    }
}

int main() {
    string line, temp;
    ifstream file("datafile.txt");

    Vector vt;
    if (file.is_open()) {
        while (getline(file, line, '\0')) {
            stringstream ss(line);
            while (ss >> temp) {
                // cout << temp << endl;
                vt
            }
        }
    } else
        cout << "Unable to open file";  //파일이 없을때
    file.close();                       //파일을 닫는다.
    map.print();
}