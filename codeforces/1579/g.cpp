#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  int N = *max_element(a.begin(), a.end()) * 3;
  const int INF = 1e9;

  vector<int> f(N, -INF);
  f[0] = 0;
  for (auto d : a) {
    vector<int> g(N, -INF);
    for (int i = 0; i < f.size(); i++) {
      g[max(0, i - d)] = max(g[max(0, i - d)], f[i] - d);
      if (i + d < f.size()) {
        g[i + d] = max(g[i + d], min(0, f[i] + d));
      }
    }
    swap(f, g);
  }
  int res = INF;
  for (int i = 0; i < f.size(); i++) {
    res = min(res, i - f[i]);
  }
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}