#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
vector<int> adj[N];
int f[3][N];

void dfs(int u, int p) {
    vector<int> dp(4, N);
    dp[0] = 0;
    int sum = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        vector<int> newDp(4, N);
        for (int mask = 0; mask < 4; mask++) {
            newDp[mask | 2] = min(newDp[mask | 2], dp[mask] + f[0][v]);
            newDp[mask] = min(newDp[mask], dp[mask] + f[1][v]);
            if (!(mask & 1)) newDp[mask | 1] = min(newDp[mask | 1], dp[mask] + f[2][v]);
        }
        sum += min(f[0][v], min(f[1][v], f[2][v]));
        dp = newDp;
        // cout << "! " << u << ' ' << v << endl;
        // for (int i = 0; i < 4; i++) cout << dp[i] << ' ';
        //     cout << endl;
    }
    f[0][u] = dp[2];
    f[1][u] = dp[3];
    f[2][u] = min(dp[0], dp[1]);
    f[0][u] = min(f[0][u], 1 + sum);
    // cout << "# " << u << ' ' << f[0][u] << ' ' << f[1][u] << ' ' << f[2][u] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << min(f[0][1], f[1][1]) << endl;
    return 0;
}