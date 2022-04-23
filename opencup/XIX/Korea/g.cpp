#include <bits/stdc++.h>

using namespace std;

const int N = 250010;
const int K = 9;
const long long INF = 1e18;

int n, k;
int w[N];
long long dp[2][3][K + 1][2 * K + 1];

void minimize(long long &u, long long v) {
    u = min(u, v);
}

void init(int u) {
    for (int s = 0; s < 3; s++) {
        for (int j = 0; j <= k; j++) {
            fill(dp[u][s][j], dp[u][s][j] + 2 * k + 1, INF);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    init(0);
    dp[0][1][0][k] = 0;
    int cur = 0;
    for (int i = 1; i <= n; i++, cur ^= 1) {
        init(cur ^ 1);
        for (int j = 0; j <= k; j++) {
            for (int x = 0; x <= 2 * k; x++) {
                // s = 0
                // use itself
                for (int last = 0; last < 3; last++) {
                    minimize(dp[cur ^ 1][0][j][x], dp[cur][last][j][x] + w[i]);
                }
                // use another
                if (x > 0) {
                    for (int last = 0; last < 3; last++) {
                        minimize(dp[cur ^ 1][0][j][x - 1], dp[cur][last][j][x]);
                    }
                }
                // s = 1
                minimize(dp[cur ^ 1][1][j][x], dp[cur][0][j][x]);
                // pay for another
                if (x < 2 * k && j < k) {
                    minimize(dp[cur ^ 1][1][j + 1][x + 1], dp[cur][0][j][x] + w[i]);
                }
                // s = 2
                minimize(dp[cur ^ 1][2][j][x], dp[cur][1][j][x]);
                // pay for another
                if (x < 2 * k && j < k) {
                    minimize(dp[cur ^ 1][2][j + 1][x + 1], dp[cur][1][j][x] + w[i]);
                }
            }
        }
    }
    long long res = INF;
    for (int j = 0; j <= k; j++) {
        res = min(res, dp[cur][0][j][k]);
        res = min(res, dp[cur][1][j][k]);
    }
    cout << res << endl;
    return 0;
}