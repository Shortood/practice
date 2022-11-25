#include <cstring>
#include <iostream>

using namespace std;

int b_index[1000] = {0};
int cnt;
string text = "A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN STING";
string pattern = "STING";
//string text = "AAAAAAAAAAAAAAAAAAAAAAAA";  //최악
//string pattern = "AAAAAAAAAB";
int brutesearch(string p, string a) {
    int i = 0, j = 0, M = p.length(), N = a.length();
    int b_cnt = 0;  //일치하는 패턴의 수
    cnt = 0;        //비교연산
    while (i <= N) {
        cnt++;
        if (a[i] != p[j]) {  //같지 않으면 다시 이전으로 돌아간다
            i -= j;
            j = -1;
        }
        if (j == M - 1) {  //일치하는 패턴을 찾았다면 저장
            b_index[b_cnt++] = i - M + 1;
            i -= j;
            j = -1;
        }
        i++, j++;  //다음 문자
    }
    return b_cnt;  //일치하는 문자 갯수
}
int SP[1000], kmp_index[1000] = {0};  // sp, 일치하는 문자 저장
int kmp_cnt = 0;                      //일치하는 문자 수

void initSP(string p) {
    int i, j, M = p.length();
    SP[0] = -1;
    for (i = 0, j = -1; i < M; i++, j++, SP[i] = j) {  //접두부 테이블
        while ((j >= 0) && (p[i] != p[j])) {           // suffix와 prefix 비교
            j = SP[j];
        }
    }
}

int kmpsearch(string p, string a) {
    int i, j, M = p.length(), N = a.length();
    cnt = 0;
    initSP(p);  //테이블 만들기

    for (i = 0, j = 0; j < M && i < N; i++, j++) {
        cnt++;                                //문자 비교 회수
        while ((j >= 0) && (a[i] != p[j])) {  //문자가 다르다면 테이블에 값에 맞게 j값을 건너뜀
            j = SP[j];
        }
        // cout << endl;
        if (j == M - 1) {  //일치하는 값을 찾았다면
            // cout << "find" << j << " " << M << endl;
            j = SP[j];                         // j를 테이블을 이용해 건너뜀
            kmp_index[kmp_cnt++] = i - M + 1;  //위치 저장, 갯수 증가
        }
    }
    return kmp_cnt;  //일치하는 문자 갯수 리턴
}

const int q = 33554393;
const int d = 32;
int rb_cnt = 0, rb_index[1000] = {0};  //일치하는 문자 수, 문자 저장

int index(char a) {  //아스키코드 리턴
    return (int)(a);
}

int rksearch(string p, string a) {
    cnt = 0;
    int i, dM = 1, h1 = 0, h2 = 0;
    int M = p.length(), N = a.length();         //문자 길이
    for (i = 1; i < M; i++) dM = (d * dM) % q;  //문자 길이만큼 32를 곱해줌
    for (i = 0; i < M; i++) {
        h1 = (h1 * d + index(p[i])) % q;  //문자열을 인덱스로 저장
        h2 = (h2 * d + index(a[i])) % q;  //문자열을 인덱스로 저장
    }

    for (i = 0; i <= N - M; i++) {
        if (h1 == h2) {  //문자열 값이 같다면
            rb_index[rb_cnt++] = i;
        }
        h2 = (h2 + d * q - index(a[i]) * dM) % q;  //제일 앞 한자리를 빼준다
        h2 = (h2 * d + index(a[i + M])) % q;       //다음 수를 더한다
        cnt++;
    }
    return rb_cnt;  // 갯수 리턴
}

int main() {
    int c = brutesearch(pattern, text);  // brute 실행
    if (c) {
        for (int i = 0; i < c; i++)  //일치하는 위치 출력
            cout << b_index[i] << " ";
        cout << endl;
    } else
        cout << "Cant find at brutesearch" << endl;
    cout << cnt << endl;  //비교회수 출력

    if (int k = kmpsearch(pattern, text)) {  // kmp 실행
        for (int i = 0; i < k; i++)          //일치하는 위치 출력
            cout << kmp_index[i] << " ";
        cout << endl;
    } else
        cout << "Cant find at kmp" << endl;

    cout << cnt << endl;  //비교회수 출력

    if (int r = rksearch(pattern, text)) {  // rk 실행
        for (int i = 0; i < r; i++)         //일치하는 위치 출력
            cout << rb_index[i] << " ";
        cout << endl;
    } else
        cout << "Cant find at rksearch" << endl;
    cout << cnt << endl;  //비교회수 출력
}