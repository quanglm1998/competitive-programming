#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

vector<int> p(N, 0);

void solve(int test) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }

  auto GetDivs = [&](int u) {
    vector<pair<int, int>> res;
    while (u > 1) {
      int v = p[u];
      int cnt = 0;
      while (u % v == 0) {
        u /= v;
        cnt++;
      }
      res.push_back({v, cnt});
    }
    return res;
  };

  int g = 0;
  for (auto u : a) {
    g = __gcd(g, u);
  }

  for (auto &u : a) {
    u /= g;
  }

  vector<pair<int, int>> ls;

  for (int i = 0; i < n; i++) {
    auto divs = GetDivs(a[i]);
    for (auto [u, cnt] : divs) {
      ls.push_back({u, i});
    }
  }

  int res = 0;
  sort(ls.begin(), ls.end());
  for (int l = 0, r = 0; l < ls.size(); l = r) {
    while (r < ls.size() && ls[l].first == ls[r].first) r++;
    vector<int> pos;
    for (int i = l; i < r; i++) {
      pos.push_back(ls[i].second);
    }
    for (int i = l; i < r; i++) {
      pos.push_back(ls[i].second + n);
    }

    int last = -10;
    int cur = 0;
    for (auto u : pos) {
      if (u == last + 1) {
        cur++;
      } else {
        cur = 1;
      }
      res = max(res, cur);
      last = u;
    }
  } 
  cout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  for (int i = 2; i < N; i++) {
    if (p[i] == 0) {
      for (int j = i; j < N; j += i) {
        if (p[j] == 0) p[j] = i;
      }
    }
  }

  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);
  }
  return 0;
}