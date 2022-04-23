#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n, m;
vector<int> adj[N];

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
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int res = 0;
  for (int i = 1; i <= n; i++) {
    int num_edges = 0;
    DSU dsu(n);
    int f = 0;
    for (int j = i; j <= n && !f; j++) {
      for (auto u : adj[j]) {
        if (u >= i && u < j) {
          num_edges++;
          if (!dsu.unite(u, j)) {
            f = 1;
            break;
          }
        }
      }
      res += !f && num_edges == j - i;
    }
  }
  cout << res << endl;
  return 0;
}