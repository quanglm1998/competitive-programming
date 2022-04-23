#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int x, y;
  cin >> x >> y;
  if (x >= y) {
    cout << x - y << '\n';
    return;
  }
  if ((y - x) % 2 == 0) {
    cout << (y - x) / 2 << '\n';
  } else {
    cout << (y - x + 1) / 2 + 1 << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}