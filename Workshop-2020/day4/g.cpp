#include <bits/stdc++.h>

using namespace std;

const int N = 2000010;
const int LOG = 22;

int n, m;
pair<int, int> e[N];
vector<int> adj[N];
int lv[N];
int par[LOG][N];
bool choose[N];
int isColored[N];
int nxt[N];

struct DSU {
    vector<int> root;

    DSU(int n) : root(n + 1, 0) {}

    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }

    bool unite(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        return 1;
    }
};
 
void dfs(int u, int p) {
    lv[u] = lv[p] + 1;
    par[0][u] = p;
    for (int i = 1; i < LOG; i++) {
        par[i][u] = par[i - 1][par[i - 1][u]];
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

int getNxt(int u) {
    if (isColored[u]) return nxt[u] = getNxt(nxt[u]);
    return u;
}

int lca(int u, int v) {
    if (lv[u] < lv[v]) swap(u, v);
    int h = lv[u] - lv[v];
    for (int i = 0; i < LOG; i++) {
        if (h >> i & 1) u = par[i][u];
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 1; i <= m; i++) {
        cin >> e[i].first >> e[i].second;
        if (dsu.unite(e[i].first, e[i].second)) {
            adj[e[i].first].push_back(e[i].second);
            adj[e[i].second].push_back(e[i].first);
            choose[i] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!lv[i]) dfs(i, 0);
    }
    for (int i = 1; i <= n; i++) nxt[i] = par[0][i];
    for (int i = 1; i <= m; i++) {
        int res = 0;
        if (choose[i]) {
            // do nothing
        } else {
            res = 1;
            auto solve = [&](int u, int w) {
                while (lv[getNxt(u)] > lv[w]) {
                    u = getNxt(u);
                    isColored[u] = 1;
                    res++;
                }
            };

            int u = e[i].first;
            int v = e[i].second;
            int w = lca(u, v);
            solve(u, w);
            solve(v, w);
        }
        cout << res << endl;
    }
    return 0;
}