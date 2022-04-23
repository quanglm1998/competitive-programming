#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  multiset<pair<int, int>> a;
  for (int i = 1; i <= n; i++) {
    int u;
    cin >> u;
    if (u > 0) {
      a.insert({u, i});
    }
  }
  vector<pair<int, int>> res;
  while (a.size() >= 2) {
    auto it = a.end();
    auto itx = prev(it);
    auto ity = prev(itx);
    auto x = *itx;
    auto y = *ity;
    a.erase(itx);
    a.erase(ity);

    res.push_back({x.second, y.second});
    x.first--;
    y.first--;
    if (x.first > 0) a.insert(x);
    if (y.first > 0) a.insert(y);
  }
  cout << res.size() << '\n';
  for (auto [u, v] : res) {
    cout << u << ' ' << v << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}