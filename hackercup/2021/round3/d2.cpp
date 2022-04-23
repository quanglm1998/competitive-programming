#include <bits/stdc++.h>

using namespace std;

const int X[] = {0, 1, 0, -1};
const int Y[] = {1, 0, -1, 0};

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

class DSU {
 public:
  explicit DSU(int n) : num_comp_(n), root_(n, -1), sz_(n, 1), s_(n) {}

  int num_comp() const { return num_comp_; }
  int sz(int u) { return sz_[GetRoot(u)]; }


  int GetRoot(int u) { return ~root_[u] ? root_[u] = GetRoot(root_[u]) : u; }

  int AddRange(int u, int l, int r) {
    u = GetRoot(u);
    int res = 0;
    int res2 = 0;
    // for (int i = l; i <= r; i++) {
    //   bool f = 0;
    //   for (auto [x, y] : s_[u]) {
    //     if (x <= i && i <= y) {
    //       f = 1;
    //       break;
    //     }
    //   }
    //   res2 += f;
    // }

    // auto old_s = s_[u];

    // debug("add", u, l, r);
    // debug("before", s_[u]);
    while (1) {
      auto it = s_[u].lower_bound({l, -1});
      if (it == s_[u].end()) break;
      if (it->second <= r) {
        res += it->second - it->first + 1;
        s_[u].erase(it);
      } else break;
    }
    // debug(res, s_[u]);

    auto range = pair(l, r);
    auto it = s_[u].lower_bound({range.first, -1});
    if (it != s_[u].begin() && prev(it)->second >= l) {
      auto p_it = prev(it);
      if (p_it->second >= r) {
        return 0;
      }
      res += p_it->second - l + 1;
      range.first = p_it->first;
      s_[u].erase(p_it);
    }
    if (it != s_[u].end() && it->first <= r) {
      res += r - it->first + 1;
      range.second = it->second;
      s_[u].erase(it);
    }

    s_[u].insert(range);
    // debug("after", s_[u]);
    // debug(r - l + 1, res);
    // if (res != res2) {
    //   debug("diff", res, res2);
    //   debug("add", u, l, r);
    //   debug("old", old_s);
    //   debug("new", s_[u]);
    //   exit(0);
    // }

    return r - l + 1 - res;
  }

  bool Unite(int u, int v) {
    u = GetRoot(u);
    v = GetRoot(v);
    if (u == v) return false;
    if (s_[u].size() > s_[v].size()) swap(u, v);
    sz_[v] += sz_[u];
    root_[u] = v;
    for (auto val : s_[u]) {
      AddRange(v, val.first, val.second);
    }
    s_[u].clear();
    num_comp_--;
    return true;
  }

 private:
  int num_comp_;  // number of connected components
  vector<int> sz_;
  vector<int> root_;
  vector<set<pair<int, int>>> s_;
};

struct Event {
  int t, op;
  int x, y;
  int l, r;

  bool operator < (const Event &other) const {
    if (t != other.t) return t > other.t;
    return op < other.op;
  }

  friend string to_string(const Event &e) {
    string res = "{";
    res += to_string(e.t) + ", ";
    res += to_string(e.op) + ", ";
    res += to_string(e.x) + ", ";
    res += to_string(e.y) + ", ";
    res += to_string(e.l) + ", ";
    res += to_string(e.r) ;
    res += "}";
    return res;
  }
};

void Solve(int test) {
  cerr << "Case #" << test << endl;
  cout << "Case #" << test << ": ";
  int r, c;
  cin >> r >> c;
  vector<vector<int>> h(r, vector<int>(c));
  vector<vector<int>> s(r, vector<int>(c));
  vector<Event> events;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> h[i][j];
      events.push_back({h[i][j], 1, i, j, 0, 0});
    }
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> s[i][j];
    }
  }
  vector<vector<int>> last(r, vector<int>(c, 0));
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int a, b, u;
    cin >> a >> b >> u;
    a--, b--;
    if (last[a][b] < i) {
      events.push_back({s[a][b], 0, a, b, last[a][b], i - 1});
    }
    s[a][b] = u;
    last[a][b] = i;
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      events.push_back({s[i][j], 0, i, j, last[i][j], k - 1});
    }
  }
  sort(events.begin(), events.end());


  auto Encode = [&](int u, int v) {
    return u * c + v;
  };

  auto Decode = [&](int id) {
    return make_pair(id / c, id % c);
  };

  vector<vector<bool>> is_alive(r, vector<bool>(c));

  auto IsInside = [&](int u, int v) {
    return u >= 0 && u < r && v >= 0 && v < c;
  };

  // debug(events);

  DSU dsu(r * c);
  long long res = 0;
  long long cnt = 0;
  for (auto [t, op, x, y, l, r] : events) {
    auto id = Encode(x, y);
    if (op == 0) {
      if (is_alive[x][y]) {
        res += r - l + 1;
        cnt += dsu.AddRange(id, l, r);
      }
    } else {
      assert(!is_alive[x][y]);
      is_alive[x][y] = true;
      for (int i = 0; i < 4; i++) {
        auto xx = x + X[i];
        auto yy = y + Y[i];
        if (!IsInside(xx, yy)) continue;
        if (!is_alive[xx][yy]) continue;
        dsu.Unite(id, Encode(xx, yy));
        // debug("unite", x, y, xx, yy);
      }
    }
  }
  cout << res << ' ' << cnt << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  cerr << tc << endl;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}