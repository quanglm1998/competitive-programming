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

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (auto &row : a) {
    for (auto &u : row) {
      cin >> u;
      u--;
    }
  }
  set<vector<int>> perms;
  auto best = a;
  for (int i = 0; i < n; i++) {
    vector<int> p(m);
    for (int j = 0; j < m; j++) {
      p[m - a[i][j] - 1] = j;
    }
    if (perms.count(p)) continue;
    perms.insert(p);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int u, int v) {
      for (int j = 0; j < m; j++) {
        auto id = p[j];
        if (a[u][id] != a[v][id]) return a[u][id] > a[v][id];
      }
      return false;
    });
    vector<vector<int>> now(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        now[i][j] = a[order[i]][p[j]];
      }
    }
    int f = 0;
    for (int i = 0; i < n && f == 0; i++) {
      for (int j = 0; j < m && f == 0; j++) {
        if (now[i][j] != best[i][j]) {
          if (now[i][j] < best[i][j]) {
            f = -1;
            break;
          }
          f = 1;
          break;
        }
      }
    }
    if (f == 1) {
      best = now;
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    cout << best[x][y] + 1 << '\n';
  }
  return 0;
}