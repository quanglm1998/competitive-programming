#include <bits/stdc++.h>

using namespace std;

struct BIT {
  vector<int> t;

  BIT(int n) {
    t.resize(n, 0);
  }

  void add(int x, int v) {
    while (x < n) {
      t[x] += v;
      x += x & -x;
    }
  }

  int get(int x) {
    int res = 0;
    while (x) {
      res += t[x];
      x -= x & -x;
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  BIT t(n);
  for (const int &u : a) {
    t.add(u, 1);
  }
  for (int i = 0; i < n; i++) {
    cout << t.get(i);
  }
  return 0;
}
