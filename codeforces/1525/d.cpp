#include <bits/stdc++.h>

using namespace std;

const int N = 5010;

int n;
int a[N];
int dp[N][N];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 1e9;
      if (j > 0) {
        dp[i][j] = min(dp[i][j], dp[i][j - 1]);  
      }
      if (a[i] == 0) {
        dp[i][j] = min(dp[i][j], dp[i - 1][j]);
      } else {
        if (a[j] == 0 && j > 0) {
          dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + abs(i - j));
        }
      }
    }
  }
  cout << dp[n][n] << endl;
  return 0;
}