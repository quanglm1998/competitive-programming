#include <bits/stdc++.h>

using namespace std;

// source: tourist
template <typename A, typename B>
string to_string(pair<A, B> p);
 
string to_string(const string& s) {
  return '"' + s + '"';
}
 
string to_string(const char* s) {
  return to_string((string) s);
}
 
string to_string(bool b) {
  return (b ? "true" : "false");
}
 
string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}
 
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
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

mt19937 rng(0);

const int N = 860;
const int INF = 1e9;

int n;
int a[N * 2][N];
int dp[N * 2][N];
int res[N];
int order[N];

int r[N * 2], l[N * 2];
int pos[N];

void solve(int start, int k) {
    int u = start;
    int cnt = 0;
    while (u <= start + n) {
        pos[cnt++] = u;
        u = r[u];
    }

    for (int i = 0; i <= cnt; i++) {
        fill(dp[i], dp[i] + k + 1, INF);
    }
    dp[0][0] = 0;
    for (int i = 0; i < cnt; i++) {
        for (int ii = i + 1; ii < cnt; ii++) {
            for (int j = 0; j < k; j++) {
                if (dp[i][j] >= INF) continue;
                dp[ii][j + 1] = min(dp[ii][j + 1], dp[i][j] + a[pos[i] + 1][pos[ii] - pos[i]]);
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        res[i] = min(res[i], dp[cnt - 1][i]);
    }

    // for (int i = start; i <= start + n; i = r[i]) {
    //     fill(dp[i], dp[i] + k + 1, INF);
    // }
    // dp[start][0] = 0;
    // for (int i = start; i <= start + n; i = r[i]) {
    //     for (int ii = r[i]; ii <= start + n; ii = r[ii]) {
    //         for (int j = 0; j < k; j++) {
    //             if (dp[i][j] >= INF) continue;
    //             dp[ii][j + 1] = min(dp[ii][j + 1], dp[i][j] + a[i + 1][ii - i]);
    //         }
    //     }
    // }
    // for (int i = 1; i <= k; i++) {
    //     res[i] = min(res[i], dp[start + n][i]);
    // }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            a[i + n][j] = a[i][j];
        }
    }
    fill(res + 1, res + n + 1, INF);
    // iota(nxt + 0, nxt + n * 2 + 1, 1);
    iota(l + 0, l + n * 2 + 1, -1);
    iota(r + 0, r + n * 2 + 1, 1);

    iota(order + 1, order + n + 1, 1);

    shuffle(order + 1, order + n + 1, rng);

    auto Del = [&](int u) {
        r[l[u]] = r[u];
        l[r[u]] = l[u];
    };

    int last = 0;
    for (int k = n; k >= 1; k--) {
        int need = 1;
        if (k < n) need = ceil(-12 / log2(1.0 * (n - k) / n));
        need = min(need, n);

        for (int i = last + 1; i <= need; i++) {
            solve(order[i], k);
            Del(order[i]);
            Del(order[i] + n);
        }

        last = need;
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}