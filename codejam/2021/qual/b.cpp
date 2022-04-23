#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, x, y;
char s[N];
int dp[2][N];

void solve(int test) {
  cout << "Case #" << test << ": ";
  cin >> x >> y;
  cin >> (s + 1);
  n = strlen(s + 1);
  for (int i = 0; i < 2; ++i) {
      fill(dp[i], dp[i] + n + 1, 1e9);
  }
  for (int i = 1; i <= n; i++) {
    if (i == 1) {
      if (s[1] != 'J') dp[0][1] = 0;
      if (s[1] != 'C') dp[1][1] = 0;
    } else {
      if (s[i] != 'J') dp[0][i] = min(dp[0][i - 1], dp[1][i - 1] + y);
      if (s[i] != 'C') dp[1][i] = min(dp[1][i - 1], dp[0][i - 1] + x);
    }
  }
  cout << min(dp[0][n], dp[1][n]) << '\n';
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