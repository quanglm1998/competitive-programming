#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N];

struct BIT {
  int t[N];

  void Init(int n) {
    fill(t, t + n + 1, 0);
  }

  void Add(int x, int v) {
    while (x <= n) {
      t[x] += v;
      x += x & -x;
    }
  }

  int Get(int x) {
    int res = 0;
    while (x) {
      res += t[x];
      x -= x & -x;
    }
    return res;
  }

  int Get(int l, int r) {
    return Get(r) - Get(l - 1);
  }
} t;

void Solve(int test) {
  cin >> n;
  t.Init(n);
  vector<int> vals;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    vals.push_back(a[i]);
  }  
  sort(vals.begin(), vals.end());
  vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
  }
  long long res = 0;
  for (int i = 1; i <= n; i++) {
    res += min(t.Get(1, a[i] - 1), t.Get(a[i] + 1, n));
    t.Add(a[i], 1);
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