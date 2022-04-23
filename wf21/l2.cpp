#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

class DSU {
 public:
  explicit DSU(int n, const vector<int> c) : num_comp_(n), root_(n, -1), sz_(n, 1) {
    sum_.resize(n);
    res_.resize(n);
    for (int i = 0; i < n; i++) {
      sum_[i] = c[i];
      res_[i] = INF;
    }
  }

  int num_comp() const { return num_comp_; }
  int sz(int u) { return sz_[GetRoot(u)]; }
  long long sum(int u) { return sum_[GetRoot(u)]; }
  long long res(int u) { return res_[GetRoot(u)]; }

  int GetRoot(int u) { return ~root_[u] ? root_[u] = GetRoot(root_[u]) : u; }

  bool Unite(int u, int v, int w) {
    u = GetRoot(u);
    v = GetRoot(v);
    if (u == v) return false;
    res_[v] = max(min(res_[v], w + sum_[v]), min(res_[u], w + sum_[u]));
    sz_[v] += sz_[u];
    sum_[v] += sum_[u];
    root_[u] = v;
    num_comp_--;
    return true;
  }

 private:
  int num_comp_;  // number of connected components
  vector<int> sz_;
  vector<int> root_;
  vector<long long> sum_;
  vector<long long> res_;
};


int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> c(n);
  for (auto &u : c) {
    cin >> u;
  }
  vector<pair<int, pair<int, int>>> edges(m);
  for (auto &[w, u] : edges) {
    cin >> u.first >> u.second >> w;
    u.first--;
    u.second--;
  }
  sort(edges.begin(), edges.end());
  reverse(edges.begin(), edges.end());
  DSU dsu(n, c);
  for (auto [w, u] : edges) {
    dsu.Unite(u.first, u.second, w);
  }
  auto res = dsu.res(0) - dsu.sum(0);
  if (res <= 0) cout << -1 << '\n';
  else cout << res << '\n';
  return 0;
}