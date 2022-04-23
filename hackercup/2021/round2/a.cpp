#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  cout << "Case #" << test << ": ";
  int n, m;
  cin >> n >> m;
  vector<int> s(m);
  vector<bool> used(m);
  for (auto &u : s) {
    cin >> u;
  }
  int res = 0;
  for (int j = 0; j < n; j++) {
    vector<int> p(m);
    vector<bool> next_used(m);
    set<pair<int, int>> pos;
    for (int i = 0; i < m; i++) {
      cin >> p[i];
      pos.insert({p[i], i});
    }
    vector<bool> filled(m);

    // used
    for (int i = 0; i < m; i++) {
      if (!used[i]) continue;
      auto it = pos.lower_bound({s[i], -1});
      if (it == pos.end() || it->first != s[i]) continue;
      filled[i] = 1;
      next_used[it->second] = 1;
      pos.erase(it);
    }
    // unused
    for (int i = 0; i < m; i++) {
      if (used[i]) continue;
      auto it = pos.lower_bound({s[i], -1});
      if (it == pos.end() || it->first != s[i]) continue;
      filled[i] = 1;
      next_used[it->second] = 0;
      pos.erase(it);
    }
    // unfilled
    for (int i = 0; i < m; i++) {
      if (filled[i]) continue;
      auto it = pos.begin();
      if (used[i]) res++;
      next_used[it->second] = 1;
      pos.erase(it);
    }
    swap(used, next_used);
    swap(s, p);
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