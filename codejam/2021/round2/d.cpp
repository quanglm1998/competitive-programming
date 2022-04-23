#include <bits/stdc++.h>

using namespace std;

const int N = 11;
const int INF = 1e9;

int r, c, f, s;
char line[N];
int a[N], b[N];
int min_cost[N][1 << 10];
int dp[2][N];
int g[N][1 << 10];

int Init(int mask1, int mask2) {
  dp[0][0] = dp[1][0] = INF;
  dp[mask1 & 1][0] = 0;
  // cout << mask1 << ' ' << mask2 << endl;
  for (int i = 1; i < c; i++) {
    dp[0][i] = dp[1][i] = INF;
    int y = mask2 >> (i - 1) & 1;
    for (int j = 0; j < 2; j++) {
      for (int S = 0; S < 2; S++) {
        int last = j;
        int now = mask1 >> i & 1;
        if (S) swap(now, last);
        int cost = 0;
        if (last != y) cost += f;
        if (S) cost += s;
        // if (i == 1 && j == 1 && S == 1) {
        //   cout << last << ' ' << now << ' ' << y << endl;
        //   cout << cost << endl;
        // }
        dp[now][i] = min(dp[now][i], dp[j][i - 1] + cost);
      }
    }
    // cout << i << ' ' << dp[0][i] << ' ' << dp[1][i] << endl;
  }
  int x = mask2 >> (c - 1) & 1;
  return min(dp[x][c - 1], dp[x ^ 1][c - 1] + f);
}

void solve(int test) {
  cout << "Case #" << test << ": ";
  for (int i = 0; i < r; i++) {
    a[i] = b[i] = 0;
  }

  cin >> r >> c >> f >> s;
  for (int i = 0; i < r; i++) {
    cin >> line;
    for (int j = 0; j < c; j++) {
      if (line[j] == 'M') a[i] |= 1 << j;
    }
  }
  for (int i = 0; i < r; i++) {
    cin >> line;
    for (int j = 0; j < c; j++) {
      if (line[j] == 'M') b[i] |= 1 << j;
    }
  }

  for (int i = 0; i < r; i++) {
    for (int mask = 0; mask < (1 << c); mask++) {
      min_cost[i][mask] = Init(mask, b[i]);
    }
  }

  // for (int mask = 0; mask < (1 << c); mask++) {
  //   cout << mask << ' ' min_cost[0][mask] << endl;
  // }

  for (int i = 0; i < r; i++) {
    for (int mask = 0; mask < (1 << c); mask++) {
      g[i][mask] = INF;
    }
  }

  auto Swap = [](int &mask1, int &mask2, int pos) {
    int u = mask1 >> pos & 1;
    int v = mask2 >> pos & 1;
    if (u == v) return;
    mask1 ^= (1 << pos);
    mask2 ^= (1 << pos);
  };

  g[0][a[0]] = 0;
  for (int i = 0; i + 1 < r; i++) {
    for (int mask = 0; mask < (1 << c); mask++) {
      for (int p_mask = 0; p_mask < (1 << c); p_mask++) {
        int cur_mask = mask;
        int nxt_mask = a[i + 1];
        for (int j = 0; j < c; j++) {
          if (p_mask >> j & 1) {
            Swap(cur_mask, nxt_mask, j);
          }
        }
        g[i + 1][nxt_mask] = min(g[i + 1][nxt_mask], g[i][mask] + min_cost[i][cur_mask] + s * __builtin_popcount(p_mask));
      }
    }
    // cout << "# " << i + 1 << endl;
    // for (int mask = 0; mask < (1 << c); mask++) {
    //   cout << mask << ' ' << g[i + 1][mask] << endl;
    // }
  }

  int res = INF;
  for (int mask = 0; mask < (1 << c); mask++) {
    int now = g[r - 1][mask];
    now += min_cost[r - 1][mask];
    res = min(res, now);
  }
  cout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);  
  }
  return 0;
}