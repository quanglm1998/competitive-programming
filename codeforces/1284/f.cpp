#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n;
vector<int> adj[N];
pair<int, int> b[N];
int lsHLD[N], posInHLD[N], numChild[N], top[N], cntHLD = 0;
int lv[N], par[N];

void dfsInit(int u, int p) {
    par[u] = p;
    numChild[u] = 1;
    lv[u] = lv[p] + 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsInit(v, u);
        numChild[u] += numChild[v];
    }
}

void dfsBuildHLD(int u, int last, int p) {
    cntHLD++;
    lsHLD[cntHLD] = u;
    posInHLD[u] = cntHLD;
    top[u] = last;
    int biggest = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (biggest == -1 || numChild[v] > numChild[biggest]) biggest = v;
    }
    if (biggest != -1) {
        dfsBuildHLD(biggest, last, u);
    }
    for (int v : adj[u]) {
        if (v == p || v == biggest) continue;
        dfsBuildHLD(v, v, u);
    }
}

struct IT {
    set<int> t[N << 2];
    pair<int, int> smallest[N << 2];
    void init(int node, int l, int r) {
        smallest[node] = {0, l};
        if (l < r) {
            int m = l + r >> 1;
            init(node << 1, l, m);
            init(node << 1 | 1, m + 1, r);
        }
    }
    void add(int node, int l, int r, int x, int y, int id) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            t[node].insert(id);
            smallest[node].first++;
            return;
        }
        int m = l + r >> 1;
        add(node << 1, l, m, x, y, id);
        add(node << 1 | 1, m + 1, r, x, y, id);
        smallest[node] = min(smallest[node << 1], smallest[node << 1 | 1]);
        smallest[node].first += t[node].size();
    }

    void erase(int node, int l, int r, int x, int y, int id) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            t[node].erase(id);
            smallest[node].first--;
            return;
        }
        int m = l + r >> 1;
        erase(node << 1, l, m, x, y, id);
        erase(node << 1 | 1, m + 1, r, x, y, id);
        smallest[node] = min(smallest[node << 1], smallest[node << 1 | 1]);
        smallest[node].first += t[node].size();
    }

    pair<int, int> getSmallest() {
        return smallest[1];
    }

    int getId(int node, int l, int r, int x) {
        if (x > r || x < l) return -1;
        if (!t[node].empty()) return *t[node].begin();
        if (l < r) {
            int m = l + r >> 1;
            int p1 = getId(node << 1, l, m, x);
            if (p1 != -1) return p1;
            return getId(node << 1 | 1, m + 1, r, x);
        }
        return -1;
    }

    void addVal(int node, int l, int r, int x) {
        if (x > r || x < l) return;
        if (l == r) {
            smallest[node].first = 1e9;
            return;
        }        
        int m = l + r >> 1;
        addVal(node << 1, l, m, x);
        addVal(node << 1 | 1, m + 1, r, x);
        smallest[node] = min(smallest[node << 1], smallest[node << 1 | 1]);
        smallest[node].first += t[node].size();
    }
} t;

void update(int u, int v, int id) {
    while (top[u] != top[v]) {
        if (lv[top[u]] < lv[top[v]]) swap(u, v);
        t.add(1, 1, n, posInHLD[top[u]], posInHLD[u], id);
        u = par[top[u]];
    }
    if (lv[u] < lv[v]) swap(u, v);
    t.add(1, 1, n, posInHLD[v] + 1, posInHLD[u], id);
}

void remove(int u, int v, int id) {
    while (top[u] != top[v]) {
        if (lv[top[u]] < lv[top[v]]) swap(u, v);
        t.erase(1, 1, n, posInHLD[top[u]], posInHLD[u], id);
        u = par[top[u]];
    }
    if (lv[u] < lv[v]) swap(u, v);
    t.erase(1, 1, n, posInHLD[v] + 1, posInHLD[u], id);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i < n; i++) {
        cin >> b[i].first >> b[i].second;
    }
    dfsInit(1, 0);
    dfsBuildHLD(1, 1, 0);
    t.init(1, 1, n);
    for (int i = 1; i < n; i++) {
        update(b[i].first, b[i].second, i);
    }
    t.addVal(1, 1, n, posInHLD[1]);
    vector<tuple<int, int, int, int>> res;
    for (int i = 1; i < n; i++) {
        int smallest = t.getSmallest().second;
        int id = t.getId(1, 1, n, smallest);
        t.addVal(1, 1, n, smallest);
        if (id != -1)  {
            remove(b[id].first, b[id].second, id);
            res.push_back({lsHLD[smallest], par[lsHLD[smallest]], b[id].first, b[id].second});
        }
    }
    cout << res.size() << '\n';
    for (auto u : res) {
        int x, y, xx, yy;
        tie(x, y, xx, yy) = u;
        cout << x << ' ' << y << ' ' << xx << ' ' << yy << '\n';
    }
    return 0;
}