#include <iostream>
#include <algorithm>

using namespace std;

//12865
int k, w[101], v[101], n;
int dp[101][100001];
int main() {

	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
	}

	for (int i = 1; i <= n; i++) { //물건 갯수
		for (int j = 1; j <= k; j++) { //무게
			if (j >= w[i])//무게가 들어갈 물건 무게 보다 크면
				//비교 안넣었을때 vs 같은 무게 빼고 지금 꺼 넣은 거
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}

	cout << dp[n][k];
}


/*
4 7

6 13
4 8
3 6
5 12
*/