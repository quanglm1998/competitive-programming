#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  set<int> s;
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    s.insert(i - u);
  }
  cout << (s.size() == 1 ? n : 1) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}