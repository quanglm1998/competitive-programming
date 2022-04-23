#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 410;
 
int n, m;
int a[N][N];
int last[1000010], pos[1000010], it;
short dp[N][N][N];
 
void getmin(short &u, short v) {
  u = min(u, v);
}
 
int main() {
  //freopen("board.inp", "r", stdin);
 // freopen("board.out", "w", stdout);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      for (int k = 1; k <= m; k++) {
        dp[i][j][k] = m;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    it++;
    for (int j = m; j; j--) {
      if (pos[a[i][j]] == it) {
        getmin(dp[i][i][j], last[a[i][j]] - 1);
      }
      pos[a[i][j]] = it;
      last[a[i][j]] = j;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      it++;
      for (int k = m; k; k--) {
        if (pos[a[i][k]] == it) {
          getmin(dp[i][j][k], last[a[i][k]] - 1);
        }
        pos[a[i][k]] = it;
        last[a[i][k]] = k;
 
        if (pos[a[j][k]] == it) {
          getmin(dp[i][j][k], last[a[j][k]] - 1);
        }
        pos[a[j][k]] = it;
        last[a[j][k]] = k;
      }
    }
  }
  int res = 0;
  for (int i = n; i; i--) {
    for (int j = i; j <= n; j++) {
      for (int k = m; k; k--) {
        short &foo = dp[i][j][k];
        if (k < m) {
          getmin(foo, dp[i][j][k + 1]);
        }
        if (i < j) {
          getmin(foo, dp[i + 1][j][k]);
          getmin(foo, dp[i][j - 1][k]);
        }
        res = max(res, (j - i + 1) * ((int)foo - k + 1));
      }
    }
  }
  cout << res << endl;
  return 0;
}