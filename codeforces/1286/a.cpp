#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const int INF = 1e9;

int n;
int a[N];
int dp[2][N][N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                dp[0][i][j][k] = INF;
                dp[1][i][j][k] = INF;
            }
        }
    }
    dp[0][0][0][0] = 0;
    dp[1][0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (a[i + 1] == 0) {
                    dp[0][i + 1][j + 1][k] = min(dp[0][i + 1][j + 1][k], dp[0][i][j][k]);
                    dp[0][i + 1][j + 1][k] = min(dp[0][i + 1][j + 1][k], dp[1][i][j][k] + 1);
                    dp[1][i + 1][j][k + 1] = min(dp[1][i + 1][j][k + 1], dp[0][i][j][k] + 1);
                    dp[1][i + 1][j][k + 1] = min(dp[1][i + 1][j][k + 1], dp[1][i][j][k]);
                } else {
                    if (a[i + 1] & 1) {
                        dp[1][i + 1][j][k + 1] = min(dp[1][i + 1][j][k + 1], dp[0][i][j][k] + 1);
                        dp[1][i + 1][j][k + 1] = min(dp[1][i + 1][j][k + 1], dp[1][i][j][k]);
                    } else {
                        dp[0][i + 1][j + 1][k] = min(dp[0][i + 1][j + 1][k], dp[0][i][j][k]);
                        dp[0][i + 1][j + 1][k] = min(dp[0][i + 1][j + 1][k], dp[1][i][j][k] + 1);
                    }
                }
            }
        }
    }
    int numEven = n / 2;
    cout << min(dp[0][n][numEven][n - numEven], dp[1][n][numEven][n - numEven]) << endl;
    return 0;
}