#include <ctime>
#include <iostream>
#define MAXINT 10000
using namespace std;
int f_mat[5][5] = {{6, 7, 12, 5}, {5, 3, 11, 18}, {7, 17, 3, 3}, {8, 10, 14, 9}};
int **mat;

int matrixPath(int m, int n) {   //길찾기
    int **t_mat = new int *[m];  //배열 생성
    for (int i = 0; i <= m; i++) {
        t_mat[i] = new int[n];
    }

    for (int i = 0; i <= m; i++)  //테두리에 최대값을 넣어줌
        t_mat[i][0] = MAXINT;
    for (int i = 0; i <= n; i++)
        t_mat[0][i] = MAXINT;

    t_mat[0][1] = 0;
    t_mat[1][0] = 0;
    for (int i = 1; i <= m; i++) {      //동적 프로그래밍 방식을 실행
        for (int j = 1; j <= n; j++) {  //위와 왼쪽 길중 더 작은 값을 더해줌
            // cout << mat[i - 1][j - 1] << " " << t_mat[i - 1][j] << " " << t_mat[i][j - 1] << endl;
            t_mat[i][j] = mat[i - 1][j - 1] + min(t_mat[i - 1][j], t_mat[i][j - 1]);
        }
    }
    return t_mat[n][m];
}

int matrixPath_ex(int m, int n) {  //처음에 주어진 예시의 길 찾기 위 방식과 같음
    int **t_mat = new int *[m];
    for (int i = 0; i <= m; i++) {
        t_mat[i] = new int[n];
    }

    for (int i = 0; i <= m; i++)
        t_mat[i][0] = MAXINT;
    for (int i = 0; i <= n; i++)
        t_mat[0][i] = MAXINT;

    t_mat[0][1] = 0;
    t_mat[1][0] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            t_mat[i][j] = f_mat[i - 1][j - 1] + min(t_mat[i - 1][j], t_mat[i][j - 1]);
        }
    }
    return t_mat[n][m];
}

int main() {
    srand(time(NULL));
    int M, N;

    for (int i = 0; i < 4; i++) {  //행렬 출력
        for (int j = 0; j < 4; j++) {
            cout << f_mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << matrixPath_ex(4, 4) << endl;  //길찾기
    cout << "-------------------" << endl;
    cin >> M >> N;  //행과 열 수 입력
    mat = new int *[M];
    for (int i = 0; i <= M; i++) {  // 베열 생성
        mat[i] = new int[N];
    }

    for (int i = 0; i < M; i++) {  //랜덤값 생성
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 20 + 1;  //수는 20이하로 설정
        }
    }

    for (int i = 0; i < M; i++) {  //행렬 출력
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    cout << matrixPath(M, N) << endl;  //총 값 출력
}