#include <bits/stdc++.h>

using namespace std;

template <int MOD>
class Modular {
  static_assert(MOD >= 0, "MOD can't be negative!");

 public:
  explicit Modular(long long v = 0) : v_(v) {
    v_ %= MOD;
    if (v_ < 0) v_ += MOD;
  }

  explicit operator int() const { return v_; }
  explicit operator bool() const { return bool(v_); }

  Modular Inv() const { return Modular(Inverse(v_, MOD)); }
  Modular Power(long long v) const {
    Modular res(1);
    Modular u(*this);
    while (v) {
      if (v & 1) res *= u;
      u *= u;
      v >>= 1;
    }
    return res;
  }

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

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (auto &u : a) cin >> u;
  vector<int> b(m);
  for (auto &u : b) cin >> u;
  auto sum_a = accumulate(a.begin(), a.end(), 0);
  vector<Mint> f(sum_a + 1);
  f[0] = Mint(1);
  for (auto u : a) {
    for (int i = f.size() - 1; i >= u; i--) {
      f[i] -= f[i - u];
    }
  }
  Mint res(n + m);
  for (auto u : b) {
    for (int i = 0; i < f.size(); i++) {
      res -= Mint(u) * f[i] * Mint(u + i).Inv();
    }
  }
  cout << res << endl;
  return 0;
}