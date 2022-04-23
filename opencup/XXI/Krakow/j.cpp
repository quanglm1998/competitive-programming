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

const int X[] = {0, 1, 0, -1};
const int Y[] = {1, 0, -1, 0};

void Solve(int test) {
  int n;
  cin >> n;
  vector<vector<int>> v(n, vector<int>(n));
  for (auto &row : v) {
    for (auto &cell : row) {
      cin >> cell;
    }
  }

  vector<vector<int>> p(n, vector<int>(n));
  for (auto &row : p) {
    for (auto &cell : row) {
      cin >> cell;
    }
  }

  auto IsInside = [&](int u, int v) {
    return u >= 0 && u < n && v >= 0 && v < n;
  };

  struct Civilization {
    int num;
    int val;
    int length;
  };

  vector<Civilization> a(n * n, {0, 0, 0});

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[p[i][j]].num++;
      a[p[i][j]].val += v[i][j];
      for (int k = 0; k < 4; k++) {
        int ii = i + X[k];
        int jj = j + Y[k];
        if (IsInside(ii, jj) && p[i][j] != p[ii][jj]) {
          a[p[i][j]].length++;
        }
      }
    }
  }
  vector<multiset<int>> v_by_length(4 * n * n);
  map<int, int> pos_set;

  auto AddCivil = [&](int u) {
    if (!a[u].num) {
      return;
    }
    pos_set[a[u].length]++;
    v_by_length[a[u].length].insert(a[u].val);
  };

  auto RemoveCivil = [&](int u) {
    if (!a[u].num) {
      return;
    }
    pos_set[a[u].length]--;
    if (!pos_set[a[u].length]) {
      pos_set.erase(a[u].length);
    }
    v_by_length[a[u].length].erase(v_by_length[a[u].length].find(a[u].val));
  };

  for (int i = 0; i < n * n; i++) {
    AddCivil(i);
  }

  auto Erase = [&](int x, int y) {
    // debug("erase", x, y);
    int old_cil = p[x][y];
    // debug(old_cil);
    RemoveCivil(old_cil);
    a[old_cil].num--;
    a[old_cil].val -= v[x][y];
    for (int k = 0; k < 4; k++) {
      int xx = x + X[k];
      int yy = y + Y[k];
      if (IsInside(xx, yy) && p[x][y] != p[xx][yy]) {
        a[old_cil].length--;
        RemoveCivil(p[xx][yy]);
        a[p[xx][yy]].length--;
        AddCivil(p[xx][yy]);
      }
    }
    AddCivil(old_cil);
    // debug("end erase", x, y);
  };

  auto Insert = [&](int x, int y) {
    // debug("insert", x, y);
    auto new_cil = p[x][y];
    // debug(new_cil);
    RemoveCivil(new_cil);
    a[new_cil].num++;
    a[new_cil].val += v[x][y];
    for (int k = 0; k < 4; k++) {
      int xx = x + X[k];
      int yy = y + Y[k];
      if (IsInside(xx, yy) && p[x][y] != p[xx][yy]) {
        a[new_cil].length++;
        RemoveCivil(p[xx][yy]);
        a[p[xx][yy]].length++;
        AddCivil(p[xx][yy]);
      }
    }
    // debug(a[new_cil].num, a[new_cil].val, a[new_cil].length);
    AddCivil(new_cil);
    // debug("end insert", x, y);
  };

  int q;
  cin >> q;
  while (q--) { 
    int u, v, x;
    long long A, B, C;
    cin >> u >> v >> x >> A >> B >> C;
    u--, v--;
    debug(u, v, x, A, B, C);
    Erase(u, v);
    p[u][v] = x;
    Insert(u, v);

    for (int i = 0; i < n * n; i++) {
      if (!a[i].num) continue;
      debug(i, a[i].num, a[i].val, a[i].length);
    }
    long long res = -1e18;
    for (auto [length, _] : pos_set) {
      assert(!v_by_length[length].empty());
      res = max(res, A * *v_by_length[length].begin() + B * length + C * *v_by_length[length].begin() * length);
      res = max(res, A * *v_by_length[length].rbegin() + B * length + C * *v_by_length[length].rbegin() * length);
    }
    cout << res << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}