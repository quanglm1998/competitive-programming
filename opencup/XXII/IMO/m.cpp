#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  const int N = 1e6;
  vector<int> cnt(N + 1, 0);
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    cnt[u]++;
  }
  long long res = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = i; j <= N; j += i) {
      int k = j / i;
      if (k > i && (k - i) % 2 == 0) {
        res += 1ll * cnt[j] * cnt[(k - i) / 2];
      }
    }
  }
  cout << res << '\n';
  return 0;
}