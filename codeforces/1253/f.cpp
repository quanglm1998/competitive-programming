#include <bits/stdc++.h>

using namespace std;

const int LOG = 20;
const int N = 300010;
const long long INF = 1e18;

int n, m, k, q;
vector<pair<int, int>> adj[N];
long long d[N];
int id[N];
int used[N];
int pos[N];
long long maxVal[LOG][N];
int lg2[N];

struct Edge {
    int u, v;
    long long w;
} edges[N];

struct DSU {
    int root[N];
    list<pair<int, long long>> ls[N];
    DSU() {
        memset(root, 0, sizeof root);
        for (int i = 0; i < N; i++) ls[i].push_back({i, 0ll});
    }
    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u; 
    }
    bool unite(int u, int v, long long d) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        ls[v].back().second = d;
        ls[v].splice(ls[v].end(), ls[u]);
    }       
    bool isRoot(int u) { return root[u] == 0; }
} dsu;

void dijkstra() {
    set<pair<long long, int>> s;
    for (int i = 1; i <= n; i++) {
        if (i <= k) {
            d[i] = 0;
            s.insert({d[i], i});
            id[i] = i;
        } else d[i] = INF;
    }
    while (!s.empty()) {
        int u = s.begin()->second; s.erase(s.begin());
        if (used[u]) continue;
        used[u] = 1;
        for (auto v : adj[u]) {
            if (d[v.first] > d[u] + v.second) {
                d[v.first] = d[u] + v.second;
                id[v.first] = id[u];
                s.insert({d[v.first], v.first});
            }
        }
    }
}

long long getMax(int l, int r) {
    int lg = lg2[r - l + 1];
    return max(maxVal[lg][l], maxVal[lg][r - (1 << lg) + 1]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    lg2[1] = 0;
    for (int i = 2; i < N; i++) lg2[i] = lg2[i >> 1] + 1;
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
    }
    dijkstra();
    vector<Edge> e;
    for (int i = 1; i <= m; i++) {
        if (id[edges[i].u] != id[edges[i].v]) e.push_back({id[edges[i].u], id[edges[i].v], edges[i].w + d[edges[i].u] + d[edges[i].v]});
    }
    sort(e.begin(), e.end(), [&](Edge &u, Edge &v) {
        return u.w < v.w;
    });
    for (auto val : e) {
        dsu.unite(val.u, val.v, val.w);
    }
    int root = -1;
    for (int i = 1; i <= k; i++) if (dsu.isRoot(i)) root = i;
    int cnt = 0;
    for (auto val : dsu.ls[root]) {
        pos[val.first] = ++cnt;
        maxVal[0][cnt] = val.second;
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j + (1 << i) - 1 <= k; j++) {
            maxVal[i][j] = max(maxVal[i - 1][j], maxVal[i - 1][j + (1 << i - 1)]);
        }
    }
    while (q--) {
        int u, v; cin >> u >> v;
        u = pos[u]; v = pos[v];
        if (u > v) swap(u, v);
        cout << getMax(u, v - 1) << '\n';
    }
    return 0;
}