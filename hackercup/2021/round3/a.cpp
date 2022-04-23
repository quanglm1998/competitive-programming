#include <bits/stdc++.h>

using namespace std;

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
constexpr int MOD = (int)1e9 + 7;
using Mint = Modular<MOD>;


void Solve(int test) {
  cout << "Case #" << test << ": ";
  int n, m;
  cin >> n >> m;
  set<pair<int, int>> s;
  for (int i = 0; i < n; i++) {
    s.insert({i, i});
  }

  auto Get = [&](int u) {
    auto it = s.lower_bound({u + 1, -1});
    return prev(it);
  };

  Mint cur = Mint(n) * Mint(n - 1) / Mint(2);
  Mint res(1);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    if (u > v) swap(u, v);
    auto uu = Get(u);
    auto vv = Get(v);
    vector<pair<int, int>> ls;
    for (auto it = uu; it != next(vv); it++) {
      ls.push_back(*it);
    }
    assert(!ls.empty());
    for (auto val : ls) {
      s.erase(val);
    }
    s.insert({ls[0].first, ls.back().second});

    int sz = ls[0].second - ls[0].first + 1;
    for (int i = 1; i < ls.size(); i++) {
      cur += Mint(sz) * Mint(ls[i].second - ls[i].first + 1);
      sz += ls[i].second - ls[i].first + 1;
    }
    res *= cur;
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