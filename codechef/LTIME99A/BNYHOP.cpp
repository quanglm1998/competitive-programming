#include <bits/stdc++.h>

using namespace std;

template <int MOD>
class Modular {
  static_assert(MOD >= 0, "MOD can't be negative!");
  static_assert(MOD * 2 > 0, "MOD is too large for int");

 public:
  explicit Modular(long long v = 0) : v_((v %= MOD) < 0 ? v + MOD : v) {}

  Modular Inv() const { return Modular(Inverse(v_, MOD)); }
  Modular Power(long long v) const {
    Modular res(1), u(*this);
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
  friend std::istream& operator>>(std::istream& in, Modular& number) {
    long long v;
    in >> v;
    number = Modular(v);
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Modular& number) {
    return out << int(number);
  }
  friend string to_string(const Modular& number) {
    return to_string(int(number));
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
constexpr int MOD = (int)1e9 + 7;
using Mint = Modular<MOD>;

// 1-indexed
// Can't add when x = 0
// Ensure that T supports operator: + -
template <typename T = int>
class BIT {
 public:
  explicit BIT(int n = 0) : n_(n), t_(n + 1, T(0)) {}

  void Add(int x, T v) {
    for (; x <= n_; x += x & -x) t_[x] += v;
  }

  // [l, r] INCLUSIVELY
  void Add(int l, int r, T v) {
    assert(l <= r && l >= 0 && r <= n_);
    Add(l, v);
    Add(r + 1, -v);
  }

  T Get(int x) {
    assert(x >= 0 && x <= n_);
    T res = T(0);
    for (; x; x -= x & -x) res += t_[x];
    return res;
  }

  // [l, r] INCLUSIVELY
  T Get(int l, int r) {
    assert(l <= r && r <= n_ && l >= 0);
    return Get(r) - (l ? Get(l - 1) : T(0));
  }

 private:
  int n_;
  vector<T> t_;
};

void Solve(int test) {
  int n;
  cin >> n;
  vector<vector<int>> adj(n + 1, vector<int>());
  for (int i = 2; i <= n; i++) {
    int u;
    cin >> u;
    adj[u].push_back(i);
  }
  vector<int> a(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> order(n + 1);
  iota(order.begin(), order.end(), 0);
  sort(order.begin() + 1, order.end(), [&](int u, int v) {
    return a[u] > a[v];
  });
  vector<int> in(n + 1), out(n + 1);
  int cur = 0;

  function<void(int)> Dfs = [&](int u) {
    in[u] = ++cur;
    for (auto v : adj[u]) {
      Dfs(v);
    }
    out[u] = cur;
  };
  Dfs(1);

  BIT<Mint> t1(n), t2(n);
  Mint res(0);
  for (int i = 1; i <= n; i++) {
    int u = order[i];
    Mint cur = t1.Get(in[u]) + t2.Get(in[u], out[u]);
    res += cur;
    cur++;
    t1.Add(in[u], out[u], cur);
    t2.Add(in[u], cur);
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