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

class NTT {
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
    if (a.empty() || b.empty()) return {};
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
};

class NttWithIS : public NTT {
 public:
  // Inverse polynomial of F(x)
  // I_n(x): I_n(x) * F(x) = 1 (mod x^n)
  // I_1(0) = 1 / F(0)
  // I_2n(x) = 2I_n(x) - I_n(x)^2 * F(x)
  // Inversed polinomial is only TRUE for 0 <= i < F.size()
  // which means F * I = {1, 0, 0, ... 0, X, X, ...}
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
  // Squareroot polinomial is only TRUE for 0 <= i < F.size()
  // which means S ^ 2 = {F[0], F[1], ..., F[size - 1], X, X, ...}
  vector<Mint> PolySqrt(vector<Mint> F, Mint sqrt_F0) {
    auto n = static_cast<int>(F.size());
    auto cur_base = n == 1 ? 0 : 32 - __builtin_clz(n - 1);
    F.resize(1 << cur_base);
    vector<Mint> S = {sqrt_F0};
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
    for (auto& u : res) u *= INV_2;
    return res;
  }

  const Mint INV_2 = Mint(2).Inv();
  int max_base_;
  vector<Mint> roots_;  // 0: -1, 1: i, ...
  vector<int> rev_;
} ntt; 

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> a(n, vector<int>());
  map<int, vector<pair<int, int>>> pos;

  for (int i = 0; i < n; i++) {
    int sz;
    cin >> sz;
    a[i].resize(sz);
    for (int j = 0; j < sz; j++) {
      cin >> a[i][j];
      a[i][j]--;
      pos[a[i][j]].push_back({i, j});
    }
  }

  vector<bool> visited(k);
  vector<bool> used_val(k);
  vector<bool> used_array(n);
  vector<int> dist(k);
  set<pair<int, int>> s;

  bool flag;

  function<int(int, int, int, int)> Dfs = [&](int arr, int id, int val, int d) -> int { 
    if (s.count({arr, id})) return 0;
    s.insert({arr, id});

    int res = 0;
    if (!visited[val]) {
      res++;
    }
    visited[val] = 1;

    dist[val] = d;

    // same array
    if (!used_array[arr]) {
      used_array[arr] = 1;
      for (int i = 0; i < a[arr].size(); i++) {
        if (!visited[a[arr][i]]) {
          res += Dfs(arr, i, a[arr][i], d + i - id);
        } else {
          if (dist[a[arr][i]] != d + i - id) {
            flag = 1;
          }
        }
      }
    }

    // same value
    if (!used_val[val]) {
      used_val[val] = 1;
      for (auto [nxt_arr, nxt_id] : pos[val]) {
        if (!used_array[nxt_arr]) {
          res += Dfs(nxt_arr, nxt_id, val, d);
        }
      }
    }
    return res;
  };

  vector<Mint> f(m + 1);
  f[0]++;

  for (int i = 0; i < k; i++) {
    if (visited[i]) continue;
    if (!pos.count(i)) {
      f[1]--;
    } else {
      flag = 0;
      auto [arr, id] = pos[i][0];
      auto u = Dfs(arr, id, i, 0);
      if (!flag && u <= m) f[u]--;
    }
  }
  debug(f);
  auto g = ntt.PolyInv(f);
  cout << g[m] << '\n';
  return 0;
}