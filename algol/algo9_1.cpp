#include <ctime>
#include <iostream>
#define MAXINT 101
using namespace std;
int cnt = 0, cnt2 = 0;
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

int Intersection(struct line ab, struct line cd) {  //교차 확인
    int linecrossing;
    //조건이 만족된다면
    if ((Direction(ab.p1, ab.p2, cd.p1) * Direction(ab.p1, ab.p2, cd.p2) <= 0) && (Direction(cd.p1, cd.p2, ab.p1) * Direction(cd.p1, cd.p2, ab.p2) <= 0))
        linecrossing = true;  //교차한다
    else
        linecrossing = false;
    return linecrossing;
}

bool IsInsidePoint(struct point poly[], int N, struct point z) {
    int count, i, lastpoint;         //교차하는 수,  이전 점
    int pointontestline;             //점이 검사에 있는지 확인
    struct line testline, polyline;  //검사선, 도형의 변을 연장한 선
    count = 0;
    lastpoint = 1;    // 0번째 칸에는 insertionsort를 위한 값이 들어감
    testline.p1 = z;  //점을 넣어줌
    testline.p2 = z;
    testline.p2.x = MAXINT;         //두번째 점의 x를 연장시킨다
    for (i = 2; i <= N + 1; i++) {  //다각형 위의 모든 점을 확인
        polyline.p1 = polyline.p2 = poly[i];
        //꼭지점이 검사선 상에 있는지 확인한다
        if (Intersection(testline, polyline))
            pointontestline = true;
        else {  //없다면 이전에 확인한 점을 다른 점으로 넣어준다
            polyline.p2 = poly[lastpoint];
            lastpoint = i;                             //이전에 확인한 점을 바꿔준다
            if (!pointontestline) {                    //이전점이 검사선 위에 없었다면
                if (Intersection(polyline, testline))  //선이 교차하는지 확인
                    count++;
            } else {  //있었다면 이전점과 현재점의 방향을 확인
                if (Direction(testline.p1, testline.p2, polyline.p1) *
                        Direction(testline.p1, testline.p2, polyline.p2) <
                    0) {  //서로 반대라면 교차했다고 처리한다
                    count++;
                }
                //다시 초기화
                pointontestline = false;
            }
        }
    }
    return ((count % 2) == 1);  //교차가 홀 수면 교차한다
}

int main() {
    int x, y, miny = 100, checki;
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
    checki = 2;
    for (int i = 1; i <= 8; i++) {  //각각의 수평각 계산
        poly[i].angle = ComputeAngle(poly[checki], poly[i]);
    }
    insertion(poly, 8);             //수평각을 기준으로 정렬
    for (int i = 1; i <= 8; i++) {  //다각형 순서대로 출력
        cout << poly[i].c << " ";
    }

    cout << endl;
    cout << "-----------------" << endl;

    checki = 0;
    cin >> N;
    struct point *polygon = new struct point[N + 2], z;
    for (int i = 1; i <= N; i++) {
        x = rand() % 100;  // x와 y값
        y = rand() % 100;
        c = 'A' + i - 1;  //점 이름
        cout << c << " " << x << " " << y << endl;
        polygon[i] = point(x, y, c);
        if (y < miny) {  // y값이 가장 작은 점을 찾는다
            miny = y;
            checki = i;
        } else if (y == miny && polygon[checki].x > x)  // y값이 같다면 x값이 가장 작은 점을 찾는다
            checki = i;
    }

    polygon[0].angle = -1;          // insertion sort를 위해 가장 작은 값을 넣어준다
    for (int i = 1; i <= N; i++) {  //각각의 수평각 계산
        polygon[i].angle = ComputeAngle(polygon[checki], polygon[i]);
        // cout << polygon[i].c << " " << polygon[i].angle << endl;
    }
    cout << "-----------------" << endl;
    insertion(polygon, N);          //수평각을 기준으로 정렬
    for (int i = 1; i <= N; i++) {  //다각형 순서대로 출력
        cout << polygon[i].c << " ";
    }
    polygon[N + 1] = point(polygon[1].x, polygon[1].y, polygon[1].c);
    cout << endl;
    cout << "수평각 회수 " << cnt << endl;
    cout << "각 비교 회수 " << cnt2 << endl;
    cin >> x >> y;  // z 점 x, y입력
    z = point(x, y, 'z');
    if (IsInsidePoint(poly, N, z))  //위치 출력
        cout << "도형 안에 위치" << endl;
    else
        cout << "도형 밖에 위치" << endl;
}