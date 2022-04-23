#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int a, b, c;
  cin >> a >> b >> c;
  cout << (a == 7 || b == 7 || c == 7 ? "YES" : "NO") << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}