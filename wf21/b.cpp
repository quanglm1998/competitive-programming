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

class DSU {
 public:
  explicit DSU(int n) : num_comp_(n), root_(n, -1), sz_(n, 1), ls_(n) {
    for (int i = 0; i < n; i++) {
      ls_[i].insert(i);
    }
  }

  int num_comp() const { return num_comp_; }
  int sz(int u) { return sz_[GetRoot(u)]; }
  set<int>& ls(int u)  { return ls_[GetRoot(u)]; }

  int GetRoot(int u) { return ~root_[u] ? root_[u] = GetRoot(root_[u]) : u; }

  bool Unite(int u, int v) {
    u = GetRoot(u);
    v = GetRoot(v);
    if (u == v) return false;
    if (ls_[u].size() > ls_[v].size()) swap(u, v);
    for (auto val : ls_[u]) ls_[v].insert(val);
    sz_[v] += sz_[u];
    root_[u] = v;
    num_comp_--;
    return true;
  }

 private:
  int num_comp_;  // number of connected components
  vector<int> sz_;
  vector<int> root_;
  vector<set<int>> ls_;
};

template <typename T>
struct Node {
  Node() { min_val = add = T(0); }

  static Node worst() {
    Node res;
    res.min_val = numeric_limits<T>::max();
    res.add = T(0);
    return res;
  }

  template <typename S>
  void Apply(int l, int r, const S &val) {
    min_val += val;
    add += val;
  }

  void Pull(int l, int r, const Node &u, const Node &v) {
    min_val = min(u.min_val, v.min_val);
    add = T(0);
  }

  void Push(int l, int r, Node &u, Node &v) {
    if (!add) return;
    int m = l + r >> 1;
    u.Apply(l, m, add);
    v.Apply(m + 1, r, add);
    add = T(0);
  }

  T min_val;
  T add;
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

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;

  DSU dsu(n);
  SegmentTree<Node<int>> t(n);
  t.Update(0, n - 1, +1);

  auto Update = [&](int u, int delta) {
    t.Update(*dsu.ls(u).begin(), *dsu.ls(u).rbegin(), delta);
  };

  auto Unite = [&](int u, int v) {
    Update(u, -1);
    Update(v, -1);
    dsu.Unite(u, v);
    Update(u, +1);
  };

  int cmp_val;
  auto NotGreater = [&](const Node<int>& t, int val) {
    return t.min_val <= val;
  };

  while (m--) {
    int op, u, v;
    cin >> op >> u >> v;
    u--, v--;
    // debug(op, u, v);
    if (op == 1) {
      while (dsu.GetRoot(u) != dsu.GetRoot(v)) {
        auto lv_u = t.Get(u, u).min_val;
        auto lv_v = t.Get(v, v).min_val;
        // debug(u, v, lv_u, lv_v);
        if (lv_u == lv_v) {
          if (lv_u == 1) {
            Unite(u, v);
            break;
          }
          auto uu = t.RightMostHas<int>(0, u, NotGreater, lv_u - 1);
          auto vv = t.RightMostHas<int>(0, v, NotGreater, lv_v - 1);
          if (uu == vv) {
            Unite(u, v);
            if (u > v) swap(u, v);
            auto &ls = dsu.ls(uu);
            auto it = ls.upper_bound(u);
            if (it != ls.end() && *it < v) {
              Unite(u, uu);
            }
            break;
          }
          Unite(uu, u);
          Unite(vv, v);
          continue;
        }
        if (lv_u < lv_v) {
          swap(lv_u, lv_v);
          swap(u, v);
        }
        int w = t.RightMostHas<int>(0, u, NotGreater, lv_u - 1);
        Unite(u, w);
      }
    } else {
      cout << (dsu.GetRoot(u) == dsu.GetRoot(v));
    }
  }
  cout << '\n';
  return 0;
}