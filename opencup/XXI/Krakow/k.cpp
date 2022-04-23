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
  int n, k;
  cin >> n >> k;
  const int INF = 1e9;
  vector<vector<int>> dist(n + k, vector<int>(n + k, INF));
  for (int i = 0; i < n + k; i++) dist[i][i] = 0;
  for (int i = 0; i < k; i++) {
    int r;
    cin >> r;
    for (int j = 0; j < r; j++) {
      int u;
      cin >> u;
      u--;
      dist[u][i + n] = dist[i + n][u] = 1;
    }
  }
  int s;
  cin >> s;
  vector<int> ids(k, s);
  for (int i = 0; i < s; i++) {
    int u;
    cin >> u;
    u--;
    ids[u] = i;
  }
  vector<int> ls(n + k);
  iota(ls.begin(), ls.end(), 0);
  sort(ls.begin(), ls.end(), [&](int u, int v) {
    if (u >= n && v >= n) return ids[u - n] > ids[v - n];
    return u < v;
  });
  // debug(ls);
  vector<int> res(s + 1);
  bool first = true;
  for (auto u : ls) {
    if (first && u >= n && ids[u - n] < s) {
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (dist[i][j] < INF) max_to(res[s], dist[i][j] / 2 - 1);
        }
      }
      first = false;
    }
    for (int i = 0; i < n + k; i++) {
      for (int j = 0; j < n + k; j++) {
        min_to(dist[i][j], dist[i][u] + dist[u][j]);
      }
    }
    if (u >= n && ids[u - n] < s) {
      // debug(u, ids[u - n]);
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (dist[i][j] < INF) {
            max_to(res[ids[u - n]], dist[i][j] / 2 - 1);
            // debug(i, j, dist[i][j]);
          }
        }
      }
    }
  }
  for (auto u : res) cout << u << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}