#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string res = "";
    while (n > 1) {
      if (n % 2) res += 'R';
      else res += 'L';
      n >>= 1;
    }
    reverse(res.begin(), res.end());
    cout << res << '\n';
  }
  return 0;
}