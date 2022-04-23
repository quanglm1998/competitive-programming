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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
// change null_type to T if we want to use map instead
// find_by_order(k) returns an iterator to the k-th element (0-indexed)
// order_of_key(k) returns numbers of item being strictly smaller than k
template <typename T>
using OrderedSet =
  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


struct Node {
  int min_val = 0;
  int delta = 0;

  Node() {}

  template<typename T>
  void Apply(int l, int r, const T &val) {
    min_val += val;
    delta += val;
  }

  void Pull(const Node &u, const Node &v) {
    min_val = min(u.min_val, v.min_val);
    delta = 0;
  }

  void Push(int l, int r, Node &u, Node &v) {
    u.min_val += delta;
    v.min_val += delta;
    u.delta += delta;
    v.delta += delta;
    delta = 0;
  }

  friend string to_string(const Node &u) {
    return "(" + to_string(u.min_val) + ' ' + to_string(u.delta) + ")";
  }
};

struct SegmentTree {
  int n;
  vector<Node> t;

  SegmentTree(int n) : n(n) {
    t.assign(n << 2 | 1, {});
  }

  template<typename T>
  void Add(int node, int l, int r, int x, int y, const T &val) {
    if (x > r || y < l) return;
    if (x <= l && r <= y) {
      t[node].Apply(l, r, val);
      debug("add", node, l, r, x, y, t[node]);
      return;
    }
    auto m = (l + r) / 2;
    t[node].Push(l, r, t[node << 1], t[node << 1 | 1]);
    Add(node << 1, l, m, x, y, val);
    Add(node << 1 | 1, m + 1, r, x, y, val);
    t[node].Pull(t[node << 1], t[node << 1 | 1]);
    debug("add", node, l, r, x, y, t[node]);
  }

  Node Get(int node, int l, int r, int x, int y) {
    if (x > r || y < l) return Node();
    if (x <= l && r <= y) return t[node];
    auto m = (l + r) / 2;
    t[node].Push(l, r, t[node << 1], t[node << 1 | 1]);
    Node p1 = Get(node << 1, l, m, x, y);
    Node p2 = Get(node << 1 | 1, m + 1, r, x, y);
    Node res;
    res.Pull(p1, p2);
    return res;
  }
};


void Solve(int test) {
  cout << "Case #" << test << ": ";
  int n, m, k, S;
  cin >> n >> m >> k >> S;
  k--;
  vector<string> s(n);
  for (auto &u : s) {
    cin >> u;
  }
  vector<OrderedSet<int>> car_pos(m);
  SegmentTree st(n * 2 + 1);

  auto GetLower = [&](int y) {
    int full_lower = k + n + 1;
    if (car_pos[y].size() >= k + 1) {
      full_lower = *car_pos[y].find_by_order(k);
    }
    return full_lower;
  };

  auto GetUpper = [&](int y) {
    int full_upper = k - n - 1;
    if (car_pos[y].size() >= n - k) {
      full_upper = *car_pos[y].find_by_order(car_pos[y].size() - (n - k));
    }
    return full_upper;
  };

  auto Add = [&](int x, int y) {
    debug("add", x, y);
    int full_upper = GetUpper(y);
    int full_lower = GetLower(y);
    debug(full_upper, full_lower);
    if (full_upper < x && x < full_lower) {
      st.Add(1, 0, n * 2, x + n - k, x + n - k, 1);
    }
    car_pos[y].insert(x);
    int nxt_upper = GetUpper(y);
    int nxt_lower = GetLower(y);
    debug(nxt_upper, nxt_lower);
    st.Add(1, 0, n * 2, full_upper + 1 + n - k, nxt_upper - 1 + n - k, 1);
    st.Add(1, 0, n * 2, nxt_lower + 1 + n - k, full_lower - 1 + n - k, 1);
  };

  auto Remove = [&](int x, int y) {
    debug("remove", x, y);
    int full_upper = GetUpper(y);
    int full_lower = GetLower(y);
    car_pos[y].erase(x);
    int nxt_upper = GetUpper(y);
    int nxt_lower = GetLower(y);
    debug(full_upper, full_lower);
    debug(nxt_upper, nxt_lower);
    st.Add(1, 0, n * 2, nxt_upper + 1 + n - k, full_upper - 1 + n - k, -1);
    st.Add(1, 0, n * 2, full_lower + 1 + n - k, nxt_lower - 1 + n - k, -1);
    if (nxt_upper < x && x < nxt_lower) {
      st.Add(1, 0, n * 2, x + n - k, x + n - k, -1);
    }
  };

  for (int i = k - n; i <= k + n; i++) {
    st.Add(1, 0, n * 2, i + n - k, i + n - k, abs(k - i));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == 'X') Add(i, j);
    }
  }


  long long res = 0;
  while (S--) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    debug("change", x, y);
    if (s[x][y] == 'X') {
      s[x][y] = '.';
      Remove(x, y);
    } else {
      s[x][y] = 'X';
      Add(x, y);
    }
    res += st.t[1].min_val;
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