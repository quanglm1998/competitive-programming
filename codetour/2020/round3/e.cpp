#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1010;
const long long INF = 1e18;

int n, m, t;
int a[N];
vector<pair<int, int>> adj[N];
int dp[N][N];
set<pair<int, pair<int, int>>> s;

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[v].push_back({u, w});
    }
    for (int i = 1; i <= n; i++) {
        fill(dp[i], dp[i] + t + 1, -INF);
    }
    dp[1][0] = 0;
    for (int x = 1; x <= t; x++) {
        for (int u = 1; u <= n; u++) {
            for (auto [v, w] : adj[u]) {
                if (x < w) continue;
                if (dp[v][x - w] < 0) continue;
                if (v == n) continue;
                dp[u][x] = max(dp[u][x], dp[v][x - w] + a[u]);
            }
        }
    }

    int res = -1;
    for (int i = 0; i <= t; i++) {
        if (dp[n][i] != -INF) res = max(res, dp[n][i]);
    }
    if (res == -1) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}