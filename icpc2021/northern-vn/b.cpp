#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  set<int> m;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    m.insert(u);
  }
  for (auto u : m) {
    if (!m.count(-u)) {
      cout << -u << "\n";
      return 0;
    }
  }
  exit(1);
  return 0;
}