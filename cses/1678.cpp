#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
vector<int> adj[N];
int used[N];
int dead[N];
int par[N];

void dfs(int u) {
    used[u] = 1;
    for (int v : adj[u]) {
        if (!used[v]) {
            par[v] = u;
            dfs(v);
        } else {
            if (dead[v]) continue;
            int cur = u;
            vector<int> res(1, cur);
            while (cur != v) {
                cur = par[cur];
                res.push_back(cur);
            }
            res.push_back(u);
            reverse(res.begin(), res.end());
            cout << res.size() << '\n';
            for (int u : res) cout << u << ' ';
                cout << '\n';
            exit(0);
        }
    }
    dead[u] = 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}