#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  string s;
  cin >> s;
  int x;
  cin >> x;
  if (s[0] - 'A' == x) {
    cout << "YES\n";
  } else cout << "NO\n";
  return 0;
}