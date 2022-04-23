#include <bits/stdc++.h>

using namespace std;

const int N = 13;

int n, m;
int a[N + 1];
bool hasEdge[N + 1][N + 1];
pair<long long, long long> dp[1 << N][N + 1][N + 1];

int getBit(int mask, int u) {
    u--;
    return mask >> u & 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> q;
    while (q--) {
        memset(dp, 0, sizeof dp);
        memset(hasEdge, 0, sizeof hasEdge);
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            hasEdge[u][v] = hasEdge[v][u] = 1;
        }
        if (n == 1) {
            cout << a[1] << ' ' << 1 << '\n';
            continue;
        }
        for (int i = 1; i <= n; i++) {
            dp[1 << i - 1][i][0] = {a[i], 1};
        }
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 1; u <= n; u++) {
                if (!getBit(mask, u)) continue;
                for (int v = 0; v <= n; v++) {
                    if (v != 0 && !getBit(mask, v)) continue;
                    if (dp[mask][u][v].second == 0) continue;
                    for (int w = 1; w <= n; w++) {
                        if (getBit(mask, w) || !hasEdge[u][w]) continue;
                        long long newCost = dp[mask][u][v].first + a[w] + 1ll * a[w] * a[u];
                        if (v && hasEdge[v][w]) newCost += 1ll * a[w] * a[u] * a[v];
                        long long num = dp[mask][u][v].second;
                        int newMask = mask | (1 << w - 1);
                        if (newCost > dp[newMask][w][u].first) {
                            dp[newMask][w][u] = {newCost, num};
                        } else if (newCost == dp[newMask][w][u].first) {
                            dp[newMask][w][u].second += num;
                        }
                    }
                }
            }
        }

        long long cost = 0;
        long long num = 0;
        int tot = (1 << n) - 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[tot][i][j].first > cost) {
                    tie(cost, num) = dp[tot][i][j];
                } else if (dp[tot][i][j].first == cost) {
                    num += dp[tot][i][j].second;
                }
            }
        }
        cout << cost << ' ' << num / 2 << '\n';
    }
    return 0;
}