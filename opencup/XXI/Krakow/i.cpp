#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> cnt(1'000'001, 0);
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    cnt[u]++;
  }
  long long res = 0;
  for (int i = 1; i < cnt.size(); i++) {
    for (int j = i; j < cnt.size(); j += i) {
      auto k = j + i;
      if ((k ^ j) == i && k < cnt.size()) {
        res += cnt[j] * cnt[k];
      }
    }
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