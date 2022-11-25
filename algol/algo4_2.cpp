#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int max_v, min_v, n, cnt = 0;
double mid_v;

template <typename itemType>
inline void swap(itemType a[], int i, int j)  //자료 바꾸기
{
    itemType t = a[i];
    a[i] = a[j];
    a[j] = t;
}

template <typename itemType>
int partition(itemType a[], int l, int r) {
    int i, j;
    itemType v;  //키 값
    cnt++;       // r>l 비교
    if (r > l) {
        v = a[l];   //가장 왼쪽 값을 키값으로
        i = l;      // i의 초기값을 가장 왼쪽 인덱스로 설정
        j = r + 1;  // j의 초기값을 제일 오른쪽 인덱스에서 한 칸 옆으로 설정
        for (;;) {
            while (i + 1 < n && a[++i] < v)  //키 값보다 큰 값을 찾는다
                cnt++;
            while (a[--j] > v)  //키 값보다 작은 값을 찾는다
                cnt++;
            if (i >= j) break;  //두 위치가 바뀌면 모든 값을 보았다
            swap(a, i, j);
        }
    }
    swap(a, j, l);
    return j;
}

template <typename itemType>
void select(itemType a[], int l, int r, int k) {
    int j;
    if (r > l) {
        j = partition(a, l, r);
        cnt += 3;                                               // if문 비교
        if (j > l + k - 1) select(a, l, j - 1, k);              //키 값이 찾는 위치보다 크다면 왼쪽을 본다
        if (j < l + k - 1) select(a, j + 1, r, k - j + l - 1);  //키 값이 찾는 위치보다 작다면 오른쪽을 본다
        if (j == l + k - 1) {                                   //위치를 찾았다면
            mid_v = a[j];                                       //미드 값 저장
            // cout << "mid " << mid_v << endl;
        }
    } else if (r == l) {  // r과 l값이 같으면 그 위치가 중간 위치
        mid_v = a[l];     //중간값 저장
        cnt++;            //중간값 확인
    }
}

int main() {
    int *a;
    int small, large;
    srand(time(NULL));
    cin >> n;

    a = new int[n];

    for (int i = 0; i < n; i++) {
        a[i] = rand() % n + 1;
        // cout << a[i] << " ";
    }

    select(a, 0, n - 1, n / 2);  //중앙 값 찾기

    min_v = a[0];  //최소값과 최대값에 미리 0번째 값 넣어놓기
    max_v = a[0];

    for (int i = 1; i < n - 1; i += 2) {  //최대 최소 한번에 구하기
        if (a[i] < a[i + 1]) {            //두 수중 작은 값을 small
            small = a[i];                 //큰 값을 large에 넣는다
            large = a[i + 1];
        } else {
            small = a[i + 1];
            large = a[i];
        }
        if (small < min_v) min_v = small;  //현재 최소값보다 작으면 바꾼다
        if (large > max_v) max_v = large;  //현재 최대값보다 크면 바꾼다
    }

    // for (int i = 0; i < n; i++) {
    //    cout << a[i] << " ";
    //}
    cout << endl;
    cout << min_v << " " << mid_v << " " << max_v << endl;  //출력
    cout << "cnt = " << cnt << endl;
}