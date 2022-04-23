#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int r;
  cin >> r >> n;
  if (r != 1) return 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  set<pair<pair<int, int>, int>> s;
  int last = 1;
  for (int i = 2; i <= n; i++) {
    if (a[i] != a[i - 1]) {
      s.insert({{last, i - 1}, a[last]});
      last = i;
    }
  }
  s.insert({{last, n}, a[n]});
  int q;
  cin >> q;
  while (q--) {
    int foo;
    int x, c;
    cin >> foo >> x >> c;
    assert(foo == 1);
    auto it = prev(s.lower_bound({{x + 1, -1}, -1}));
    auto cur = *it;
    cur.second = c;

    if (it != s.begin()) {
      auto pre = prev(it);
      if (pre->second == c) {
        cur.first.first = pre->first.first;
        s.erase(pre);
      }
    }
    if (next(it) != s.end()) {
      auto nxt = next(it);
      if (nxt->second == c) {
        cur.first.second = nxt->first.second;
        s.erase(nxt);
      }
    }

    s.erase(it);
    s.insert(cur);
  }
  for (auto [p, c] : s) {
    auto [u, v] = p;
    for (int i = u; i <= v; i++) {
      cout << c << ' ';
    }
  }
  cout << endl;
  return 0;
}