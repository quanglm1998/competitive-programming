#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  cout << "Case #" << test << ": ";
  int n;
  long long c;
  cin >> n >> c;
  vector<pair<long long, int>> ls;
  for (int i = 0; i < n; i++) {
    long long l, r;
    cin >> l >> r;
    ls.push_back({l + 1, 1});
    ls.push_back({r, -1});
  }
  sort(ls.begin(), ls.end());
  long long last = -1;
  int cur = 0;
  multiset<pair<int, long long>> s;
  for (int l = 0, r = 0; l < ls.size(); l = r) {
    while (r < ls.size() && ls[l].first == ls[r].first) r++;
    if (cur) s.insert({cur, ls[l].first - last});
    for (int i = l; i < r; i++) {
      cur += ls[i].second;
    }
    last = ls[l].first;
  }
  long long res = n;
  while (c > 0 && !s.empty()) {
    auto it = prev(s.end());
    auto num = min(c, it->second);
    res += 1ll * num * it->first;
    c -= num;
    s.erase(it);
  }
  cout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);
  }
  return 0;
}