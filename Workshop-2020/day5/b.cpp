#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> root;
    vector<int> sz;
    vector<pair<int, int>> rank;
    vector<int> cntSize;
    vector<vector<int>> best;

    DSU(int n) : root(n + 1, 0), sz(n + 1, 1), rank(n + 1, {1, n}), cntSize(n + 1, n) {
        best.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            best[i].push_back(i);
        }
    }

    int getRoot(int u) {
        return root[u] ? getRoot(root[u]) : u;
    }

    bool unite(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap(u, v);
        root[v] = u;
        sz[u] += sz[v];
        if (rank[u] != rank[v]) {
            if (rank[u] < rank[v]) {
                rank[u] = rank[v];
                best[u].swap(best[v]);
            }
        } else {
            if (best[u].size() < best[v].size()) best[u].swap(best[v]);
            best[u].insert(best[u].end(), best[v].begin(), best[v].end());
        }
        return 1;
    }
};

struct Edge {
    int u, v, s;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0) break;
        vector<Edge> e(m);
        for (auto &u : e) {
            cin >> u.u >> u.v >> u.s;
        }
        sort(e.begin(), e.end(), [&](Edge &u, Edge &v) {
            return u.s > v.s;
        });
        DSU dsu(n);
        for (int l = 0, r = 0; l < m; l = r) {
            while (r < m && e[r].s == e[l].s) r++;
            vector<int> lsNode;
            for (int i = l; i < r; i++) {
                if (dsu.unite(e[i].u, e[i].v)) lsNode.push_back(e[i].u);
            }
            vector<int> ls;
            for (int u : lsNode) {
                ls.push_back(dsu.getRoot(u));
            }

            auto cmp = [&](int u, int v) {
                if (dsu.rank[u] != dsu.rank[v]) return dsu.rank[u] > dsu.rank[v];
                return dsu.sz[u] > dsu.sz[v];
            };

            sort(ls.begin(), ls.end(), cmp);
            ls.resize(unique(ls.begin(), ls.end(), cmp) - ls.begin());

            for (int ll = 0, rr = 0; ll < ls.size(); ll = rr) {
                while (rr < ls.size() && cmp(ls[ll], ls[rr]) == 0) rr++;
                int sz = dsu.sz[ls[ll]];
                for (int i = ll; i < rr; i++) {
                    dsu.rank[ls[i]] = {sz, dsu.cntSize[sz]};
                }
                dsu.cntSize[sz]--;
            }
        }
        int root = dsu.getRoot(1);
        sort(dsu.best[root].begin(), dsu.best[root].end());
        for (int u : dsu.best[root]) cout << u << ' ';
            cout << '\n';
    }
    return 0;
}