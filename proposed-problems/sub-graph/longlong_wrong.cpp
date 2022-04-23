#include <bits/stdc++.h>

using namespace std;

const int N = 250010;
const int INF = 1e9;

int n, m;
vector<int> adj[N];
int f[N], g[N];

struct DSU {
    vector<int> root;
    vector<int> sz;

    vector<pair<int, int>> changed;

    DSU(int n = 0) : root(n + 1, 0), sz(n + 1, 1) {}

    int getRoot(int u) {
        while (root[u]) u = root[u];
        return u;
    }

    bool unite(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap(u, v);
        changed.push_back({u, v});
        root[v] = u;
        sz[u] += sz[v];
        return 1;   
    }

    void rollback(int k) {
        while (changed.size() > k) {
            auto u = changed.back(); changed.pop_back();
            sz[u.first] -= sz[u.second];
            root[u.second] = 0;
        }
    }
} dsu;

void solve(int l, int r, int optL, int optR) {
    if (l > r) return;
    int tBegin = dsu.changed.size();
    int m = l + r >> 1;
    for (int i = min(r, optL); i >= m; i--) {
        for (int j : adj[i]) {
            if (i < j && j <= optL) {
                assert(dsu.unite(i, j));
            }
        }
    }
    int tMid = dsu.changed.size();
    int optM = -1;
    for (int i = max(m, optL + 1); i <= optR && optM == -1; i++) {
        for (int j : adj[i]) {
            if (m <= j && j < i) {
                if (!dsu.unite(i, j)) {
                    optM = i - 1;
                    break;
                }
            }
        }
    }
    if (optM == -1) optM = optR;
    f[m] = optM;
    dsu.rollback(tMid);

    solve(l, m - 1, optL, optM);
    dsu.rollback(tBegin);

    for (int i = max(r + 1, optL + 1); i <= optM; i++) {
        for (int j : adj[i]) {
            if (r + 1 <= j && j < i) {
                if (!dsu.unite(i, j)) {
                    optM = i - 1;
                    break;
                }
            }
        }
    }
    solve(m + 1, r, optM, optR);
    dsu.rollback(tBegin);
}

int deg[N];

/*
    Complete Node,
    Change default values to WORST
    Change SegmentTree.init
*/
struct Node {
    int minVal, lazy, cnt;

    Node() {
        minVal = INF;
        lazy = 0;
        cnt = 1;
    }

    template<typename T>
    void apply(int l, int r, const T &val) {
        minVal += val;
        lazy += val;
    }

    void pull(const Node &u, const Node &v) {
        minVal = min(u.minVal, v.minVal);
        cnt = 0;
        if (minVal == u.minVal) cnt += u.cnt;
        if (minVal == v.minVal) cnt += v.cnt;
    }

    void push(int l, int r, Node &u, Node &v) {
        u.lazy += lazy;
        v.lazy += lazy;
        u.minVal += lazy;
        v.minVal += lazy;
        lazy = 0;
    }   
};

struct SegmentTree {
    void init(int node, int l, int r) {
        if (l == r) {
            t[node].apply(l, r, l - INF); // <-- change this
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        t[node].pull(t[node << 1], t[node << 1 | 1]);
    }

    /*------------------------------------------------------------------*/
    int n;
    vector<Node> t;
    
    SegmentTree(int n) : n(n) {
        t.assign(n << 2 | 1, {});
        init(1, 1, n);
    }

    template<typename T>
    void update(int node, int l, int r, int x, int y, const T &val) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            t[node].apply(l, r, val);
            return;
        }
        int m = l + r >> 1;
        t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
        update(node << 1, l, m, x, y, val);
        update(node << 1 | 1, m + 1, r, x, y, val);
        t[node].pull(t[node << 1], t[node << 1 | 1]);
    }

    Node get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return Node();
        if (x <= l && r <= y) return t[node];
        int m = l + r >> 1;
        t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
        Node p1 = get(node << 1, l, m, x, y);
        Node p2 = get(node << 1 | 1, m + 1, r, x, y);
        Node res;
        res.pull(p1, p2);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    // n = 250000;
    // m = n - 1;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        // u = i;
        // v = n;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());
    dsu = DSU(n);
    solve(1, n, 1, n);

    fill(g + 1, g + n + 1, n);

    // for (int i = 1; i <= n; i++) {
    //     g[i] = max(g[i - 1], i);
    //     while (g[i] < n) {
    //         int lower = lower_bound(adj[g[i] + 1].begin(), adj[g[i] + 1].end(), i) - adj[g[i] + 1].begin();
    //         int upper = upper_bound(adj[g[i] + 1].begin(), adj[g[i] + 1].end(), g[i]) - adj[g[i] + 1].begin();
    //         if (upper - lower > 2) break;
    //         int f = 0;
    //         for (int j = lower; j < upper; j++) {
    //             int u = adj[g[i] + 1][j];
    //             if (deg[u] == 2) {
    //                 f = 1;
    //                 break;
    //             }
    //         }
    //         if (f) break;
    //         for (int j = lower; j < upper; j++) {
    //             int u = adj[g[i] + 1][j];
    //             deg[u]++;
    //         }
    //         deg[g[i] + 1] = upper - lower;
    //         g[i]++;
    //     }

    //     deg[i] = 0;
    //     for (int u : adj[i]) {
    //         if (i < u && u <= g[i]) {
    //             deg[u]--;   
    //         }
    //     }
    // }
    
    SegmentTree st(n);

    int res = 0;
    for (int i = n; i; i--) {
        for (int j : adj[i]) {
            if (j > i) {
                st.update(1, 1, n, j, n, -1);
            }
        }
        Node now = st.get(1, 1, n, i, min(f[i], g[i]));
        if (now.minVal == i) res += now.cnt;
    }
    cout << res << endl;
    return 0;
}