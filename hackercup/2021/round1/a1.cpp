#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  cout << "Case #" << test << ": ";
  int n;
  cin >> n;
  string s;
  cin >> s;
  pair<int, int> dp(0, 0);  
  for (auto u : s) {
    pair<int, int> nxt(1e9, 1e9);
    if (u == 'O') {
      nxt.second = min(dp.first + 1, dp.second);
    } else if (u == 'X') {
      nxt.first = min(dp.first, dp.second + 1);
    } else {
      nxt = dp;
    }
    dp = nxt;
  }  
  cout << min(dp.first, dp.second) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}