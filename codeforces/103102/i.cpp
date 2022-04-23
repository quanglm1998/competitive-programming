#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;
const int N = 1000010;

int add(int u, int v) {
  return (u + v) % MOD;
}

int sub(int u, int v) {
  return (u - v + MOD) % MOD;
}

int mul(int u, int v) {
  return 1ll * u * v % MOD;
}

int n;
int dp[N];

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  if (n == 1) {
    cout << 1 << '\n';
    return 0;
  }
  if (n == 2) {
    cout << 2 << '\n';
    return 0;
  }
  dp[3] = 1;
  int res = 0;
  for (int i = 3; i <= n; i++) {
    int u = i - 1;
    for (int j = u; j <= n; j += u) {
      for (int delta = 0; delta <= min(2, u - 1); delta++) {
        if (j + delta > n) continue;
        if (j + delta <= i) continue;
        dp[j + delta] = add(dp[j + delta], dp[i]);
      }
    }
    res = add(res, dp[i]);
  }

  cout << mul(res, mul(2, n)) << '\n';
  return 0;
}