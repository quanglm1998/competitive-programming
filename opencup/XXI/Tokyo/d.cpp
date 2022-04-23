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

  // Inverse polynomial of F(x)
  // I_n(x): I_n(x) * F(x) = 1 (mod x^n)
  // I_1(0) = 1 / F(0)
  // I_2n(x) = 2I_n(x) - I_n(x)^2 * F(x)
  vector<Mint> PolyInv(vector<Mint> F) {
    auto n = static_cast<int>(F.size());
    auto cur_base = n == 1 ? 0 : 32 - __builtin_clz(n - 1);
    F.resize(1 << cur_base);
    vector<Mint> I = {F[0].Inv()};
    for (int k = 1; k < 1 << cur_base; k <<= 1) {
      vector<Mint> foo(F.begin(), F.begin() + (k * 2));
      I = Inv2n(I, foo);
    }
    I.resize(n);
    return I;
  }

  // Square root polynomial of F(x)
  // S_n(x) : S_n(x)^2 = F(x) (mod x^n)
  // S_n(0) = sqrt(F(0))
  // S_2n(x) = (S_n(x) + F(x) / S_n(x)) / 2
  vector<Mint> PolySqrt(vector<Mint> F) {
    auto n = static_cast<int>(F.size());
    auto cur_base = n == 1 ? 0 : 32 - __builtin_clz(n - 1);
    F.resize(1 << cur_base);
    vector<Mint> S = {Mint(1)};  // CHANGE THIS to sqrt(F[0]) <-----------------
    assert(S[0] * S[0] == F[0] && "Can't find sqrt(F[0])");
    vector<Mint> IS = {S[0].Inv()};
    for (int k = 1; k < 1 << cur_base; k <<= 1) {
      vector<Mint> foo(F.begin(), F.begin() + (k * 2));
      auto bar = S;
      bar.resize(bar.size() * 2);
      S = Sqrt2n(S, Inv2n(IS, bar), foo);
      IS = Inv2n(IS, S);
    }
    return S;
  }

 private:
  // calculate I_2n(x) given I_n(x)
  // ensure that I_n(x) * F(x) = 1 (mod x^I.size()) and F.size() = 2I.size()
  vector<Mint> Inv2n(const vector<Mint>& I, const vector<Mint>& F) {
    assert(I.size() * 2 == F.size());
    auto res = Mult(I, F);
    res.resize(F.size());
    for (auto& u : res) u = -u;
    res[0] += Mint(2);
    res = Mult(res, I);
    res.resize(F.size());
    return res;
  }

  // calculate S_2n(x) given S_n(x), 1 / S_n(x) = IS(x)
  // ensure that S_n(x)^2 = F(x) (mod x^I.size()) and F.size() = 2S.size() and
  // 2S.size() == IS.size()
  vector<Mint> Sqrt2n(const vector<Mint>& S, const vector<Mint>& IS,
                      const vector<Mint>& F) {
    assert(S.size() * 2 == F.size());
    assert(S.size() * 2 == IS.size());
    auto res = Mult(F, IS);
    res.resize(F.size());
    for (int i = 0; i < S.size(); i++) res[i] += S[i];
    const static Mint INV_2 = Mint(2).Inv();
    for (auto& u : res) u *= INV_2;
    return res;
  }

  int max_base_;
  vector<Mint> roots_;  // 0: -1, 1: i, ...
  vector<int> rev_;
} ntt;

typedef vector<Mint> vm;

vm operator+(const vm &a, const vm &b) {
  vm res(max(a.size(), b.size()));
  for (int i = 0; i < res.size(); i++) {
    res[i] = (i < a.size() ? a[i] : Mint(0)) + (i < b.size() ? b[i] : Mint(0));
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<Mint> a(n);
  for (auto &u : a) cin >> u;
  vector<Mint> b(n);
  for (auto &u : b) cin >> u;
  vector<Mint> c(n);
  for (auto &u : c) cin >> u;


  function<pair<vm, vm>(int, int)> Init = [&](int l, int r) {
    if (l == r) {
      vm numer = {Mint(c[l])};
      vm denom = {Mint(1), Mint(-a[l])};
      return pair(numer, denom);
    }
    int m = l + r >> 1;
    auto L = Init(l, m);
    auto R = Init(m + 1, r);
    vm numer = ntt.Mult(L.first, R.second) + ntt.Mult(R.first, L.second);
    vm denom = ntt.Mult(L.second, R.second);
    return pair(numer, denom);
  };

  auto C = Init(0, n - 1);
  auto A = ntt.Mult(C.first, ntt.PolyInv(C.second));
  A.resize(n + 1);

  function<pair<vm, vm>(vm, int, int)> Solve = [&](const vm &A, int l, int r) {
    assert(A.size() == r - l + 2);
    if (l == r) {
      vm B = {Mint(1), Mint(b[l])};
      auto res = ntt.Mult(A, B)[B.size() - 1];
      return pair(vm(1, res), B);
    }
    int m = l + r >> 1;
    vm A_L(A.begin(), A.begin() + m - l + 2);
    auto L = Solve(A_L, l, m);
    auto A_R = ntt.Mult(A, L.second);
    A_R = vm(A_R.begin() + L.second.size() - 1, A_R.begin() + L.second.size() - 1 + r - (m + 1) + 2);
    auto R = Solve(A_R, m + 1, r);
    vm B = ntt.Mult(L.second, R.second);
    L.first.insert(L.first.end(), R.first.begin(), R.first.end());
    return pair(L.first, B);
  };

  auto res = Solve(A, 0, n - 1);
  for (auto u : res.first) cout << u << ' ';
  cout << '\n';
  return 0;
}