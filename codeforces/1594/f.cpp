#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  long long s, n, k;
  cin >> s >> n >> k;
  auto x = n / k;
  auto q = n % k;
  // cout << s << ' ' << n << ' ' << k << ' ' << x << ' ' << q << endl;
  if (k <= n) cout << (s >= x * 2 * k + q ? "NO" : "YES") << '\n';
  else {
    if (s < k || s >= n + k) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}