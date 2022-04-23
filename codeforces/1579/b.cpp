#include <bits/stdc++.h>

using namespace std;

const int N = 55;

int n;
int a[N];
int b[N];

void Solve(int test) {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = a[i];
  }
  sort(b + 1, b + n + 1);
  vector<pair<pair<int, int>, int>> res;
  for (int i = 1; i <= n; i++) {
    int pos = 0;
    for (int j = i; j <= n; j++) {
      if (a[j] == b[i]) {
        pos = j;
        break;
      }
    }
    assert(pos);
    if (pos > i) {
      res.push_back({{i, n}, pos - i});
      rotate(a + i, a + pos, a + n + 1);
    }
  }
  cout << res.size() << '\n';
  for (auto [u, v] : res) {
    cout << u.first << ' ' << u.second << ' ' << v << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}