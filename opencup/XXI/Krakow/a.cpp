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

// hash function of an 0-indexed array
// make sure that BASE > array's elements' max value
template <int MOD>
class HashArray {
  using ModInt = Modular<MOD>;

 public:
  explicit HashArray(const vector<int> &a, int base = 10007)
      : base_(ModInt(base)), sz_(static_cast<int>(a.size()) + 1) {
    pref_hash_.resize(sz_, ModInt(0));
    power_of_base_.resize(sz_, ModInt(1));
    for (int i = 1; i < sz_; i++) {
      assert(a[i - 1] > 0 && a[i - 1] < base);
      power_of_base_[i] = power_of_base_[i - 1] * base_;
      pref_hash_[i] = pref_hash_[i - 1] * base_ + ModInt(a[i - 1]);
    }
  }

  // a[0] -> a[n - 1]
  HashArray(int *a, int n, int base = 10007) : base_(ModInt(base)), sz_(n + 1) {
    pref_hash_.resize(sz_, ModInt(0));
    power_of_base_.resize(sz_, ModInt(1));
    for (int i = 1; i < sz_; i++) {
      power_of_base_[i] = power_of_base_[i - 1] * base_;
      pref_hash_[i] = pref_hash_[i - 1] * base_ + ModInt(a[i - 1]);
    }
  }

  // hash value of subarray [l..r] INCLUSIVELY
  ModInt GetHash(int l, int r) const {
    assert(l <= r && l >= 0 && r + 1 < sz_);
    return pref_hash_[r + 1] - pref_hash_[l] * power_of_base_[r - l + 1];
  }

 private:
  vector<ModInt> pref_hash_;
  vector<ModInt> power_of_base_;
  ModInt base_;
  int sz_;
};

const int MOD1 = (int)1e9 + 7;
const int MOD2 = 998244353;

void Solve(int test) {
  int n, m, k;
  cin >> n >> m >> k;
  // n = m = 1000;
  // k = 1000;
  string s;
  cin >> s;
  string t;
  cin >> t;

  // string s = "";
  // for (int i = 0; i < n; i++) {
  //   s += char(rand() % 26 + 'a');
  // }

  // string t = "";
  // for (int i = 0; i < n; i++) {
  //   t += char(rand() % 26 + 'a');
  // }

  if (abs(n - m) > k) {
    cout << "NO\n";
    return;
  }
  
  vector<int> ss(s.size());
  for (int i = 0; i < s.size(); i++) {
    ss[i] = s[i] - 'a' + 1;
  }
  vector<int> tt(t.size());
  for (int i = 0; i < t.size(); i++) {
    tt[i] = t[i] - 'a' + 1;
  }
  HashArray<MOD1> hs1(ss), ht1(tt);
  HashArray<MOD2> hs2(ss), ht2(tt);

  vector<vector<int>> dp(k + 1, vector<int>(2 * k + 1, -2));
  vector<vector<int>> trace(k + 1, vector<int>(2 * k + 1));

  auto GetLen = [&](int x, int y) {
    int low = 0, high = min(n - x, m - y) + 1;
    while (high - low > 1) {
      int mid = low + high >> 1;
      if (hs1.GetHash(x, x + mid - 1) == ht1.GetHash(y, y + mid - 1) &&
          hs2.GetHash(x, x + mid - 1) == ht2.GetHash(y, y + mid - 1)) {
        low = mid;
      } else {
        high = mid;
      }
    }
    return low;
  };

  dp[0][k] = -1 + GetLen(0, 0);
  for (int i = 0; i < k; i++) {
    // debug(i, dp[i]);
    for (int j = 0; j < 2 * k + 1; j++) {
      if (dp[i][j] == -2) continue;
      int x = dp[i][j];
      int y = x + j - k;
      if (x + 1 < n && j - 1 >= 0) {
        auto val = x + 1 + GetLen(x + 2, y + 1);
        if (dp[i + 1][j - 1] < val) {
          dp[i + 1][j - 1] = val;
          trace[i + 1][j - 1] = -1;
        }
      }
      if (y + 1 < m && j + 1 < 2 * k + 1) {
        auto val = x + GetLen(x + 1, y + 2);
        if (dp[i + 1][j + 1] < val) {
          dp[i + 1][j + 1] = val;
          trace[i + 1][j + 1] = 1;
        }
      }
      if (x + 1 < n && y + 1 < m) {
        auto val = x + 1 + GetLen(x + 2, y + 2);
        if (dp[i + 1][j] < val) {
          dp[i + 1][j] = val;
          trace[i + 1][j] = 0;
        }
      }
    }
  }

  int res = k + 1;
  pair<int, int> pos;

  for (int i = 0; i <= k && res > i; i++) {
    for (int j = 0; j < 2 * k + 1; j++) {
      if (dp[i][j] == -2) continue;
      int x = dp[i][j];
      int y = x + j - k;
      if (x == n - 1 && y == m - 1) {
        res = i;
        pos = {i, j};
        break;
      }
    }
  }
  if (res == k + 1) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n" << res << '\n';
  while (pos.first > 0) {
    auto op = trace[pos.first][pos.second];
    pos.first--;
    pos.second -= op;
    int x = dp[pos.first][pos.second];
    int y = x + pos.second - k;
    if (op == 0) {
      cout << "REPLACE " << x + 2 << ' ' << t[y + 1] << '\n';
    } else if (op == -1) {
      cout << "DELETE " << x + 2 << '\n';
    } else {
      cout << "INSERT " << x + 2 << ' ' << t[y + 1] << '\n'; 
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