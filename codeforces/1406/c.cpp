#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
vector<int> adj[N];
int sz[N];
int halfPoint;

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    if (sz[u] * 2 == n) halfPoint = u;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        halfPoint = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int leaf = 0;
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() == 1 && !leaf) leaf = i;
        }
        dfs(leaf, 0);
        if (halfPoint) {
            cout << leaf << ' ' << adj[leaf][0] << '\n';
            cout << leaf << ' ' << halfPoint << '\n';
        } else {    
            cout << leaf << ' ' << adj[leaf][0] << '\n';
            cout << leaf << ' ' << adj[leaf][0] << '\n';
        }
    }
    return 0;
}