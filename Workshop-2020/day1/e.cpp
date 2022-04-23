#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m, k;
set<int> adj[N], revAdj[N];
int isDead[N];
set<pair<pair<int, int>, int>> s;
int used[N];

void erase(int u, int v) {
    if (v > m) s.erase({{revAdj[v].size(), adj[v].size()}, -v});
    revAdj[v].erase(u);
    if (v > m) s.insert({{revAdj[v].size(), adj[v].size()}, -v});
}

void add(int u, int v) {
    if (u == v) return;
    if (v > m) s.erase({{revAdj[v].size(), adj[v].size()}, -v});
    revAdj[v].insert(u);
    if (v > m) s.insert({{revAdj[v].size(), adj[v].size()}, -v});
    if (u > m) s.erase({{revAdj[u].size(), adj[u].size()}, -u});
    adj[u].insert(v);
    if (u > m) s.insert({{revAdj[u].size(), adj[u].size()}, -u});
}

void dfs(int u) {
    used[u] = 1;
    for (int v : adj[u]) {
        if (!used[v]) dfs(v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        if (u != v) {
            adj[u].insert(v);
            revAdj[v].insert(u);
        }
    }
    for (int i = 1; i <= m; i++) {
        if (!used[i]) dfs(i);
    }
    for (int i = m + 1; i <= n; i++) {
        s.insert({{revAdj[i].size(), adj[i].size()}, -i});
    }
    while (!s.empty()) {
        auto u  = s.begin()->second;
        auto deg = s.begin()->first.first;
        if (deg >= 2) break;
        s.erase(s.begin());
        u = -u;
        int p = -1;
        if (deg == 1) p = *revAdj[u].begin();
        for (int v : adj[u]) {
            erase(u, v);
            if (p != -1) add(p, v);
        }
        adj[u].clear();
    }
    int res = m;
    for (auto u : s) {
        if (used[-u.second]) res++;
    }
    cout << res << endl;
    return 0;   
}