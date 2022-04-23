#include <bits/stdc++.h>

using namespace std;

class DSU {
 public:
  explicit DSU(int n) : num_comp_(n), root_(n, -1), sz_(n, 1), dist(n, vector<int>(n, -1)) {
    ls.resize(n);
    for (int i = 0; i < n; i++) {
      ls[i].push_back(i);
    }
  }

  int get_dist(int u, int v) {
    return dist[u][v];
  }
  int num_comp() const { return num_comp_; }
  int sz(int u) { return sz_[GetRoot(u)]; }

  int GetRoot(int u) { return ~root_[u] ? root_[u] = GetRoot(root_[u]) : u; }

  bool Unite(int u, int v, int d) {
    u = GetRoot(u);
    v = GetRoot(v);
    if (u == v) return false;
    for (auto x : ls[u]) {
      for (auto y : ls[v]) {
        dist[x][y] = dist[y][x] = d;
      }
    }
    for (auto x : ls[u]) ls[v].push_back(x);
    sz_[v] += sz_[u];
    root_[u] = v;
    num_comp_--;
    return true;
  }

 private:
  int num_comp_;  // number of connected components
  vector<int> sz_;
  vector<int> root_;
  vector<vector<int>> ls;
  vector<vector<int>> dist;
};

void solve(int tt) {
      cout << "Case #" << tt << ": ";
    int n;
    cin >> n;
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int u;
        cin >> u;
        if (i < j) {
          edges.push_back({i, j, u});
        }
      }
    }
    sort(edges.begin(), edges.end(), [&](tuple<int, int, int> u, tuple<int, int, int> v) {
      return get<2>(u) > get<2>(v);
    });
    DSU dsu(n);
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (auto [u, v, d] : edges) {
      if (dsu.Unite(u, v, d)) {
        res[u][v] = res[v][u] = d;
      } else {
        if (dsu.get_dist(u, v) != d) {
          assert(dsu.get_dist(u, v) != -1);
          cout << "NO\n";
          return;
        }
      }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << res[i][j];
        if (j + 1 < n) cout << ' ';
      }
      cout << '\n';
    }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int tt = 1; tt <= tc; tt++) {
    solve(tt);
  }
  return 0;
}