#include <ctime>
#include <iostream>
#define MAXINT 101
using namespace std;
int cnt = 0, cnt2 = 0, incnt = 0;
int N;
struct point {
    int x, y;     // x, y 값
    float angle;  //수평각
    char c;
    point(int x = 0, int y = 0, char c = ' ') {
        this->x = x;
        this->y = y;
        this->c = c;
    }
};

struct line {
    struct point p1, p2;
};

void Swap(struct point *a, struct point *b) {
    struct point t;
    t = *a;
    *a = *b;
    *b = t;
}

float ComputeAngle(struct point p1, struct point p2) {  //수평각 계산
    cnt++;                                              //수평각 계산 회수
    int dx, dy, ax, ay;                                 // x길이 ,y길이, x길이 절댓값, y길이 절댓값
    float t;                                            //각
    dx = p2.x - p1.x;                                   // x길이
    ax = abs(dx);                                       //절댓값
    dy = p2.y - p1.y;                                   // y길이
    ay = abs(dy);                                       //절댓값
    // cout << "/p1 " << p1.x << " " << p1.y << " " << p1.c << endl;
    // cout << "/p2 " << p2.x << " " << p2.y << " " << p2.c << endl;
    // cout << "ax " << ax << " ay " << ay << endl;
    t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);  // 1사분면 or 같은 위치
    if (dx < 0)
        t = 2 - t;    // 2사분면
    else if (dy < 0)  // 4사분면
        t = 4 + t;
    // cout << "t " << t << endl;
    return t * 90.0;  //각 리턴
}

void insertion(struct point a[], int N) {  //정렬
    int i, j;
    struct point val;
    for (i = 1; i <= N; i++) {
        val = a[i];
        j = i;
        while (a[j - 1].angle > val.angle) {  //각에 따라 정렬
            cnt2++;
            a[j] = a[j - 1];
            j--;
        }
        cnt2++;
        a[j] = val;
    }
}
int Direction(struct point a, struct point b, struct point c) {
    int dxab, dxac, dyab, dyac, dir;
    dxab = b.x - a.x;               // a와 b점의 x차이
    dyab = b.y - a.y;               // a와 b점의 y차이
    dxac = c.x - a.x;               // a와 c점의 x차이
    dyac = c.y - a.y;               // a와 c점의 y차이
    if (dxab * dyac < dyab * dxac)  // ab 기울기 > ac기울기
        dir = 1;
    if (dxab * dyac > dyab * dxac)  // ab 기울기 < ac기울기
        dir = -1;
    if (dxab * dyac == dyab * dxac) {  // ab 기울기 == ac기울기
        if (dxab == 0 && dyab == 0)    // a와 b가 같은 위치
            dir = 0;
        if ((dxab * dxac < 0) || (dyab * dyac < 0))  // a가 b와 c 사이에 위치
            dir = -1;
        else if ((dxab * dxab + dyab * dyab) >= (dxac * dxac + dyac * dyac))  // c가 ab사이에 위치하거나 a나 b와 같이 위치
            dir = 0;
        else
            dir = 1;
    }

    return dir;
}
void FindSimplePolygon(struct point P[], int n) {
    for (int i = 1; i <= n; i++) {  //각각의 수평각 계산
        P[i].angle = ComputeAngle(P[1], P[i]);
    }
    insertion(P, n);  //수평각을 기준으로 정렬
}

int GrahamScan(struct point P[], int n) {
    int i, FirstPoint, NextPoint;
    incnt = 0;
    FirstPoint = 1;
    for (i = 2; i <= n; i++)  //기준점 찾기
        if (P[i].y < P[FirstPoint].y) FirstPoint = i;
    for (i = 1; i < n; i++)
        if (P[i].y == P[FirstPoint].y && P[i].x > P[FirstPoint].x) FirstPoint = i;
    Swap(&P[FirstPoint], &P[1]);    //기준점 첫번째로 옮기기
    FindSimplePolygon(P, n);        //다각형 만들기
    for (int i = 1; i <= n; i++) {  //다각형 출력
        cout << P[i].c << " ";
    }
    cout << endl;
    P[0] = P[n];
    NextPoint = 3;
    for (i = 4; i <= n; i++) {
        while (Direction(P[NextPoint], P[NextPoint - 1], P[i]) <= 0) {  //방향이 시계반대방향이라면
            incnt++;                                                    //내부점 갯수
            NextPoint--;                                                //내부점으로 처리
        }
        NextPoint++;

        Swap(&P[NextPoint], &P[i]);
    }
    return NextPoint;
}

int main() {
    int x, y, result;
    char c;
    srand(time(NULL));

    struct point poly[9];
    poly[0].angle = -1;
    poly[1] = point(3, 4, 'A');
    poly[2] = point(1, 2, 'B');
    poly[3] = point(2, 5, 'C');
    poly[4] = point(2, 6, 'D');
    poly[5] = point(9, 3, 'E');
    poly[6] = point(5, 3, 'F');
    poly[7] = point(6, 4, 'G');
    poly[8] = point(8, 4, 'H');
    result = GrahamScan(poly, 8);
    for (int i = 1; i <= result; i++) {  //다각형 순서대로 출력
        cout << poly[i].c << " ";
    }
    cout << endl;

    cin >> N;
    struct point polygon[N + 2], z;

    for (int i = 1; i <= N; i++) {
        x = rand() % 100;  // x와 y값
        y = rand() % 100;
        c = 'A' + i - 1;  //점 이름
        cout << c << " " << x << " " << y << endl;
        polygon[i] = point(x, y, c);
    }

    polygon[0].angle = -1;  // insertion sort를 위해 가장 작은 값을 넣어준다
    result = GrahamScan(polygon, N);

    for (int i = 1; i <= result; i++) {  //다각형 순서대로 출력
        cout << polygon[i].c << " ";
    }

    cout << endl;
    cout << "수평각 회수 " << cnt << endl;
    cout << "각 비교 회수 " << cnt2 << endl;
    cout << "내부점 수 " << incnt << endl;
}