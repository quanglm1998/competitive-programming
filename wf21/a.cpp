#include <bits/stdc++.h>

using namespace std;

// debugger, source: tourist
template <typename A, typename B>
string to_string(pair<A, B> p);
string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]);
  return res;
}
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) res += ", ";
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<vector<bool>> used(n, vector<bool>(m));

  const int X[] = {0, -1, 0, 1};
  const int Y[] = {1, 0, -1, 0};

  auto IsInside = [&](int u, int v) {
    return u >= 0 && u < n && v >= 0 && v < m;
  };

  function<void(int, int, vector<pair<int, int>>&)> Dfs = [&](int u, int v, vector<pair<int, int>> &ls) {
    used[u][v] = true;
    ls.push_back({u, v});
    for (int i = 0; i < 4; i++) {
      int uu = u + X[i];
      int vv = v + Y[i];
      if (!IsInside(uu, vv) || used[uu][vv]) continue;
      if (a[u][v] != a[uu][vv]) continue;
      Dfs(uu, vv, ls);
    }
  };

  vector<vector<int>> s(n, vector<int>(m, -1));
  vector<vector<pair<int, int>>> tile_list;
  vector<pair<int, int>> pos_tile;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '.') continue;
      if (used[i][j]) continue;
      tile_list.push_back(vector<pair<int, int>>());
      Dfs(i, j, tile_list.back());
      for (auto [u, v] : tile_list.back()) {
        s[u][v] = tile_list.size() - 1;
      }
      for (auto &[u, v] : tile_list.back()) {
        u -= i;
        v -= j;
      }
      pos_tile.push_back({i, j});
    }
  }

  for (int i = 0; i < tile_list.size(); i++) {
    debug(i, tile_list[i]);
  }
  for (int i = 0; i < n; i++) {
    debug(s[i]);
  }

  const int INF = 1e9;
  vector<vector<vector<int>>> block_tile(pos_tile.size(), vector<vector<int>>(n, vector<int>(m, INF)));
  vector<vector<vector<int>>> d(pos_tile.size(), vector<vector<int>>(n, vector<int>(m, 0)));
  vector<vector<vector<int>>> trace(pos_tile.size(), vector<vector<int>>(n, vector<int>(m, -1)));
  using pii = pair<int, pair<int, int>>;
  vector<vector<vector< pii >>> block_list(n, vector<vector< pii >>(m));
  vector<bool> is_delelted(pos_tile.size());

  auto CalcBlock = [&](int id, int x, int y) {
    int res = 0;
    // debug("calc", id, x, y);
    for (auto [du, dv] : tile_list[id]) {
      auto uu = x + du;
      auto vv = y + dv;
      if (!IsInside(uu, vv)) return INF;
      if (s[uu][vv] == -1) continue;
      if (s[uu][vv] != id) {
        block_list[uu][vv].push_back({id, {x, y}});
        // debug(id, x, y, uu, vv);
        res++;
      }
    }
    return res;
  };

  queue<pair<int, pair<int, int>>> q;
  for (int i = 0; i < tile_list.size(); i++) {
    auto [u, v] = pos_tile[i];
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < m; y++) {
        block_tile[i][x][y] = CalcBlock(i, x, y);
      }
    }
    q.push({i, {u, v}});
    d[i][u][v] = 2;
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j= 0; j < m; j++) {
  //     debug(i, j, block_list[i][j]);
  //   }
  // }

  vector<pair<int, string>> res;

  auto Remove = [&](int id, int x, int y) {
    debug("remove", id, x, y);
    for (auto [du, dv] : tile_list[id]) {
      auto uu = pos_tile[id].first + du;
      auto vv = pos_tile[id].second + dv;
      assert(IsInside(uu, vv));
      for (auto [id2, o2] : block_list[uu][vv]) {
        auto [xx, yy] = o2;
        // if (id2 == 4) debug(id, uu, vv, xx, yy);
        block_tile[id2][xx][yy]--;
        if (!block_tile[id2][xx][yy] && d[id2][xx][yy] == 1 && !is_delelted[id2]) {
          d[id2][xx][yy] = 2;
          q.push({id2, {xx, yy}});
        }
      }
    }
    res.push_back({y, ""});
    while (trace[id][x][y] != -1) {
      debug(id, x, y, trace[id][x][y]);
      if (trace[id][x][y] == 0) res.back().second += 'L';
      if (trace[id][x][y] == 1) res.back().second += 'D';
      if (trace[id][x][y] == 2) res.back().second += 'R';
      auto d = trace[id][x][y];
      x -= X[d];
      y -= Y[d];
    }
    res.back().second += 'S';
    is_delelted[id] = true;
  };

  auto SearchFrom = [&](int id, int x, int y) {
    for (int i = 0; i < 3; i++) {
      auto xx = x + X[i];
      auto yy = y + Y[i];
      if (!IsInside(xx, yy)) continue;
      if (d[id][xx][yy]) continue;
      trace[id][xx][yy] = i;
      if (block_tile[id][xx][yy]) {
        d[id][xx][yy] = 1;
      } else {
        d[id][xx][yy] = 2;
        q.push({id, {xx, yy}});
      }
    }
  };

  while (!q.empty()) {
    auto [id, o] = q.front();
    q.pop();
    auto [x, y] = o;
    debug(id, x, y);
    if (is_delelted[id]) continue;
    if (x == 0) {
      Remove(id, x, y);
      debug(block_tile[4][0][5]);
      continue;
    }
    SearchFrom(id, x, y);
  }


  if (res.size() != pos_tile.size()) {
    cout << -1 << '\n';
    return 0;
  }
  cout << res.size() << '\n';
  reverse(res.begin(), res.end());
  for (auto [u, v] : res) {
    cout << u + 1 << ' ' << v << '\n';
  }
  return 0;
}