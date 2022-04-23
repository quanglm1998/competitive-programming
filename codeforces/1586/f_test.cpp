#include <bits/stdc++.h>

using namespace std;

int Solve(int n) {
  int res = 1;
  vector<set<int>> s(n + 1);
  for (int i = n - 1; i; i--) {
    for (int j = i + 1; j <= n; j++) {
      int val = 1;
      while (s[j].count(val)) {
        val++;
      }
      res = max(res, val);
      s[i].insert(val);
      cout << i << ' ' << j << ' ' << val << endl;
    }
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // for (int i = 2; i <= 20; i++) {
  //   cout << i << ' ' << Solve(i) << endl;
  // }
  Solve(5);
  return 0;
}