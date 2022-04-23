#include <bits/stdc++.h>

using namespace std;

vector<int> ls;

void Solve(int test) {
  int n;
  cin >> n;
  cout << (upper_bound(ls.begin(), ls.end(), n) - ls.begin()) * 2 << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  const int K = 1e9;
  ls.push_back(1);
  int cur = 1;
  while (ls.back() <= K) {
    ls.push_back(ls.back() + cur++);
  }

  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}