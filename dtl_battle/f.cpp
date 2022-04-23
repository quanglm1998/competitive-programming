#include <bits/stdc++.h>

using namespace std;

int Power(int a, int b, int m) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1ll * res * a % m;
    a = 1ll * a * a % m;
    b >>= 1;
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int a, m;
  cin >> a >> m;
  int cur = 1;
  while (Power(a, cur, m) != cur % m && cur <= 1e7) cur++;
  if (Power(a, cur, m) == cur % m) cout << cur << '\n';
  else cout << -1 << '\n';
  return 0;
}