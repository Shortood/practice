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

	for (int i = 1; i <= n; i++) { //���� ����
		for (int j = 1; j <= k; j++) { //����
			if (j >= w[i])//���԰� �� ���� ���� ���� ũ��
				//�� �ȳ־����� vs ���� ���� ���� ���� �� ���� ��
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