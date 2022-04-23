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

const int MOD = (int)1e9 + 7;
inline int add(int u, int v, int m = MOD) { return (u += v) >= m ? u - m : u; }
inline int sub(int u, int v, int m = MOD) { return (u -= v) < 0 ? u + m : u; }
inline int mul(int u, int v, int m = MOD) { return (long long)u * v % m; }
inline int power(int u, int v, int m = MOD) {
  int res = 1;
  for (; v; v >>= 1, u = mul(u, u, m)) if (v & 1) res = mul(res, u, m);
  return res;
}
inline int neg(int u, int m = MOD) { return sub(0, u); }
inline int inv(int u, int m = MOD) { return power(u, m - 2, m); }
inline int add_to(int &u, int v, int m = MOD) { return u = add(u, v, m); }
inline int sub_to(int &u, int v, int m = MOD) { return u = sub(u, v, m); }
inline int mul_to(int &u, int v, int m = MOD) { return u = mul(u, v, m); }

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<long long> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  sort(a.rbegin(), a.rend());
  vector<int> fac(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    fac[i] = mul(fac[i - 1], i);
  }
  vector<int> inv_fac(n + 1, 1);
  inv_fac[n] = inv(fac[n]);
  for (int i = n - 1; i >= 0; i--) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }

  auto Binom = [&](int n, int k) {
    if (k < 0 || k > n) return 0;
    return mul(fac[n], mul(inv_fac[k], inv_fac[n - k]));
  };

  vector<long long> pref_xor(n, 0);
  vector<long long> suff_xor(n, 0);
  pref_xor[0] = a[0];
  for (int i = 1; i < n; i++) {
    pref_xor[i] = pref_xor[i - 1] ^ a[i];
  }
  suff_xor[n - 1] = a[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    suff_xor[i] = suff_xor[i + 1] ^ a[i];
  }

  vector<long long> basis(64, 0);
  auto times = 1;
  auto res = 0;

  auto Check = [&](long long u) {
    for (int i = 63; i >= 0; i--) {
      if ((u >> i & 1) == 0) continue;
      if (!basis[i]) return false;
      u ^= basis[i];
    }
    return u == 0;
  };

  auto AddBasis = [&](long long u) {
    for (int i = 63; i >= 0; i--) {
      if ((u >> i & 1) == 0) continue;
      if (!basis[i]) {
        basis[i] = u;
        return;
      }
      u ^= basis[i];
    }
    mul_to(times, 2);
    assert(u == 0);
  };

  for (int l = 0, r = 0; l < n; l = r) {
    while (r < n && a[l] == a[r]) r++;
    auto suff = (r == n ? 0ll : suff_xor[r]);
    auto pref = (l == 0 ? 0ll : pref_xor[l - 1]);
    debug(l, r, pref, suff);

    for (int i = 1; i <= r - l; i++) {
      auto num = Binom(r - l, i);
      auto rest = a[l] * ((r - l - i) % 2);
      debug(i, num, rest);
      // only chunk
      if ((pref ^ suff ^ rest) == a[l] - (i + 1) % 2) {
        add_to(res, num);
      }
      debug(res);
      // multiple chunks
      debug(suff ^ rest ^ (a[l] - i % 2));
      if (Check(suff ^ rest ^ (a[l] - i % 2))) {
        add_to(res, mul(num, times));
        if ((pref ^ suff ^ rest) == a[l] - i % 2) {
          sub_to(res, num);
        }
      }
    }
    for (int i = l; i < r; i++) {
      AddBasis(a[l]);
    }
  }
  if (suff_xor[0] == 0) add_to(res, 1);
  cout << res << '\n';
  return 0;
}