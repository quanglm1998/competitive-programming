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

using ld = double;

const int N = 15;
const int M = 110;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  // n = 15, m = 100;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
    // u = rand() % 100 + 1;
  }

  vector<int> sum(1 << n, 0);

  for (int mask = 1; mask < (1 << n); mask++) {
    int u = -1;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        u = i;
        break;
      }
    }
    sum[mask] = sum[mask ^ (1 << u)] + a[u];
  }

  vector<vector<ld>> inv(n + 1, vector<ld>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    inv[i][0] = 1;
    for (int j = 1; j <= m; j++) {
      inv[i][j] = inv[i][j - 1] / i;
    }
  }
  vector<vector<ld>> cons(n + 1, vector<ld>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    cons[i][0] = 1;
    for (int j = 1; j <= m; j++) {
      cons[i][j] = cons[i][j - 1] * (i - 1) / i;
    } 
  }

  const ld EPS = 1e-15;

  vector<vector<ld>> c(m + 1, vector<ld>(m + 1, 0));
  for (int i = 0; i <= m; i++) for (int j = 0; j <= i; j++) {
    if (i == j || j == 0) c[i][j] = 1;
    else c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }

  vector<vector<ld>> f(1 << n, vector<ld>(m + 1, 0));
  for (int mask = 0; mask < (1 << n); mask++) {
    f[mask][0] = 1;
  }
  for (int mask = 1; mask < (1 << n); mask++) {
    for (int tot = 1; tot <= m; tot++) {
      int u = -1;
      for (int i = 0; i < n; i++) {
        if (mask >> i & 1) {
          u = i;
          break;
        }
      }
      int num = __builtin_popcount(mask);
      for (int x = 0; x < a[u]; x++) {
        if (x > tot) continue;
        f[mask][tot] += f[mask ^ (1 << u)][tot - x] * c[tot][x] * inv[num][x]
                      * cons[num][tot - x];
      }
    }
  }


  // for (int mask = 0; mask < (1 << n); mask++) {
  //   debug(mask, f[mask]);
  // }


  vector<vector<ld>> p(1 << n, vector<ld>(m + 1, 0));
  vector<vector<ld>> e(1 << n, vector<ld>(m + 1, 0));

  for (int mask = 0; mask < (1 << n); mask++) {
    for (int tot = 0; tot < m; tot++) {
      if (tot + sum[((1 << n) - 1) ^ mask] == m) {
        p[mask][tot + 1] = f[mask][tot];
      }
    }
  }

  // for (int mask = 0; mask < (1 << n); mask++) {
  //   debug(mask, p[mask], e[mask]);
  // }

  for (int mask = 0; mask < (1 << n); mask++) {
    int num = __builtin_popcount(mask);
    for (int last = 1; last <= m; last++) {
      if (p[mask][last] < EPS && e[mask][last] < EPS) continue;
      for (int u = 0; u < n; u++) {
        if (mask >> u & 1) continue;
        ld cur = inv[num + 1][a[u]];
        for (int x = 0; x < last; x++) {
          if (x + a[u] > m) break;
          // if ((mask | 1 << u) == 7 && x + a[u] == 2) {
          //   debug(mask, x, u, last, cur, p[mask][last], e[mask][last]);
          //   debug(cur * (p[mask][last] + e[mask][last]));
          // }
          p[mask | 1 << u][x + a[u]] += p[mask][last] * cur;
          e[mask | 1 << u][x + a[u]] += e[mask][last] * cur;
          e[mask | 1 << u][x + a[u]] += p[mask][last] * cur;
          cur *= ld(num) / (num + 1) * (a[u] + x) / (x + 1);
        }
      }
    }
  }

  // for (int mask = 0; mask < (1 << n); mask++) {
  //   debug(mask, p[mask], e[mask]);
  // }

  ld res = 0;
  for (int last = 1; last <= m; last++) {
    res += e[(1 << n) - 1][last];
  }
  cout << fixed << setprecision(10) << res << '\n';
  return 0;
}