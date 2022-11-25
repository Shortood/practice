#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int b_index[10001][2] = {
    0,
};
int cnt;
string a[100][100];
string p[10][10];
void stringinit() {  //문자열 입력
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            a[i][j] = 'A';

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            p[i][j] = 'A';
    p[9][9] = 'B';
}

int brutesearch(string p[10][10], string a[100][100]) {
    int i = 0, j = 0, k = 0, z = 0;
    int b_cnt = 0;  //일치하는 패턴의 수
    cnt = 0;        //비교연산
    while (i <= 99 && j <= 99) {
        cnt++;
        // cout << "ij " << i << " " << j << " " << k << " " << z << endl;
        if (a[i][j] != p[k][z]) {  //같지 않으면 다시 이전으로 돌아간다
            i -= k;
            j -= z;
            z = -1;
            k = 0;
        }
        if (k == 9 && z == 9) {  //일치하는 패턴을 찾았다면 저장
            // cout << "같음" << i << " " << j << endl;
            b_index[b_cnt][0] = i - k;
            b_index[b_cnt++][1] = j - z;
            i -= k;
            j -= z;
            z = -1;
            k = 0;
        }
        j++;
        z++;
        if (j > 99) {  //다음줄로
            i++;
            j = 0;
            k = 0;
            z = 0;
        }
        if (z > 9) {  //다음 줄로
            j -= z;
            i++;
            k++;
            z = 0;
        }
    }
    return b_cnt;
}

int SP[100][100] = {
    0,
},
    kmp_index[1000][2] = {
        //
        0,
};

void initSP(string p[10][10]) {
    int i, j, k;
    for (int i = 0; i < 10; i++) {
        SP[i][0] = -1;
    }

    for (k = 0; k < 10; k++) {  // sp테이블을 2차원 배열로 저장
        for (i = 0, j = -1; i < 10; i++, j++, SP[k][i] = j) {
            while ((j >= 0) && (p[k][i] != p[k][j])) {
                j = SP[k][j];
            }
        }
    }
}
//일치하는 문자열 위치 저장
int check[10][100] = {
    0,
};

int kmp_cnt = 0, kmp_cnt2 = 0;  //일치하는 수 저장

int kmpsearch(string p[10][10], string a[100][100]) {
    int k = 0, i = 0, z = 0, j = 0, q = 0;
    cnt = 0;
    initSP(p);
    while (k < 90) {
        for (q = 0; q < 10; q++) {  // 10줄 비교
            for (i = 0, j = 0; j < 10 && i < 100; i++, j++) {
                cnt++;
                while ((j >= 0) && (a[k + q][i] != p[q][j])) {  //문자가 다르다면 테이블에 값에 맞게 j값을 건너뜀
                    j = SP[q][j];
                }
                if (j == 9) {             //문자열이 일치한다면
                    check[q][i - 9] = 1;  // check 배열에 저장
                    j = SP[q][j];         // j값을 건너뜀
                }
            }
        }

        for (int i = 0; i <= 90; i++) {           // check 배열 확인
            if (check[0][i] == 1) {               //일치하는 문자열을 확인했다면
                for (j = 1; j < 10; j++) {        //아래 9줄을 추가로 확인
                    if (check[j][i] != 1) break;  //다른것이 있다면 break
                }
                if (j == 10) {  //모두 같다면 위치 저장
                    kmp_index[kmp_cnt][0] = k;
                    kmp_index[kmp_cnt][1] = i;
                    kmp_cnt++;
                }
            }
        }
        k++;
        kmp_cnt2 += kmp_cnt;  //일치하는 문자열 수 저장
        kmp_cnt = 0;
    }
    return kmp_cnt2;  //일치하는 문자열 수 리턴
}

const int q = 33554393;
const int d = 32;
int rb_cnt = 0, rb_index[10000][2] = {
                    0,
};

int index(string a) {  //아스키코드 리턴
    return (int)(a[0]);
}

bool rkcheck(int h1[100], int h2[100], int k) {  //위 아래 10줄이 모두 일치하는지 확인
    for (int i = 0; i < 10; i++) {
        if (h1[i] != h2[k + i]) {  //틀린 문자를 만나면
            return false;          // false 리턴
        }
    }
    return true;
}

int rksearch(string p[10][10], string a[100][100]) {
    cnt = 0;
    int i, j, dM = 1, h1[10] = {0}, h2[100] = {0};
    int M = 10, N = 100;
    for (i = 1; i < M; i++) dM = (d * dM) % q;  //문자 길이만큼 32를 곱해줌

    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            h1[i] = (h1[i] * d + index(p[i][j])) % q;  // 10개의 문자열에 각각 인덱스 저장
        }
    }

    for (i = 0; i < N; i++) {  // a배열의 10줄도 저장
        for (j = 0; j < M; j++) {
            h2[i] = (h2[i] * d + index(a[i][j])) % q;
        }
    }

    for (i = 0; i < N - M; i++) {
        for (j = 0; j <= N - M; j++) {
            if (rkcheck(h1, h2, i)) {     //문자열 인덱스가 같은지 확인
                rb_index[rb_cnt][0] = i;  //같다면 정보 저장
                rb_index[rb_cnt++][1] = j;
            }
            // cout << "ij " << i << " " << j << endl;
            h2[j] = (h2[j] + d * q - index(a[i][j]) * dM) % q;  //앞 한자리를 빼준다
            h2[j] = (h2[j] * d + index(a[i][j + M])) % q;       //뒤 한자리를 더해준다
            cnt++;
        }
    }
    return rb_cnt;  //일치하는 수 리턴
}

int main() {
    stringinit();

    int c = brutesearch(p, a);
    if (c) {                         //일치하는 문자열이 있다면
        for (int i = 0; i < c; i++)  //위치 출력
            cout << b_index[i][0] << " " << b_index[i][1] << endl;
        cout << c << endl;  //갯수 출력
    } else
        cout << "Cant find at brutesearch" << endl;
    cout << cnt << endl;  //비교회수 출력

    cout << "-------" << endl;

    if (int k = kmpsearch(p, a)) {   //일치하는 문자열이 있다면
        for (int i = 0; i < k; i++)  //위치 출력
            cout << kmp_index[i][0] << " " << kmp_index[i][1] << endl;
        cout << endl;
        cout << k << endl;  //갯수 출력
    } else
        cout << "Cant find at kmp" << endl;

    cout << cnt << endl;  //비교회수 출력

    cout << "-------" << endl;
    if (int r = rksearch(p, a)) {    //일치하는 문자열이 있다면
        for (int i = 0; i < r; i++)  //위치 출력
            cout << rb_index[i][0] << " " << rb_index[i][1] << endl;
        cout << r << endl;  //갯수 출력
    } else
        cout << "Cant find at rksearch" << endl;
    cout << cnt << endl;  //비교회수 출력
}