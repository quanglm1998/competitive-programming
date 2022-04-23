#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  int n, k;
  cin >> n >> k;
  vector<int> a(k);
  for (auto &u : a) {
    cin >> u;
    u--;
  }
  vector<int> t(k);
  for (auto &u : t) {
    cin >> u;
  }
  vector<int> dist(n, 1.01e9);
  vector<bool> used(n, false);
  set<pair<int, int>> s;
  for (int i = 0; i < k; i++) {
    dist[a[i]] = t[i];
    s.insert({t[i], a[i]});
  }
  while (!s.empty()) {
    auto [d, u] = *s.begin();
    s.erase(s.begin());
    if (u > 0 && !used[u - 1] && dist[u - 1] > d + 1) {
      if (!s.count({dist[u - 1], u - 1})) {
        s.erase({dist[u - 1], u - 1});
      }
      dist[u - 1] = d + 1;
      s.insert({dist[u - 1], u - 1});
    }
    if (u + 1 < n && !used[u + 1] && dist[u + 1] > d + 1) {
      if (!s.count({dist[u + 1], u + 1})) {
        s.erase({dist[u + 1], u + 1});
      }
      dist[u + 1] = d + 1;
      s.insert({dist[u + 1], u + 1});
    }
  }
  for (auto u : dist) cout << u << ' ';
    cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);
  }
  return 0;
}