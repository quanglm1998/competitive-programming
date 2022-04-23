#include <bits/stdc++.h>

using namespace std;

const int N = 250010;
const long long INF = 1e13;

int n, k;
vector<pair<int, int>> adj[N];
pair<long long, int> dp[2][N], f[N];

pair<long long, int> operator + (const pair<long long, int> &x, const pair<long long, int> &y) {
    return {x.first + y.first, x.second + y.second};
}

pair<long long, int> operator - (const pair<long long, int> &x, const pair<long long, int> &y) {
    return {x.first - y.first, x.second - y.second};
}

void dfs(int u, int p, long long cost) {
    dp[0][u] = dp[1][u] = {0, 0};
    pair<long long, int> best(-INF * N, -1);
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dfs(v, u, cost);
        dp[0][u] = dp[0][u] + f[v];
        pair<long long, int> now = dp[0][v];
        now.first += w + cost;
        now.second++;
        best = max(best, now - f[v]);
    }
    if (best.second != -1) {
        dp[1][u] = dp[0][u] + best;
    } else dp[1][u] = {-INF * N, 0};
    f[u] = max(dp[0][u], dp[1][u]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    long long low = -1e13, high = 1e13;
    while (high - low > 1) {
        long long mid = (low + high) / 2;
        dfs(1, 0, mid);
        if (f[1].second >= k) high = mid;
        else low = mid;
    }
    dfs(1, 0, high);
    if (f[1].second < k) cout << "Impossible\n";
    else cout << f[1].first - 1ll * k * high << '\n';
    return 0;
}