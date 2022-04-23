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
constexpr int MOD = int(1e9) + 7;
using Mint = Modular<MOD>;

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

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<Mint> tot;
  vector<Mint> inv_deg;
  vector<vector<int>> adj;
  tot.push_back(Mint(0));
  inv_deg.push_back(Mint(0));
  adj.push_back(vector<int>());

  function<void(int)> Dfs = [&](int u) {
    debug(u, adj[u].size());
    if (!tot[u]) return;
    if (adj[u].empty()) return;
    Mint foo = tot[u] * inv_deg[u];
    for (auto v : adj[u]) {
      tot[v] += foo;
      Dfs(v);
    }
    tot[u] = Mint(0);
  };

  int ans = 0;
  while (n--) {
    char op;
    cin >> op;
    if (op == '+') {
      int u, v;
      cin >> u >> v;
      u ^= ans;
      v ^= ans;
      u--, v--;
      debug(u, v);
      adj[u].push_back(v);
      inv_deg[u] = Mint(adj[u].size()).Inv();

      tot.push_back(Mint(0));
      inv_deg.push_back(Mint(0));
      adj.push_back(vector<int>());

      Dfs(u);
    } else if (op == '#') {
      int u, k;
      cin >> u >> k;
      debug(u, k);
      u ^= ans;
      k ^= ans;
      u--;
      tot[u] += Mint(k);
      Dfs(u);
    } else {
      int u;
      cin >> u;
      u ^= ans;
      u--;
      cout << tot[u] << '\n';
      ans = int(tot[u]);
    }
  }
  return 0;
}