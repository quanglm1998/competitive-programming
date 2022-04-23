#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  cout << "Case #" << test << ": ";
  int n, m;
  cin >> n >> m;
  int a, b;
  cin >> a >> b;
  if ((n == 1 || m == 1) && a != b) {
    cout << "Impossible\n";
    return;
  }
  int len = n + m - 1;
  if (a < len || b < len) {
    cout << "Impossible\n";
    return;
  }
  cout << "Possible\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == n - 1 && j == m - 1) {
        cout << a - len + 1 << ' ';
      } else if (i == 0 && j == m - 1) {
        cout << b - len + 1 << ' ';
      } else {
        cout << 1 << ' ';
      }
    }
    cout << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}