#include <bits/stdc++.h>

using namespace std;

template <int MOD>
class Modular {
  static_assert(MOD >= 0, "MOD can't be negative!");
  static_assert(MOD * 2 > 0, "MOD is too large for int");

 public:
  explicit Modular(long long v = 0) : v_(v) {
    v_ %= MOD;
    if (v_ < 0) v_ += MOD;
  }

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

  static int Inverse(int a, int m) {
    auto m_ = m;
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
    return (u % m_ + m_) % m_;
  }
 private:

  int v_;
};
constexpr int MOD = 998244353;
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
  int n, m;
  cin >> n >> m;
  int a, b;
  cin >> a >> b;
  vector<pair<int, int>> edges(m);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  auto SolveSmall = [&]() -> Mint {
    vector<vector<int>> adj(n, vector<int>());
    for (auto [u, v] : edges) {
      adj[v].push_back(u);
    }
    vector<Mint> f(1 << b, Mint(0));
    f[0] = Mint(1);
    for (int i = 0; i < n; i++) {
      auto id_i = i % b;
      vector<Mint> g(1 << b, Mint(0));
      for (int mask = 0; mask < 1 << b; mask++) {
        // don't use i
        g[mask & ((1 << b) - 1 ^ 1 << id_i)] += f[mask];
        for (auto j : adj[i]) {
          auto id_j = j % b;
          if (id_i == id_j) {  // v - u = b
            if (!(mask >> id_i & 1)) {
              g[mask ^ 1 << id_i] += f[mask];
            }
          } else {  // v - u == a
            if (!(mask >> id_j & 1)) {
              g[mask ^ 1 << id_j | 1 << id_i] += f[mask];
            }
          }
        }
      }
      swap(f, g);
    }
    return accumulate(f.begin(), f.end(), Mint(0));
  };

  auto SolveMod = [&](const vector<pair<int, int>> &edges, int inv_a, int n) -> Mint {
    auto block_size = (n + b - 1) / b;
    n = block_size * b;

    auto Encode = [&](int u) {
      auto x = u / b;
      auto y = u % b;
      (y *= inv_a) %= b;
      y = (b - y) % b;
      return y * block_size + x;
    };

    vector<pair<int, int>> over_edges;
    vector<vector<int>> adj(n, vector<int>());
    for (auto [u, v] : edges) {
      auto x = Encode(u);
      auto y = Encode(v);
      if (x > y) swap(x, y);
      // debug(x, y);
      if (x / block_size == 0 && y / block_size == b - 1 && b > 2) {
        over_edges.push_back({x, y});
      } else {
        adj[y].push_back(x);
      }
    }

    // debug(b, block_size, n);
    // for (int i = 0; i < n; i++) debug(i, Encode(i));
    assert(over_edges.size() <= block_size);
    Mint res(0);
    for (int mask = 0; mask < 1 << over_edges.size(); mask++) {
      auto front_mask = 0;
      auto back_mask = 0;
      for (int i = 0; i < over_edges.size(); i++) {
        if (mask >> i & 1) {
          front_mask |= 1 << over_edges[i].first % block_size;
          back_mask |= 1 << over_edges[i].second % block_size;
        }
      }
      // debug(mask, front_mask, back_mask);
      vector<Mint> f(1 << block_size, Mint(0));
      f[0] = Mint(1);
      for (int i = 0; i < n; i++) {
        auto id_i = i % block_size;
        vector<Mint> g(1 << block_size, Mint(0));
        for (int mask = 0; mask < 1 << block_size; mask++) {
          if (i / block_size == 0 && front_mask >> id_i & 1) {
            if (!(mask >> id_i & 1)) {
              g[mask ^ 1 << id_i] += f[mask];
            }
            continue;
          }
          // don't use i
          auto next_mask = mask & ((1 << block_size) - 1 ^ 1 << id_i);
          // debug(i, mask, next_mask);
          g[next_mask] += f[mask];
          for (auto j : adj[i]) {
            auto id_j = j % block_size;
            // if (i == 1 || j == 0) {
            //   debug(mask, f[mask]);
            //   debug(id_i, id_j);
            //   debug(mask ^ 1 << id_j | 1 << id_i);
            // }
            if (id_i == id_j) {
              if (!(mask >> id_i & 1)) {
                g[mask ^ 1 << id_i] += f[mask];
              }
            } else {
              if (!(mask >> id_j & 1)) {
                g[mask ^ 1 << id_j | 1 << id_i] += f[mask];
              }
            }
          }
        }
        swap(f, g);
        // debug(i, f);
      }
      for (int final_mask = 0; final_mask < 1 << block_size; final_mask++) {
        if (!(back_mask & final_mask)) {
          // debug(final_mask, f[final_mask]);
          res += f[final_mask];
        }
      }
    }
    return res;
  };

  auto SolveBig = [&]() -> Mint {
    auto g = __gcd(a, b);
    a /= g;
    b /= g;
    auto sz = (n + g - 1) / g;
    vector<vector<pair<int, int>>> mod_egdes(g, vector<pair<int, int>>());
    for (auto [u, v] : edges) {
      mod_egdes[u % g].push_back({u / g, v / g});
    }
    Mint res = Mint(1);
    auto inv_a = Mint::Inverse(a, b);
    for (int i = 0; i < g; i++) {
      res *= SolveMod(mod_egdes[i], inv_a, sz);
    }
    return res;
  };
  
  // cout << SolveBig() << endl;

  if (b * b <= 2 * n) {
    cout << SolveSmall() << '\n';
  } else {
    cout << SolveBig() << '\n';
  }
  return 0;
}