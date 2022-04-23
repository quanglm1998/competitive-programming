#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> m;

int Solve(vector<int> a) {
  if (m.count(a)) return m[a];
  bool f = 0;
  for (auto u : a) {
    if (u) {
      f = 1;
      break;
    }
  }
  if (!f) return m[a] = 0;
  int sum = 0;
  for (int i = 0; i + 1 < a.size(); i++) {
    sum += a[i];
  }
  if (sum < a.back()) {
    return m[a] = 0;
  }

  int res = a.size() + 1;
  for (int i = 0; i < a.size(); i++) {
    for (int j = i + 1; j < a.size(); j++) {

      int cur = 0;
      vector<int> b;
      for (int k = 0; k < a.size(); k++) {
        if (k != i && k != j) b.push_back(a[k]);
      }
      auto c = b;
      b.push_back(a[i] + a[j]);
      sort(b.begin(), b.end());
      cur = max(cur, Solve(b));
      c.push_back(abs(a[i] - a[j]));
      sort(c.begin(), c.end());
      cur = max(cur, Solve(c));

      res = min(res, cur + 1);
    }
  }
  return m[a] = res;
}

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

Mint Get(int n) {
  n++;
  int cur = 1;
  Mint res;
  while (cur <= n) {
    int x = n / (cur * 2);
    int y = n % (cur * 2);
    res += Mint(cur) * Mint(x);
    if (y > cur) res += Mint(y - cur);
    cur <<= 1;
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // vector<int> cur;
  // for (int i = 1; i <= 40; i++) {
  //   cur.push_back(1);
  //   cout << i << ' ' << i - Solve(cur) << ' ' << __builtin_popcount(i) << endl;
  // }
  // cout << endl;

  int a, b;
  cin >> a >> b;
  cout << (Get(b) - Get(a - 1)) / Mint(b - a + 1) << '\n';
  return 0;
}