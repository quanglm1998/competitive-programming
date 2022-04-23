#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;

struct DSU {
    int root[N];
    pair<int, int> bound[N];
    DSU() {
        memset(root, 0, sizeof root);
        for (int i = 0; i < N; i++) bound[i] = {i, i};
    }
    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }
    void unite(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u != v) {
            root[u] = v;
            bound[v].first = min(bound[v].first, bound[u].first);
            bound[v].second = max(bound[v].second, bound[u].second);
        }
    }
    bool isRoot(int u) {
        return !root[u];
    }
} dsu;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        dsu.unite(u, v);
    }
    int res = 0;
    vector<pair<int, int>> ls;
    for (int i = 1; i <= n; i++) {
        if (dsu.isRoot(i)) ls.push_back(dsu.bound[i]);
    }
    sort(ls.begin(), ls.end());
    int mx = 0;
    for (auto u : ls) {
        if (u.first <= mx) res++;
        mx = max(mx, u.second);
    }
    cout << res << endl;
    return 0;
}