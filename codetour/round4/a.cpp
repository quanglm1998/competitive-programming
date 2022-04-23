#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 20;

int n;
vector<int> adj[N];
int in[N], out[N], cntEuler;
int par[LOG][N];
int lv[N];

void dfsInit(int u, int p) {
    lv[u] = lv[p] + 1;
    in[u] = ++cntEuler;
    par[0][u] = p;
    for (int i = 1; i < LOG; i++) par[i][u] = par[i - 1][par[i - 1][u]];
    for (int v : adj[u]) {
        dfsInit(v, u);
    }
    out[u] = cntEuler;
}

int getPar(int u, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k >> i & 1) u = par[i][u];
    }
    return u;
}

int lca(int u, int v) {
    if (lv[u] < lv[v]) swap(u, v);
    u = getPar(u, lv[u] - lv[v]);
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int root = -1;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        if (u) adj[u].push_back(i);
        else root = i;
    }
    dfsInit(root, 0);
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        vector<int> ls(k);
        for (int &u : ls) cin >> u;
        sort(ls.begin(), ls.end(), [&](int u, int v) {
            return in[u] < in[v];
        });
        set<int> s;
        for (int i = 0; i < ls.size(); i++) {
            int u = ls[i];
            s.insert(u);
            if (i) {
                int v = ls[i - 1];
                s.insert(lca(u, v));
            }
            if (i + 1 < ls.size()) {
                int v = ls[i + 1];
                s.insert(lca(u, v));
            }
        }
        cout << s.size() << '\n';
    }
    return 0;
}