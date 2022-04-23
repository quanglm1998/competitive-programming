#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cout << 1 << '\n';
  int n = 100000;
  cout << n << '\n';
  for (int i = 0; i < n / 2; i++) {
    cout << 1 << ' ';
  }
  for (int i = n / 2; i < n; i++) {
    cout << 2;
    if (i + 1 < n) cout << ' ';
  }
  cout << '\n';
  return 0;
}