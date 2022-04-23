#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;
const int LOG = 20;
const long long INF = 1e18;

vector<int> divs[N];

int n;
int a[N];
vector<pair<int, int>> adj[N];
long long res = 0;
int numChildren[N];
int isDead[N];

long long len[N];
long long maxLen[N];

int getCentroid(int u, int p, int sz) {
    numChildren[u] = 1;
    int flag = 0;
    for (auto [v, dist] : adj[u]) {
        if (v == p || isDead[v]) continue;
        int now = getCentroid(v, u, sz);
        numChildren[u] += numChildren[v];
        if (now) return now;
        if (numChildren[v] * 2 > sz) flag = 1;
    }
    if ((sz - numChildren[u]) * 2 > sz) flag = 1;
    if (!flag) return u;
    return 0;
}

void dfsInit(int u, int p) {
    for (int div : divs[a[u]]) {
        maxLen[div] = -INF;
    }
    numChildren[u] = 1;
    for (auto [v, dist] : adj[u]) {
        if (v == p || isDead[v]) continue;
        len[v] = len[u] + dist;
        dfsInit(v, u);
        numChildren[u] += numChildren[v];
    }
}

void dfsGet(int u, int p) {
    for (int div : divs[a[u]]) {
        if (maxLen[div] >= 0) {
            res = max(res, 1ll * div * (maxLen[div] + len[u]));
        }
    }
    for (auto [v, w] : adj[u]) {
        if (v == p || isDead[v]) continue;
        dfsGet(v, u);
    }
}

void dfsSet(int u, int p) {
    for (int div : divs[a[u]]) {
        maxLen[div] = max(maxLen[div], len[u]);
    }
    for (auto [v, w] : adj[u]) {
        if (v == p || isDead[v]) continue;
        dfsSet(v, u);
    }
}


void solve(int u, int sz) {
    u = getCentroid(u, 0, sz);
    len[u] = 0;
    dfsInit(u, 0);

    for (int div : divs[a[u]]) {
        maxLen[div] = 0;
    }

    for (int i = 0; i < adj[u].size(); i++) {
        auto [v, dist] = adj[u][i];
        if (isDead[v]) continue;
        dfsGet(v, u);
        dfsSet(v, u);
    }
    isDead[u] = 1;
    for (auto [v, dist] : adj[u]) {
        if (isDead[v]) continue;
        solve(v, numChildren[v]);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    for (int i = 0; i < N; i++) maxLen[i] = -INF;

    while (1) {
        cin >> n;
        if (!n) break;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        solve(1, n);
        cout << res << '\n';

        // reset
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            isDead[i] = 0;
        }
        res = 0;
    }
    return 0;
}