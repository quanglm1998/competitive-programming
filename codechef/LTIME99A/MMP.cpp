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

template <typename T>
inline bool max_to(T &u, const T &v) { return u < v ? (u = v, true) : false; }
template <typename T>
inline bool min_to(T &u, const T &v) { return u > v ? (u = v, true) : false; }

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> v(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
  }
  const int INF = 1e9;
  vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, INF)));
  vector<vector<vector<int>>> g(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, INF)));
  for (int k = 0; k <= n; k++) {
    f[1][v[1]][k] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = n - 1; k >= 0; k--) {
        min_to(g[i][j][k], g[i][j][k + 1]);
        min_to(f[i][j][k], g[i][j][k]);
      }

      for (int k = 0; k <= n; k++) {
        int new_i = i + j + k;
        if (new_i > n) continue;
        if (v[new_i] > k) continue;
        int new_j = min(j, v[new_i]);
        debug(n, i, j, k, new_i, new_j);
        if (v[new_i] < k) {
          min_to(f[new_i][new_j][k], f[i][j][k] + 1);
        } else {
          min_to(g[new_i][new_j][k], f[i][j][k] + 1);
        }
      }
    }
  }
  int res = INF;
  for (int i = 1; i <= n; i++) {
    res = min(res, f[n][i][0]);
  }
  cout << (res == INF ? -1 : res) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}