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
  int n;
  cin >> n;
  vector<Mint> fac(n + 1, Mint(1));
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * Mint(i);
  vector<Mint> inv_fac(n + 1);
  inv_fac[n] = fac[n].Inv();
  for (int i = n - 1; i >= 0; i--) inv_fac[i] = inv_fac[i + 1] * Mint(i + 1);
  vector<Mint> p2(n + 1, Mint(1));
  for (int i = 1; i <= n; i++) p2[i] = p2[i - 1] * Mint(2);
  vector<Mint> f(n + 1, Mint(1));
  Mint sum_f = Mint(1);
  for (int i = 1; i <= n; i++) {
    f[i] = fac[i - 1] * p2[i - 1] * sum_f;
    sum_f += f[i] * inv_fac[i] * p2[i].Inv();
  }

  auto Binom = [&](int n, int k) {
    if (k > n || k < 0) return Mint(0);
    return fac[n] * inv_fac[k] * inv_fac[n - k];
  };

  Mint res(0);
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    if (u) {
      Mint now(1);
      now *= f[i];
      now *= f[n - i - 1];
      now *= Binom(n - 1, i);
      res += now;
    }
  }

  cout << res << '\n';
  return 0;
}