#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  int all_and = a[0];
  for (int i = 1; i < n; i++) {
    all_and &= a[i];
  }
  if (find(a.begin(), a.end(), all_and) == a.end()) {
    cout << -1 << '\n';
  } else {
    cout << n * 2 << '\n';
    for (int i = 0; i < n; i++) {
      cout << a[i] << ' ' << all_and << ' ';
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