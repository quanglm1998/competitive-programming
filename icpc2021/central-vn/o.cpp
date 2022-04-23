#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  a--, b--;
  string s;
  cin >> s;
  vector<vector<int>> adj(n);
  vector<vector<int>> rev_adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
  }
  int x, y, k;
  cin >> x >> y >> k;
  for (int i = 0; i < k; i++) {
    int t, u, v, p, q;
    cin >> t >> u >> v >> p >> q;
  }

  k %= 2;
  vector<int> g(n), rev_g(n);

  auto GenG = [&](const vector<vector<int>> &adj, const vector<vector<int>> &rev_adj, vector<int> &g) {
    queue<int> q;
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
      deg[i] = adj[i].size();
      if (!deg[i]) {
        q.push(i);
      }
    }
    while (!q.empty()) {
      auto u = q.front();
      q.pop();
      if (adj[u].empty()) {
        g[u] = k;
      } else {
        set<int> s;
        for (auto v : adj[u]) {
          s.insert(g[v]);
        }
        g[u] = 0;
        while (s.count(g[u])) g[u]++;
      }
      for (auto v : rev_adj[u]) {
        deg[v]--;
        if (!deg[v]) {
          q.push(v);
        }
      }
    }
  };

  GenG(adj, rev_adj, g);
  GenG(adj, rev_adj, rev_g);
  if (g[a] == rev_g[b]) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}