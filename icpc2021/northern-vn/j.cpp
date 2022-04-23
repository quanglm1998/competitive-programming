#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  long long m;
  cin >> n >> m;
  vector<pair<long long, long long>> a(n);
  for (auto &[u, v] : a) {
    cin >> u >> v;
  }
  long long low = 0, high = 2e15;
  while (high - low > 1) {
    auto mid = low + high >> 1;
    __int128 tot = 0;
    for (auto [u, v] : a) {
      auto leaves = mid / (v + 1);
      tot += (__int128)(mid - leaves) * u;
    }
    if (tot >= m) {
      high = mid;
    } else {
      low = mid;
    }
  }
  cout << high << '\n';
  return 0;
}