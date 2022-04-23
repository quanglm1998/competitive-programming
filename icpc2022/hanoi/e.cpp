#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const string DIR = "RDLU";
const int X[] = {0, 1, 0, -1};
const int Y[] = {1, 0, -1, 0};

void Solve(int test) {
  int r, c;
  cin >> r >> c;
  vector<string> a(r);
  for (auto &s : a) {
    cin >> s;
  }

  auto Flip = [&](char &u) {
    if (u == 'X') {
      u = '.';
    } else {
      u = 'X';
    }
  };

  auto IsInside = [&](int u, int v) {
    return u >= 0 && u < r && v >= 0 && v < c;
  };

  vector<vector<bool>> used(r, vector<bool>(c));

  vector<pair<pair<int, int>, char>> res;

  auto GetDir = [&](int u, int v, int x, int y) {
    for (int i = 0; i < 4; i++) {
      int uu = u + X[i];
      int vv = v + Y[i];
      if (uu == x && vv == y) {
        return DIR[i];
      }
    }
    debug("here", u, v, x,  y);
    exit(1);
  };

  function<void(int, int)> Dfs = [&](int u, int v) {
    used[u][v] = 1;
    vector<pair<int, int>> ls;
    for (int i = 0; i < 4; i++) {
      int uu = u + X[i];
      int vv = v + Y[i];
      if (!IsInside(uu, vv) || used[uu][vv] || a[uu][vv] == '#') continue;
      Dfs(uu, vv);
      if (a[uu][vv] == 'X') {
        ls.push_back({uu, vv});
      }
    }

    for (auto val : ls) {
      Flip(a[val.first][val.second]);
      Flip(a[u][v]);
      res.push_back({{u, v}, GetDir(u, v, val.first, val.second)});
    }
  };

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (used[i][j] || a[i][j] == '#') continue;
      Dfs(i, j);
      if (a[i][j] == 'X') {
        cout << -1 << '\n';
        return;
      }
    }
  }
  cout << res.size() << '\n';
  for (auto [u, c] : res) {
    cout << u.first + 1 << ' ' << u.second + 1 << ' ' << c << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}