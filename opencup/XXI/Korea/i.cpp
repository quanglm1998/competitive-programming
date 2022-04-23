#include <bits/stdc++.h>

using namespace std;

const int N = 250010;
const int LOG = 20;

int n;
vector<int> adj[N];
int sz[N], lv[N], par[N];
int in[N], out[N], cnt;
int HLDLs[N], top[N];
int anc[LOG][N];

void dfsInit(int u, int p) {
    lv[u] = lv[p] + 1;
    sz[u] = 1;
    par[u] = p;
    anc[0][u] = p;
    for (int i = 1; i < LOG; i++) {
        anc[i][u] = anc[i - 1][anc[i - 1][u]];
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsInit(v, u);
        sz[u] += sz[v];
    }
}

void dfsBuildHLD(int u, int p, int last) {
    top[u] = last;
    in[u] = ++cnt;
    HLDLs[cnt] = u;
    int mainChild = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!mainChild || sz[mainChild] < sz[v]) mainChild = v;
    }
    if (mainChild) dfsBuildHLD(mainChild, u, last);
    for (int v : adj[u]) {
        if (v == p || v == mainChild) continue;
        dfsBuildHLD(v, u, v);
    }
    out[u] = cnt;
}

/*
    Complete Node
    Change default values to WORST
    Change SegmentTree.init
*/
struct Node {
    long long sum, lazy;

    Node() {
        sum = lazy = 0;
    }

    template<typename T>
    void apply(int l, int r, const T &val) {
        lazy += val;
        sum += 1ll * (r - l + 1) * val;
    }

    void pull(const Node &u, const Node &v) {
        sum = u.sum + v.sum;
    }

    void push(int l, int r, Node &u, Node &v) {
        u.lazy += lazy;
        v.lazy += lazy;
        int m = l + r >> 1;
        u.sum += 1ll * (m - l + 1) * lazy;
        v.sum += 1ll * (r - m) * lazy;
        lazy = 0;
    }
};

struct SegmentTree {
    void init(int node, int l, int r) {
        if (l == r) {
            t[node].apply(l, r, 0); // <-- change this
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
    
    SegmentTree(int n = 1) : n(n) {
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

    int find(int node, int l, int r, long long delta) {
        assert(delta <= t[node].sum);
        if (l == r) return l;
        int m = l + r >> 1;
        t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
        if (t[node << 1].sum < delta) return find(node << 1 | 1, m + 1, r, delta - t[node << 1].sum);
        return find(node << 1, l, m, delta);
    }
} st;

void updateByHLD(int u, int v) {
    while (top[u] != top[v]) {
        if (lv[top[u]] < lv[top[v]]) swap(u, v);
        st.update(1, 1, n, in[top[u]], in[u], +1);
        u = par[top[u]];
    }
    if (lv[u] < lv[v]) swap(u, v);
    st.update(1, 1, n, in[v], in[u], +1);
}

int get(int u, long long tot) {
    if (st.get(1, 1, n, in[u], out[u]).sum * 2 > tot) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        int v = anc[i][u];
        if (!v) continue;
        if (st.get(1, 1, n, in[v], out[v]).sum * 2 <= tot) u = v;
    }
    return par[u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfsInit(1, 0);
    dfsBuildHLD(1, 0, 1);
    st = SegmentTree(n);
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u;
            cin >> u;
            st.update(1, 1, n, in[u], out[u], +1);
        } else {
            int u, v;
            cin >> u >> v;
            updateByHLD(u, v);
        }
        int id = st.find(1, 1, n, (st.t[1].sum + 1) / 2);
        cout << get(HLDLs[id], st.t[1].sum) << '\n';
    }
    return 0;
}