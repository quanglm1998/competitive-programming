#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, k;
vector<int> adj[N];
int isGood[N];
int sz[N];
int res = 0;

void dfs(int u, int p) {
    sz[u] = isGood[u];
    int f = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] == k) f = 1;
    }
    if (sz[u] == 0) f = 1;
    if (isGood[u]) res++;
    else {
        if (!f) res++;   
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= k; i++) {
        int u;
        cin >> u;
        isGood[u] = 1;
    }
    dfs(1, 0);
    cout << res << endl;
    return 0;
}