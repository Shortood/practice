#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//14502
int n, m, wall, virus;
int map[9][9];
int result = 0;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

vector<pair<int, int>> way;
queue<pair<int, int>> q;

int bfs() {
	bool visit[9][9] = { 0, };

	int cnt = virus;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 2) q.push({ i,j });
		}
	}

	while (!q.empty()) {
		int nowx = q.front().first;
		int nowy = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nextx = nowx + dx[i];
			int nexty = nowy + dy[i];
			//범위 벗어남
			if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m)
				continue;
			//방문 안한 길
			if (!visit[nextx][nexty] && map[nextx][nexty] == 0) {
				q.push({ nextx,nexty });
				visit[nextx][nexty] = true;
				cnt++;
			}
		}
	}

	return n * m - (cnt + wall + 3);
}

int main() {
	int ans = 0;

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			switch (map[i][j]) {
			case 0: way.push_back({ i,j }); break; //빈칸 다 저장
			case 1: wall++; break;
			case 2: virus++; break;
			}
		}
	}

	for (int i = 0; i < way.size(); i++) {
		for (int j = i + 1; j < way.size(); j++) {
			for (int k = j + 1; k < way.size(); k++) { //벽세우기
				map[way[i].first][way[i].second] = 1;
				map[way[j].first][way[j].second] = 1;
				map[way[k].first][way[k].second] = 1;

				result=bfs();// 더 큰거 
				if (ans < result) ans = result;

				map[way[i].first][way[i].second] = 0;//복구
				map[way[j].first][way[j].second] = 0;
				map[way[k].first][way[k].second] = 0;
			}
		}
	}
	cout << ans << endl;

}