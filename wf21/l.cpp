#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m;
int c[N];
vector<pair<int, int>> adj[N];
set<pair<long long, pair<int, int>>> s;

struct DSU {
  int root[N];
  set<pair<int, int>> nxt[N];
  long long sum[N];

  pair<long long, pair<int, int>> Get(int u) {
    u = GetRoot(u);
    if (nxt[u].empty()) return { -1, { -1, -1}};
    return {sum[u] + nxt[u].rbegin()->first, {u, nxt[u].rbegin()->second}};
  }

  void init() {
    fill(root + 1, root + n + 1, 0);
    for (int i = 1; i <= n; i++) {
      nxt[i].clear();
      sum[i] = c[i];
      for (auto [v, w] : adj[i]) {
        nxt[i].insert({w, v});
      }
    }
    for (int i = 1; i <= n; i++) {
      auto u = Get(i);
      if (u.first != -1) s.insert(u);
    }
  }


  int GetRoot(int u) {
    return root[u] ? root[u] = GetRoot(root[u]) : u;
  }

  bool Unite(int u, int v) {
    // cout << "unite " << u << ' ' << v << endl;
    u = GetRoot(u);
    v = GetRoot(v);
    auto uu = Get(u);
    s.erase(uu);
    // cout << "erase " << uu.first << ' ' << uu.second.first << ' ' << uu.second.second << endl;
    nxt[u].erase(*nxt[u].rbegin());
    if (u == v) {
      auto val = Get(u);
      if (val.first != -1) s.insert(val);
      return 0;
    }
    auto vv = Get(v);
    // cout << "erase " << vv.first << ' ' << vv.second.first << ' ' << vv.second.second << endl;
    s.erase(vv);
    if (nxt[u].size() < nxt[v].size()) swap(u, v);
    for (auto x : nxt[v]) nxt[u].insert(x);
    root[v] = u;
    sum[u] += sum[v];
    auto val = Get(u);
    if (val.first != -1) s.insert(val);
    // cout << "add " << val.first << ' ' << val.second.first << ' ' << val.second.second << endl;
    return 1;
  }
} dsu;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  dsu.init();
  // for (auto [d, u] : s) {
  //   cout << d << ' ' << u.first << ' ' << u.second << '\n';
  // }
  long long res = 1e18;
  while (!s.empty()) {
    auto [d, x] = *s.rbegin();
    s.erase({d, x});
    auto [u, v] = x;
    // cout << "s " << d << ' ' << u << ' ' << v << endl;
    if (dsu.Unite(u, v)) {
      // cout << "united" << endl;
      res = min(res, d);
    }
  }
  for (int i = 1; i <= n; i++) res -= c[i];
  if (res <= 0) cout << -1 << '\n';
  else cout << res << '\n';
  return 0;

}