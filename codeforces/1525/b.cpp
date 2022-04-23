#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &u : a) {
      cin >> u;
    }
    int f = 0;
    for (int i = 0; i + 1 < n; i++) {
      if (a[i] >= a[i + 1]) {
        f = 1;
        break;
      }
    }
    if (!f) {
      cout << 0 << '\n';
      continue;
    }
    if (a[0] == 1 || a[n - 1] == n) {
      cout << 1 << '\n';
    } else if (a[0] == n && a[n - 1] == 1) {
      cout << 3 << '\n';
    } else {
      cout << 2 << '\n';
    }
  }
  return 0;
}