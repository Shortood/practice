#include <iostream>
#include <queue>
#include <vector>

using namespace std;


class info {
public:
	int bluex, bluey, redx, redy;
	int count;
};

info start;
char mi[10][10];
int mi2[10][10] = { 0, };

int bfs() {
	queue<info> q;
	q.push(start);

	return 0;
}


int main() {
	int n, m;

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mi[i][j];
			if (mi[i][j] == 'B') { start.bluex = i; start.bluey = j; }
			else if (mi[i][j] == 'R') { start.redx = i; start.redy = j; }
		}
	}
	start.count = 0;
}