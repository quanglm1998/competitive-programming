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
  explicit DSU(int n) : num_comp_(n), root_(n, -1), sz_(n, 1), has_(n, 0) {}

  int num_comp() const { return num_comp_; }
  int sz(int u) { return sz_[GetRoot(u)]; }
  bool has(int u) { return has_[GetRoot(u)]; }

  int GetRoot(int u) { return ~root_[u] ? root_[u] = GetRoot(root_[u]) : u; }

  void Set(int u) {
    has_[GetRoot(u)] = true;
  }

  bool Unite(int u, int v) {
    u = GetRoot(u);
    v = GetRoot(v);
    if (u == v) return false;
    sz_[v] += sz_[u];
    root_[u] = v;
    has_[v] |= has_[u];
    num_comp_--;
    return true;
  }

 private:
  int num_comp_;  // number of connected components
  vector<int> sz_;
  vector<int> root_;
  vector<int> has_;
};

struct Event {
  int t, op;
  int x, y;

  bool operator < (const Event &other) const {
    if (t != other.t) return t > other.t;
    return op < other.op;
  }

  friend string to_string(const Event &e) {
    string res = "{";
    res += to_string(e.t) + ", ";
    res += to_string(e.op) + ", ";
    res += to_string(e.x) + ", ";
    res += to_string(e.y);
    res += "}";
    return res;
  }
};

void Solve(int test) {
  cout << "Case #" << test << ": ";
  int r, c;
  cin >> r >> c;
  vector<vector<int>> h(r, vector<int>(c));
  vector<vector<int>> s(r, vector<int>(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> h[i][j];
    }
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> s[i][j];
    }
  }

  long long tot_res = 0, tot_cnt = 0;
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int a, b, u;
    cin >> a >> b >> u;
    a--, b--;
    s[a][b] = u;

    vector<Event> events;
    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        events.push_back({h[x][y], 1, x, y});
        events.push_back({s[x][y], 0, x, y});
      }
    }
    sort(events.begin(), events.end());

    auto Encode = [&](int u, int v) {
      return u * c + v;
    };

    vector<vector<bool>> is_alive(r, vector<bool>(c));

    auto IsInside = [&](int u, int v) {
      return u >= 0 && u < r && v >= 0 && v < c;
    };

    // debug(events);

    DSU dsu(r * c);
    sort(events.begin(), events.end());
    int res = 0;
    int min_num = 0;
    for (auto [t, op, x, y] : events) {
      auto id = Encode(x, y);
      if (op == 0) {
        if (is_alive[x][y]) {
          res++;
          if (!dsu.has(id)) {
            dsu.Set(id);
            min_num++;
          }
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
    tot_res += res;
    tot_cnt += min_num;
  }
  cout << tot_res << ' ' << tot_cnt << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}