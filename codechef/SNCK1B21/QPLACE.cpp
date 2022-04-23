#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  if (n == 4) {
    cout << "...Q\n";
    cout << "....\n";
    cout << ".Q..\n";
    cout << "....\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
        cout << '.';
        continue;
      }
      if (i == 2 || i == n - 3) {
        if (i + j == n - 1) {
          cout << 'Q';
        } else {
          cout << '.';
        }
        continue;
      }
      if (i == j) {
        cout << 'Q';
      } else {
        cout << '.';
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