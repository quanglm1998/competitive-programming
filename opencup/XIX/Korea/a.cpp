#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, c, q;
vector<int> adj[N];
int HLDList[N], in[N], out[N], cnt, top[N];
int lv[N], numChild[N], par[N];

int numRoad[N];
int numColor[N];

void dfsInit(int u, int p) {
    lv[u] = lv[p] + 1;
    numChild[u] = 1;
    par[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsInit(v, u);
        numChild[u] += numChild[v];
    }
}

void dfsBuildHLD(int u, int p, int last) {
    top[u] = last;
    in[u] = ++cnt;
    HLDList[cnt] = u;
    int best = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (best == -1 || numChild[best] < numChild[v]) best = v;
    }
    if (best != -1) dfsBuildHLD(best, u, last);
    for (int v : adj[u]) {
        if (v == p || v == best) continue;
        dfsBuildHLD(v, u, v);
    }
    out[u] = cnt;
}

struct ST {
    int minVal[N << 2], maxVal[N << 2];
    int lazy[N << 2];

    void pull(int node) {
        minVal[node] = min(minVal[node << 1], minVal[node << 1 | 1]);
        maxVal[node] = max(maxVal[node << 1], maxVal[node << 1 | 1]);
    }

    void push(int node) {
        if (lazy[node] == -1) return;
        minVal[node << 1] = maxVal[node << 1] = lazy[node << 1] = lazy[node];
        minVal[node << 1 | 1] = maxVal[node << 1 | 1] = lazy[node << 1 | 1] = lazy[node];
        lazy[node] = -1;
    }

    void init(int node, int l, int r) {
        lazy[node] = -1;
        if (l == r) {
            minVal[node] = maxVal[node] = l == 1 ? c + 1 : 0;
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        pull(node);
    }

    void update(int node, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            minVal[node] = maxVal[node] = lazy[node] = val;
            return;
        }
        int m = l + r >> 1;
        push(node);
        update(node << 1, l, m, x, y, val);
        update(node << 1 | 1, m + 1, r, x, y, val);
        pull(node);
    }

    int get(int node, int l, int r, int x) {
        if (l == r) return minVal[node];
        int m = l + r >> 1;
        push(node);
        if (x <= m) return get(node << 1, l, m, x);
        return get(node << 1 | 1, m + 1, r, x);
    }

    int find(int node, int l, int r, int x, int y, int color) {
        if (x > r || y < l) return -1;
        if (x <= l && r <= y) {
            if (minVal[node] == color && maxVal[node] == color) return -1;
            if (l == r) return l;
        }
        int m = l + r >> 1;
        push(node);
        int res = find(node << 1 | 1, m + 1, r, x, y, color);
        if (res != -1) return res;
        return find(node << 1, l, m, x, y, color);
    }
} st;

void update(int u, int delta) {
    if (!u) return;
    numColor[numRoad[u]]--;
    numRoad[u] += delta;
    numColor[numRoad[u]]++;
}

void solve(int u, int color) {
    while (u != 1) {
        int v = top[u];
        int c = st.get(1, 1, n, in[u]);
        int id = st.find(1, 1, n, in[v], in[u], c);
        // cout << u << ' ' << v << ' ' << in[v] << ' ' << id << ' ' << c << endl;
        
        if (id == -1) id = in[v];
        else id++;

        int num = in[u] - id + 1;
        update(c, -num);
        update(color, +num);
        st.update(1, 1, n, id, in[u], color);
        if (id == in[v]) u = par[v];
        else {
            id--;
            u = HLDList[id];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> c >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    numColor[0] = c;
    dfsInit(1, 0);
    dfsBuildHLD(1, 0, 1);
    st.init(1, 1, n);
    while (q--) {
        int u, c, m;
        cin >> u >> c >> m;
        solve(u, c);
        cout << numColor[m] << '\n';
    }
    return 0;
}