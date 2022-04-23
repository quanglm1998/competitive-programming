#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n, M;
  cin >> n >> M;
  vector<tuple<int, int, int>> edges(M);
  map<pair<int, int>, int> m;
  for (int i = 0; i < M; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    m[ {u, v}] = i;
    m[ {v, u}] = i;
    edges[i] = {u, v, w};
  }
  vector<vector<int>> adj(M);

  auto Check = [&](int x, int y, int z, int t) {
    if (!m.count({x, y}) || !m.count({y, z}) || !m.count({z, t})) return false;
    if (!m.count({x, z}) || !m.count({y, t})) return false;
    if (!m.count({x, t})) return false;
    return true;
  };

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        for (int l = k + 1; l < n; l++) {
          if (!Check(i, j, k, l)) {
            continue;
          }
          adj[m[ {i, j}]].push_back(m[ {k, l}]);
          adj[m[ {k, l}]].push_back(m[ {i, j}]);
          adj[m[ {i, k}]].push_back(m[ {j, l}]);
          adj[m[ {j, l}]].push_back(m[ {i, k}]);
          adj[m[ {i, l}]].push_back(m[ {j, k}]);
          adj[m[ {j, k}]].push_back(m[ {i, l}]);
        }
      }
    }
  }

  bool f = false;
  vector<bool> used(M);

  for (int i = 0; i < M; i++) {
    if (used[i]) continue;
    vector<int> ls;
    ls.push_back(i);
    used[i] = 1;
    set<int> s;
    if (get<2>(edges[i]) != -1) {
      s.insert(get<2>(edges[i]));
    }
    for (int i = 0; i < ls.size(); i++) {
      auto u = ls[i];
      for (auto v : adj[u]) {
        if (!used[v]) {
          used[v] = 1;
          ls.push_back(v);
          if (get<2>(edges[v]) != -1) {
            s.insert(get<2>(edges[v]));
          }
        }
      }
    }
    if (s.size() > 1) {
      f = true;
      break;
    }
    if (s.size() == 1) {
      auto val = *s.begin();
      for (auto u : ls) {
        get<2>(edges[u]) = val;
      }
    }
  }
  if (f) {
    cout << -1 << '\n';
    return;
  }
  
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}