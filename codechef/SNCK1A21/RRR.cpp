#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  long long n, k;
  cin >> n >> k;
  cout << (n - k) * 2 + ((k - 1) / 2) * 2 << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}