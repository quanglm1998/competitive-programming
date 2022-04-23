#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> a;
  while (n) {
    a.push_back(n);
    n /= 2;
  }
  if (a.size() % 2) a.push_back(0);
  int res = 0;
  for (int i = 0; i < a.size(); i += 2) {
    res += a[i] - a[i + 1];
  }
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}