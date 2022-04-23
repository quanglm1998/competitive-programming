#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

void Solve(int test) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int u, v;
    cin >> u >> v;
  }
  if (n == 2) {
    cout << "Hoang\n";
  } else {
    if (n % 4 == 2 || n % 4 == 3) {
      cout << "Hoang\n";
    } else {
      cout << "Vuong\n";
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