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
constexpr int MOD = 998244353;
using Mint = Modular<MOD>;

struct NTT {
 public:
  NTT() {
    max_base_ = __builtin_ctz(MOD - 1);
    auto root = Mint(2);
    while (root.Power(1 << max_base_) != Mint(1) ||
           root.Power(1 << max_base_ - 1) == Mint(1))
      root++;
    for (int i = 0; i < max_base_; i++, root *= root) roots_.push_back(root);
    reverse(roots_.begin(), roots_.end());
    rev_.resize(1 << max_base_);
    for (int i = 0; i < (1 << max_base_); i++)
      rev_[i] = (rev_[i >> 1] >> 1) + ((i & 1) << (max_base_ - 1));
  }

  void FFT(vector<Mint>& a, bool inverse) {
    auto n = static_cast<int>(a.size());
    assert(n == (n & -n) && "size of a is not a power of 2");
    auto base = n == 1 ? 0 : 32 - __builtin_clz(n - 1);
    assert(base <= max_base_ && "size of a is to large");
    auto shift = max_base_ - base;
    for (int i = 0; i < n; i++)
      if (i < (rev_[i] >> shift)) swap(a[i], a[rev_[i] >> shift]);
    for (int i = 0; i < base; i++)
      for (auto [j, w] = pair(0, Mint(1)); j < 1 << i; j++, w *= roots_[i])
        for (int k = j; k < n; k += 2 << i) {
          auto u = a[k];
          auto v = a[k + (1 << i)] * w;
          a[k] = u + v;
          a[k + (1 << i)] = u - v;
        }
    if (inverse) {
      reverse(a.begin() + 1, a.end());
      auto inv_n = Mint(n).Inv();
      for (auto& u : a) u *= inv_n;
    }
  }

  vector<Mint> Mult(vector<Mint> a, vector<Mint> b) {
    auto n = static_cast<int>(a.size() + b.size()) - 1;
    auto cur_base = n == 1 ? 0 : 32 - __builtin_clz(n - 1);
    a.resize(1 << cur_base), b.resize(1 << cur_base);
    FFT(a, false);
    FFT(b, false);
    for (int i = 0; i < 1 << cur_base; i++) a[i] *= b[i];
    FFT(a, true);
    a.resize(n);
    return a;
  }

 private:
  int max_base_;
  vector<Mint> roots_;  // 0: -1, 1: i, ...
  vector<int> rev_;
} ntt;

const int N = 250010;

int n;
int a[N];
Mint fac[N];

typedef pair<vector<Mint>, vector<Mint>> pv;

pv Solve(int l, int r) {
  if (l == r) return {{Mint(0), Mint(1ll * a[l] * l)}, {Mint(1), Mint(a[l])}};
  int m = l + r >> 1;
  auto L = Solve(l, m);
  auto R = Solve(m + 1, r);
  auto X = ntt.Mult(L.first, R.second);
  assert(X.size() >= R.first.size());
  for (int i = 0; i < R.first.size(); i++) X[i] += R.first[i];
  auto Y = ntt.Mult(L.second, R.second);
  return {X, Y};
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  fac[0] = Mint(1);
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * Mint(i);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  auto P = Solve(1, n - 2);

  auto res = Mint(0);
  for (int i = 1; i < n - 2; i++) {
    auto now = P.first[i] - P.second[i];
    now *= fac[(i + 2) - 1] * fac[n - (i + 2) - 1];
    res += now;
  }
  auto prod = Mint(1);
  for (int i = 1; i <= n - 2; i++) prod *= Mint(a[i]);
  res += prod * fac[n - 1];
  res /= Mint(2);
  res += fac[n - 2];
  res *= Mint(1ll * a[n - 1] * a[n]);
  cout << res << '\n';
  return 0;
}