#include <ctime>
#include <iostream>
#define MAXINT 101

using namespace std;
int N;

struct point {
    int x, y, z;  // x, y, z 값
    char c;
    point(int x = 0, int y = 0, int z = 0, char c = ' ') {
        this->x = x;
        this->y = y;
        this->z = z;
        this->c = c;
    }
};

void Swap(struct point *a, struct point *b) {  //값 바꾸기
    struct point t;
    t = *a;
    *a = *b;
    *b = t;
}

int dist(struct point s[], int p, int q) {  //거리 계산
    return ((s[q].x - s[p].x) * (s[q].x - s[p].x) + (s[q].y - s[p].y) * (s[q].y - s[p].y) + (s[q].z - s[p].z) * (s[q].z - s[p].z));
}
int min(int a, int b, int c) {  //최소값 찾기
    int min;
    if (a < b)
        min = a;
    else
        min = b;
    if (c < min) min = c;
    return min;
}

int partition(struct point a[], int l, int r) {  //퀵정렬
    int i, j;                                    //교환 할 수 찾고 바꾸기
    int v;                                       //키 값
    if (r > l) {
        v = a[l].x;  //제일 왼쪽 값을 키 값으로
        i = l;       // i의 초기값을 제일 왼쪽 인덱스로 설정
        j = r + 1;   // j의 초기값을 제일 오른쪽 인덱스에서 한칸 옆으로 설정
        for (;;) {   //값이 범위를 벗어나지 않도록 함
            while (i + 1 < N && a[++i].x < v)
                ;  //키 값보다 큰 값을 만날 때까지 i값 증가
            while (a[--j].x > v)
                ;                //키 값보다 작은 값을 만날 때까지 i값 증가
            if (i >= j)          //만약 i가 j보다 커지면 역전했으므로
                break;           //나간다
            Swap(&a[i], &a[j]);  // a[i]와 a[j]값을 바꿔준다
        }
    }
    Swap(&a[j], &a[l]);  //키값과 a[j]값을 바꿔준다.
    return j;            //다음 퀵정렬 기준이 되는 인덱스 리턴
}

void quicksort(struct point a[], int l, int r) {  //퀵정렬 x좌표 기준으로 정렬
    int j;
    if (r > l)  //아직 오른쪽 인덱스가 왼쪽 인덱스 보다 오른쪽에 있다면
    {
        j = partition(a, l, r);  //교환할 수 찾기
        quicksort(a, l, j - 1);  //구간 나눠서 퀵정렬 실행
        quicksort(a, j + 1, r);
    }
}
int MergePlusCPP(struct point s[], int low, int mid, int high, int less) {
    int left = s[mid].x - less;       //왼쪽 범위
    int right = s[mid + 1].x - less;  //오른쪽 범위
    int d = less;
    for (int i = 0; i <= mid; i++) {
        if (s[i].x >= left) {  //왼쪽 범위안 점들
            for (int j = mid + 1; j <= high; j++) {
                if (s[j].x <= right)                           //오른쪽 범위에 점이 있다면
                    if (dist(s, i, j) < d) d = dist(s, i, j);  // 거리가 더 작다면 d값을 바꾼다
            }
        }
    }
    return d;
}

int CPP(struct point s[], int low, int high) {
    int mid, dlmin, drmin, dlrmin;
    int less;
    int min1;
    if (low < high - 2) {               //점이 4개 이상이라면
        mid = (low + high) / 2;         //중간
        dlmin = CPP(s, low, mid);       //왼쪽 범위
        drmin = CPP(s, mid + 1, high);  //오른쪽 범위
        if (dlmin < drmin)
            less = dlmin;
        else
            less = drmin;
        dlrmin = MergePlusCPP(s, low, mid, high, less);
        return (min(dlmin, drmin, dist(s, mid, mid + 1)));  //최소값 찾기
    } else if (high - low + 1 == 3)                         //점이 3개일 경우 바로 찾는다
        return min(dist(s, low, low + 1), dist(s, low, low + 2), dist(s, low + 1, low + 2));
    else if (high - low + 1 == 2)  //점이 2개일 경우
        return dist(s, low, low + 1);
    else  //하나일 경우
        return MAXINT;
}

int main() {
    int x, y, z;
    char c;
    srand(time(NULL));

    cin >> N;
    struct point *p = new struct point[N + 1];
    for (int i = 0; i < N; i++) {
        x = rand() % 100;  // x와 y값
        y = rand() % 100;
        z = rand() % 100;
        c = 'A' + i;  //점 이름
        p[i] = point(x, y, z, c);
        cout << c << " " << x << " " << y << " " << z << endl;
    }
    quicksort(p, 0, N - 1);
    /*
        cout << "-------------------------" << endl;

        for (int i = 0; i < N; i++) { //정렬된 결과 출력
            cout << p[i].c << " " << p[i].x << " " << p[i].y << " " << p[i].z << endl;
        }
    */
    cout << "-------------------------" << endl;
    cout << CPP(p, 0, N - 1) << endl;
}