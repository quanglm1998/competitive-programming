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

const int N = 16;
const int M = 150;

long long dp[N + 1][3][M][M];
bool isPrime[M];

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  for (int i = 2; i < M; i++) {
    int f = 0;
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        f = 1;
        break;
      }
    }
    isPrime[i]= !f;
  }

  long long n;
  cin >> n;
  vector<int> ls;
  for (int i = 0; i < N; i++) {
    ls.push_back(n % 10);
    n /= 10;
  }
  dp[0][0][0][0] = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      for (int u = 0; u < M; u++) {
        for (int v = 0; v < M; v++) {
          if (!dp[i][j][u][v]) continue;
          for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
              int tot = x + y * 2 + j;
              int d = tot % 10;
              int r = tot / 10;
              if (d != ls[i]) continue;
              if (u + x >= M || v + y >= M) continue;
              dp[i + 1][r][u + x][v + y] += dp[i][j][u][v];
            }
          }
        }   
      }
    }
  }
  long long res = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (isPrime[i] && isPrime[j]) {
        res += dp[N][0][i][j];
      }
    }
  }
  cout << res << '\n';
  return 0;
}