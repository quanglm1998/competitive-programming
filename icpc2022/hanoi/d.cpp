#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  set<int> s;
  map<int, int> m;
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    s.insert(u);
    m[u]++;
    while (!s.empty() && m[*s.begin()] > 1) {
      s.erase(s.begin());
    }
    cout << (s.empty() ? -1 : *s.begin()) << '\n';
  }
  return 0;
}