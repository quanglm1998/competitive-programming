#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m, q;
set<int> adj[N];
set<pair<int, int>> queries[N];
pair<int, pair<int, int>> edges[N];
int res[N];
int root[N];

int GetRoot(int u) {
  return root[u] ? root[u] = GetRoot(root[u]) : u;
}

void Unite(int u, int v, int w) { 
  // cout << "unite " << u << ' ' << v << ' ' << w << endl;
  // for (int i = 1; i <= q; i++) cout << res[i] << ' ';
  //   cout << endl;
  // cout << "adj\n";
  // for (int i = 1; i <= n; i++) {
  //   if (GetRoot(i) == i) {
  //     cout << "# " << i << endl;
  //     for (auto u : adj[i]) cout << u << ' ';
  //       cout << endl;
  //   }
  // }
  // cout << "query\n";
  // for (int i = 1; i <= n; i++) {
  //   if (GetRoot(i) == i) {
  //     cout << "# " << i << endl;
  //     for (auto u : queries[i]) cout << u.first << ' ';
  //       cout << endl;
  //   }
  // }
  u = GetRoot(u);
  v = GetRoot(v);
  if (u == v) return;
  adj[u].erase(v);
  adj[v].erase(u);
  if (adj[u].size() + queries[u].size() > adj[v].size() && queries[v].size()) {
    swap(u, v);
  }
  set<pair<int, int>> del_queries;
  for (auto x : adj[u]) {
    auto l = queries[v].lower_bound({x, -1});
    auto r = queries[v].lower_bound({x + 1, -1});
    for (auto it = l; it != r; it++) {
      assert(res[it->second] == -1);
      assert(it->first == x);
      res[it->second] = w;
      del_queries.insert(*it);
      queries[x].erase({v, it->second});
    }
  }
  for (auto [x, id] : queries[u]) {
    if (adj[v].count(x)) {
      assert(res[id] == -1);
      res[id] = w;
      del_queries.insert({x, id});
      queries[x].erase({u, id});
    }
  }

  for (auto x : adj[u]) {
    adj[x].erase(u);
    adj[x].insert(v);
  }

  for (auto [x, id] : queries[u]) {
    queries[x].erase({u, id});
    queries[x].insert({v, id});
  }

  for (auto x : adj[u]) {
    adj[v].insert(x);
  }

  for (auto x : queries[u]) {
    if (!del_queries.count(x)) {
      queries[v].insert(x);
    }
  }

  adj[u].clear();
  queries[u].clear();
  root[u] = v;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
      adj[i].clear();
      queries[i].clear();
      root[i] = 0;
    }
    fill(res + 1, res + q + 1, -1);

    for (int i = 1; i <= m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      adj[u].insert(v);
      adj[v].insert(u);
      edges[i] = {w, {u, v}};
    }
    for (int i = 1; i <= q; i++) {
      int u, v;
      cin >> u >> v;
      if (adj[u].count(v)) {
        res[i] = 0;
        continue;
      }
      queries[u].insert({v, i});
      queries[v].insert({u, i});
    }
    sort(edges + 1, edges + m + 1);
    for (int i = 1; i <= m; i++) {
      auto [w, x] = edges[i];
      auto [u, v] = x;
      Unite(u, v, w);
    }
    for (int i = 1; i <= q; i++) {
      cout << res[i] << '\n';
    }
  }
  return 0;
}