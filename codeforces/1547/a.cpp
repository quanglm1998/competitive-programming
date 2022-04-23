#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  int xa, ya, xb, yb, xc, yc;
  cin >> xa >> ya;
  cin >> xb >> yb;
  cin >> xc >> yc;
  int res = abs(xa - xb) + abs(ya - yb);
  if (xa == xb && xc == xa && min(ya, yb) <= yc && yc <= max(ya, yb)) {
    res += 2;
  }
  if (ya == yb && yc == ya && min(xa, xb) <= xc && xc <= max(xa, xb)) {
    res += 2;
  }
  cout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);
  }
  return 0;
}