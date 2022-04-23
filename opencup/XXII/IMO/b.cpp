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

template <int MOD>
class Modular {
  static_assert(MOD > 0, "MOD must be positive");
  static_assert(MOD * 2 > 0, "MOD is too large for int");

 public:
  Modular() : v_(0) {}
  template <class T, typename enable_if<is_integral<T>::value>::type* = nullptr>
  explicit Modular(T v = 0) : v_((v %= MOD) < 0 ? v + MOD : v) {}

  Modular Inv() const { return Modular(Inverse(v_, MOD)); }

  template <class T, typename enable_if<is_integral<T>::value>::type* = nullptr>
  Modular Power(T v) const {
    Modular res(1), u(*this);
    if (v < 0) {
      v = -v;
      u = u.Inv();
    }
    for (; v; v >>= 1, u *= u)
      if (v & 1) res *= u;
    return res;
  }

  explicit operator int() const { return v_; }
  explicit operator bool() const { return static_cast<bool>(v_); }
  Modular& operator++() { return *this += Modular(1); }
  Modular& operator--() { return *this -= Modular(1); }
  Modular operator++(int) {
    Modular result(*this);
    *this += Modular(1);
    return result;
  }
  Modular operator--(int) {
    Modular result(*this);
    *this -= Modular(1);
    return result;
  }
  Modular operator-() const { return Modular(-v_); }
  Modular operator+() const { return Modular(*this); }
  Modular& operator+=(const Modular& other) {
    if ((v_ += other.v_) >= MOD) v_ -= MOD;
    return *this;
  }
  Modular& operator-=(const Modular& other) {
    if ((v_ -= other.v_) < 0) v_ += MOD;
    return *this;
  }
  Modular& operator*=(const Modular& other) {
    v_ = 1ll * v_ * other.v_ % MOD;
    return *this;
  }
  Modular& operator/=(const Modular& other) { return *this *= other.Inv(); }

  friend bool operator==(const Modular& lhs, const Modular& rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend bool operator!=(const Modular& lhs, const Modular& rhs) {
    return !(lhs == rhs);
  }
  friend Modular operator+(const Modular& lhs, const Modular& rhs) {
    return Modular(lhs) += rhs;
  }
  friend Modular operator-(const Modular& lhs, const Modular& rhs) {
    return Modular(lhs) -= rhs;
  }
  friend Modular operator*(const Modular& lhs, const Modular& rhs) {
    return Modular(lhs) *= rhs;
  }
  friend Modular operator/(const Modular& lhs, const Modular& rhs) {
    return Modular(lhs) /= rhs;
  }
  friend istream& operator>>(istream& in, Modular& number) {
    int64_t v;
    in >> v;
    number = Modular(v);
    return in;
  }
  friend ostream& operator<<(ostream& out, const Modular& number) {
    return out << int(number);
  }
  friend string to_string(const Modular& number) {
    return to_string(static_cast<int>(number));
  }

 private:
  // return u : a * u == 1 (mod m)
  // NOTE: CAN'T assume that 0 <= u < m
  static int Inverse(int a, int m) {
    assert(a && "Divide by zero");
    auto u = 0, v = 1;
    while (a) {
      auto t = m / a;
      m -= t * a;
      swap(a, m);
      u -= t * v;
      swap(u, v);
    }
    assert(m == 1 && "Can't find inversion");
    return u;
  }

  int v_;
};
constexpr int MOD = 998244353;
using Mint = Modular<MOD>;


Mint C[6][6];

template<typename T>
struct Node {
  T value[6];
  T id;
  T delta;

  Node() {}

  void Apply(int l, int r, const pair<T, T> &val) {
    if (val.first != Mint(-1)) { // change element
      value[0] = val.first;
      for (int i = 1; i < 6; i++) {
        value[i] = value[i - 1] * id;
      }
    } else {
      T p[6];
      p[0] = T(1);
      auto now = val.second;
      for (int i = 1; i < 6; i++) {
        p[i] = p[i - 1] * now;
      }
      id += p[1];
      delta += p[1];
      debug(p);
      debug(value);
      debug(id);
      for (int i = 5; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
          value[i] += C[i][j] * p[i - j] * value[j];
        }
      }
    }
  }

  void Pull(const Node &u, const Node &v) {
    for (int i = 0; i < 6; i++) {
      value[i] = u.value[i] + v.value[i];
    }
    id = u.id;
    delta = T(0);
  }

  void Push(int l, int r, Node &u, Node &v) {
    if (!delta) return;
    int m = l + r >> 1;
    u.Apply(l, m, pair(Mint(-1), delta));
    v.Apply(m + 1, r, pair(Mint(-1), delta));
    delta = T(0);
  }
};

int w;
vector<int> pw;

struct NodeW {
  vector<int> value;
  int id;
  int delta;

  NodeW() : value(vector<int>(w, 0)), id(0), delta(0) {}

  void Apply(int l, int r, const pair<int, int> &val) {
    if (val.first != -1) { // change element
      for (int i = 0; i < w; i++) {
        value[i] = val.first * pw[(i + id) % w] % w;
      }
    } else {
      id += val.second;
      if (id >= w) id -= w;
      delta += val.second;
      if (delta >= w) delta -= w;
      rotate(value.begin(), value.begin() + val.second, value.end());
    }
  }

  void Pull(const NodeW &u, const NodeW &v) {
    for (int i = 0; i < w; i++) {
      value[i] = u.value[i] + v.value[i];
    }
    id = u.id;
    delta = 0;
  }

  void Push(int l, int r, NodeW &u, NodeW &v) {
    int m = l + r >> 1;
    u.Apply(l, m, pair(-1, int(delta)));
    v.Apply(m + 1, r, pair(-1, int(delta)));
    delta = 0;
  }
};


template<typename T>
struct SegmentTree {

  /*------------------------------------------------------------------*/
  int n;
  vector<T> t;

  SegmentTree(int n) : n(n) {
    t.assign(n << 2 | 1, {});
    // Init(1, 1, n);
  }

  template <typename F>
  void Update(int node, int l, int r, int x, int y, const pair<F, F> &val) {
    if (x > r || y < l) return;
    if (x <= l && r <= y) {
      t[node].Apply(l, r, val);
      debug(node, l, r, val, t[node].value, t[node].id);
      return;
    }
    auto m = l + r >> 1;
    t[node].Push(l, r, t[node << 1], t[node << 1 | 1]);
    Update(node << 1, l, m, x, y, val);
    Update(node << 1 | 1, m + 1, r, x, y, val);
    t[node].Pull(t[node << 1], t[node << 1 | 1]);
    debug(node, l, r, val, t[node].value, t[node].id);
  }

  T Get(int node, int l, int r, int x, int y) {
    if (x > r || y < l) return T();
    if (x <= l && r <= y) return t[node];
    auto m = l + r >> 1;
    t[node].Push(l, r, t[node << 1], t[node << 1 | 1]);
    T p1 = Get(node << 1, l, m, x, y);
    T p2 = Get(node << 1 | 1, m + 1, r, x, y);
    T res;
    res.Pull(p1, p2);
    return res;
  }
};

int n, k;
int q;
vector<int> a;
vector<pair<int, int>> vals;
vector<pair<int, int>> queries;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 || j == i) C[i][j] = Mint(1);
      else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }

  cin >> n >> k >> w;
  // n = 100000;
  // k = 5;
  // w = 5;

  for (int i = 0; i < w; i++) {
    int val = 1;
    for (int j = 0; j < k; j++) {
      val = val * i % w;
    }
    pw.push_back(val);
  }
  debug(pw);

  a.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    // a[i] = 100000;
    vals.push_back({a[i], i});
  }

  cin >> q;
  // q = 100000;
  queries.resize(q);
  for (int i = 0; i < q; i++) {
    cin >> queries[i].first >> queries[i].second;
    // queries[i].first = rand() % n + 1;
    // queries[i].second = 100000;
    queries[i].first--;
    vals.push_back({queries[i].second, i + n});
  }

  sort(vals.begin(), vals.end());
  debug(vals);

  SegmentTree<Node<Mint>> s(vals.size());
  SegmentTree<NodeW> sw(vals.size());

  auto Update = [&](int pos, int value, int delta) {
    debug("change value ", pos, value);
    s.Update(1, 0, vals.size() - 1, pos, pos, pair(Mint(value), Mint(0)));
    debug(s.t[1].value[k]);
    debug("change delta ", pos, delta);
    s.Update(1, 0, vals.size() - 1, pos, vals.size() - 1, pair(Mint(-1), Mint(delta)));
    debug(s.t[1].value[k]);
    sw.Update(1, 0, vals.size() - 1, pos, pos, pair(value, 0));
    sw.Update(1, 0, vals.size() - 1, pos, vals.size() - 1, pair(-1, (delta % w + w) % w));
  };

  vector<int> old_pos(n);

  auto inv_w = Mint(w).Inv();

  for (int i = 0; i < n; i++) {
    int pos = lower_bound(vals.begin(), vals.end(), pair(a[i], i)) - vals.begin();
    debug(i, pos);
    Update(pos, a[i], 1);
    old_pos[i] = pos;
    debug(s.t[1].value[k], sw.t[1].value[0]);
  }


  for (int i = 0; i < q; i++) {
    auto [id, value] = queries[i];
    debug(id, value, "###################");
    Update(old_pos[id], 0, -1);
    debug(s.t[1].value[k], sw.t[1].value[0]);
    int pos = lower_bound(vals.begin(), vals.end(), pair(value, i + n)) - vals.begin();
    old_pos[id] = pos;
    Update(pos, value, 1);
    debug(s.t[1].value[k], sw.t[1].value[0]);
    cout << (s.t[1].value[k] - Mint(int(sw.t[1].value[0]))) * inv_w << '\n'; 
  }
  return 0;
}