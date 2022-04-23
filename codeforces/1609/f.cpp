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

// Node example for range adding and range sum getting
template <typename T>
struct Node {
  Node() { sum = add = T(0); }

  static Node worst() {
    Node res;
    return res;
  }

  template <typename S>
  void Apply(int l, int r, const S &val) {
    sum += val * T(r - l + 1);
    add += val;
  }

  void Pull(int l, int r, const Node &u, const Node &v) {
    sum = u.sum + v.sum;
    add = T(0);
  }

  void Push(int l, int r, Node &u, Node &v) {
    if (!add) return;
    int m = l + r >> 1;
    u.Apply(l, m, add);
    v.Apply(m + 1, r, add);
    add = T(0);
  }

  T sum;
  T add;
};

const long long INF = 2e18;

struct NodeMin {

  NodeMin() { val = {INF, -1};}

  static NodeMin worst() {
    return NodeMin();
  }

  void Apply(int l, int r, long long u) {
    val = {u, l};
  }

  void Pull(int l, int r, const NodeMin &u, const NodeMin&v) {
    val = min(u.val, v.val);
  }

  void Push(int l, int r, NodeMin &u, NodeMin &v) {}

  pair<long long, int> val;
};

struct NodeMax {

  NodeMax() { val = { -INF, -1};}

  static NodeMax worst() {
    return NodeMax();
  }

  void Apply(int l, int r, long long u) {
    val = {u, l};
  }

  void Pull(int l, int r, const NodeMax &u, const NodeMax&v) {
    val = max(u.val, v.val);
  }

  void Push(int l, int r, NodeMax &u, NodeMax &v) {}

  pair<long long, int> val;
};

template <typename T>
class SegmentTree {
 public:
  explicit SegmentTree(int n) : n_(n) { t_.assign(n_ << 2 | 1, T()); }

  template <typename S>
  SegmentTree(int n, const vector<S> &val) : n_(n) {
    t_.assign(n_ << 2 | 1, T());
    Init(1, 0, n_ - 1, val);
  }

  // apply `val` to all position in range [x, y]
  template <typename S>
  void Update(int x, int y, const S &val) {
    Update(1, 0, n_ - 1, x, y, val);
  }

  T Get(int x, int y) { return Get(1, 0, n_ - 1, x, y); }

  // LeftMostHas/RightMostHas returns the left/right most position v
  // such that:
  //   - v is in the segment [x, y]
  //   - and f(u) = true if node u contains position v
  // Returns -1 if we can't find such position v
  template <typename S>
  int LeftMostHas(int x, int y, const function<bool(const T &, const S &)> &f,
                  const S &val) {
    return LeftMostHas(1, 0, n_ - 1, x, y, f, val);
  }
  template <typename S>
  int RightMostHas(int x, int y, const function<bool(const T &, const S &)> &f,
                   const S &val) {
    return RightMostHas(1, 0, n_ - 1, x, y, f, val);
  }

 private:
  template <typename S>
  void Init(int node, int l, int r, const vector<S> &val) {
    if (l == r) {
      t_[node].Apply(l, r, val[l]);
      return;
    }
    auto m = l + r >> 1;
    Init(node << 1, l, m, val);
    Init(node << 1 | 1, m + 1, r, val);
    t_[node].Pull(l, r, t_[node << 1], t_[node << 1 | 1]);
  }

  template <typename S>
  void Update(int node, int l, int r, int x, int y, const S &val) {
    if (x > r || y < l) return;
    if (x <= l && r <= y) {
      t_[node].Apply(l, r, val);
      return;
    }
    auto m = l + r >> 1;
    t_[node].Push(l, r, t_[node << 1], t_[node << 1 | 1]);
    Update(node << 1, l, m, x, y, val);
    Update(node << 1 | 1, m + 1, r, x, y, val);
    t_[node].Pull(l, r, t_[node << 1], t_[node << 1 | 1]);
  }

  T Get(int node, int l, int r, int x, int y) {
    if (x > r || y < l) return T::worst();
    if (x <= l && r <= y) return t_[node];
    auto m = l + r >> 1;
    t_[node].Push(l, r, t_[node << 1], t_[node << 1 | 1]);
    T p1 = Get(node << 1, l, m, x, y);
    T p2 = Get(node << 1 | 1, m + 1, r, x, y);
    T res;
    res.Pull(l, r, p1, p2);
    return res;
  }

  template <typename S>
  int LeftMostHas(int node, int l, int r, int x, int y,
                  const function<bool(const T &, const S &)> &f, const S &val) {
    if (x > r || y < l) return -1;
    if (!f(t_[node], val)) return -1;
    if (l == r) return l;
    int m = l + r >> 1;
    t_[node].Push(l, r, t_[node << 1], t_[node << 1 | 1]);
    if (int res = LeftMostHas(node << 1, l, m, x, y, f, val); res != -1) {
      return res;
    }
    return LeftMostHas(node << 1 | 1, m + 1, r, x, y, f, val);
  }

  template <typename S>
  int RightMostHas(int node, int l, int r, int x, int y,
                   const function<bool(const T &, const S &)> &f,
                   const S &val) {
    if (x > r || y < l) return -1;
    if (!f(t_[node], val)) return -1;
    if (l == r) return l;
    int m = l + r >> 1;
    t_[node].Push(l, r, t_[node << 1], t_[node << 1 | 1]);
    if (int res = RightMostHas(node << 1 | 1, m + 1, r, x, y, f, val);
        res != -1) {
      return res;
    }
    return RightMostHas(node << 1, l, m, x, y, f, val);
  }

  int n_;
  vector<T> t_;
};


template <typename T>
class BIT {
 public:
  explicit BIT(int n) : n_(n), t_(n, T(0)) {}

  void Add(int x, T v) {
    assert(x >= 0);
    for (; x < n_; x += (x + 1) & -(x + 1)) t_[x] += v;
  }

  // [l, r] INCLUSIVELY
  void Add(int l, int r, T v) {
    assert(l <= r && l >= 0 && r < n_);
    Add(l, v);
    Add(r + 1, -v);
  }

  T Get(int x) const {
    assert(x >= 0 && x < n_);
    T res(0);
    for (; x >= 0; x -= (x + 1) & -(x + 1)) res += t_[x];
    return res;
  }

  // [l, r] INCLUSIVELY
  T Get(int l, int r) const {
    assert(l <= r && r < n_ && l >= 0);
    return Get(r) - (l ? Get(l - 1) : T(0));
  }

 private:
  int n_;
  vector<T> t_;
};


struct Rectangle {
  int x, y, l, h;
};

string to_string(Rectangle r) {
  return "{" + to_string(r.x) + ", " +
         to_string(r.y) + ", " +
         to_string(r.l) + ", " +
         to_string(r.h) + "}";
}

struct Event {
  int t;
  int type;
  int l, h;
  int add_i, add_unit;
  int get_delta;
};

string to_string(Event e) {
  return "{" + to_string(e.t) + ", " +
         to_string(e.type) + ", " +
         to_string(e.l) + ", " +
         to_string(e.h) + ", " +
         to_string(e.add_unit) + ", " +
         to_string(e.add_i) + ", " +
         to_string(e.get_delta) + "}";
}

template<typename T>
void BuildRect(int l, int r, T &t, vector<vector<Rectangle>> &rects) {
  if (l > r) return;
  auto [val, mid] = t.Get(l, r).val;
  assert(mid != -1);
  auto num_bit = __builtin_popcountll(val);
  rects[num_bit].push_back({l, mid, mid, r});
  BuildRect(l, mid - 1, t, rects);
  BuildRect(mid + 1, r, t, rects);
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<long long> a(n);
  for (auto &u : a) {
    cin >> u;
  }

  vector<vector<Rectangle>> min_rect(64);
  vector<vector<Rectangle>> max_rect(64);

  auto BuildMinRect = [&]() {
    SegmentTree<NodeMin> t_min(n, a);
    BuildRect(0, n - 1, t_min, min_rect);
  };
  BuildMinRect();

  auto BuildMaxRect = [&]() {
    SegmentTree<NodeMax> t_max(n, a);
    BuildRect(0, n - 1, t_max, max_rect);
  };
  BuildMaxRect();

  long long res = 0;

  vector<BIT<long long>> t_unit(2, BIT<long long>(n));
  vector<BIT<long long>> t_i(2, BIT<long long>(n));
  auto Solve = [&](int u) {
    vector<Event> events;
    for (const auto &r : min_rect[u]) {
      events.push_back({r.x, 0, r.l, r.h, 1, -r.x + 1, 0});
      events.push_back({r.y + 1, 0, r.l, r.h, -1, r.y, 0});
    }
    for (const auto &r : max_rect[u]) {
      events.push_back({r.x - 1, 1, r.l, r.h, 0, 0, -1});
      events.push_back({r.y, 1, r.l, r.h, 0, 0, 1});
    }
    sort(events.begin(), events.end(), [&](const Event & u, const Event & v) {
      if (u.t != v.t) return u.t < v.t;
      return u.type < v.type;
    });

    auto Update = [&](int l, int r, int a, vector<BIT<long long>> &t) {
      t[0].Add(l, 1ll * a * (1 - l));
      t[1].Add(l, 1ll * a);

      t[0].Add(r + 1, 1ll * a * r);
      t[1].Add(r + 1, -1ll * a);
    };

    auto Get = [&](int l, int r, vector<BIT<long long>> &t) {
      long long R = t[0].Get(r) + t[1].Get(r) * r;
      long long L = l == 0 ? 0 : t[0].Get(l - 1) + t[1].Get(l - 1) * (l - 1);
      return R - L; 
    };

    for (auto &event : events) {
      debug(event);
      if (event.type == 0) { // update
        Update(event.l, event.h, event.add_unit, t_unit);
        Update(event.l, event.h, event.add_i, t_i);
      } else { // get
        res += Get(event.l, event.h, t_unit) * event.get_delta;
        res += Get(event.l, event.h, t_i) * event.get_delta * event.t;
      }
    }
    for (auto &event : events) {
      if (event.type == 0) {
        Update(event.l, event.h, -event.add_unit, t_unit);
        Update(event.l, event.h, -event.add_i, t_i);
      }
    }
  };

  for (int i = 0; i < 64; i++) {
    debug("solve", i);
    Solve(i);
  }

  cout << res << '\n';
  return 0;
}