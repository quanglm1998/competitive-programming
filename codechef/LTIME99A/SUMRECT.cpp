#include <bits/stdc++.h>

using namespace std;

template <int& MOD>
class Modular {
  // static_assert(MOD >= 0, "MOD can't be negative!");
  // static_assert(MOD * 2 > 0, "MOD is too large for int");

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

int p;

void Solve(int test) {
  int n, m;
  cin >> n >> m >> p;
  using Mint = Modular<p>;
  vector<vector<Mint>> sum_hor(n + 1, vector<Mint>(m + 1));
  if (n == 1 && m == 1) {
    cout << 1 << '\n';
    return;
  }
  if (p == 2) {
    cout << (abs(n - m) == 1) << '\n';
    return;
  } 
  auto sum_ver = sum_hor;
  auto num_ver = sum_hor;
  auto num_hor = sum_hor;
  sum_hor[1][1] = sum_ver[1][1] = num_hor[1][1] = num_ver[1][1] = Mint(1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (i == 1 && j == 1) continue;
      Mint now = sum_hor[i][j - 1] + sum_ver[i - 1][j];
      now += Mint(1ll * i * j) * (num_hor[i][j - 1] + num_ver[i - 1][j]);
      if (i == n && j == m) {
        cout << now << '\n';
      }
      sum_hor[i][j] = sum_hor[i][j - 1] + now;
      sum_ver[i][j] = sum_ver[i - 1][j] + now;
      num_hor[i][j] = num_hor[i][j - 1] * Mint(2) + num_ver[i - 1][j];
      num_ver[i][j] = num_hor[i][j - 1] + num_ver[i - 1][j] * Mint(2); 
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}