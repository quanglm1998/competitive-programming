#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

template<typename T>
struct Tree {
    int n;
    vector<vector<pair<int, T>>> adj;
    vector<int> posIn;
    vector<int> posOut;
    vector<int> sz;
    vector<int> lv;
    vector<T> dist;
    vector<vector<int>> par;
    vector<int> order;

    double f[N], g[N];

    Tree(int n = -1) : n(n) {
        adj.assign(n + 1, vector<pair<int, T>>());
        posIn.assign(n + 1, 0);
        posOut.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        lv.assign(n + 1, 0);
        dist.assign(n + 1, 0);
        if (n > 0) par.assign((int)log2(n) + 1, vector<int>(n + 1, 0));
        order.assign(1, 0);
    }

    void addEdge(int u, int v, T cost = 1) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }

    void dfs(int u, int p, int a, int b) {
        f[u] = g[u] = 1.0 / n;
        posIn[u] = order.size();
        order.push_back(u);
        sz[u] = 1;
        lv[u] = lv[p] + 1;
        par[0][u] = p;
        for (int i = 1; i < par.size(); i++) par[i][u] = par[i - 1][par[i - 1][u]];

        for (auto e : adj[u]) {
            int v = e.first;
            T cost = e.second;
            if (v == p) continue;
            dist[v] = dist[u] + cost;
            dfs(v, u, a, b);
            sz[u] += sz[v];
        }

        int foo = getPar(u, a);
        if (foo) f[foo] += f[u];
        foo = getPar(u, b);
        if (foo) g[foo] += g[u];

        posOut[u] = order.size();
    }

    int getPar(int u, int k) {
        for (int i = 0; i < par.size(); i++) {
            if (k >> i & 1) u = par[i][u];
        }
        return u;
    }

    int getLCA(int u, int v) {
        if (lv[u] < lv[v]) swap(u, v);
        u = getPar(u, lv[u] - lv[v]);
        if (u == v) return u;
        for (int i = (int)par.size() - 1; i >= 0; i--) {
            if (par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return par[0][u];
    }

    // find k-th node in path from u to v
    // k = 0 returns u
    // returns -1 if invalid
    int getNodeFromPath(int u, int v, int k) {
        if (k < 0) return -1;
        int w = getLCA(u, v);
        int hu = lv[u] - lv[w];
        if (k <= hu) return getPar(u, k);
        k -= hu;
        int hv = lv[v] - lv[w];
        if (k > hv) return -1;
        return getPar(v, hv - k);
    }

    // true if u is v's ancestor
    bool isAncestor(int u, int v) {
        return posIn[u] <= posIn[v] && posOut[v] <= posOut[u];
    }

    double getRes() {
        double res = 0;
        for (int i = 1; i <= n; i++) {
            res += 1.0 - (1.0 - f[i]) * (1.0 - g[i]);
        }
        return res;
    }
};

void solve(int test) {
    cout << "Case #" << test << ": ";
    int n;
    cin >> n;
    Tree<int> t(n);
    int a, b;
    cin >> a >> b;
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        t.addEdge(i, u);
    }
    t.dfs(1, 0, a, b);
    cout << fixed << setprecision(10) << t.getRes() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}