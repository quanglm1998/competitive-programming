#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int p[N];
int dp[N];
int can[N];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  can[1] = 0;
  can[2] = 1;
  for (int i = 3; i < N; i++) {
    dp[i] = 1;
    can[i] = 1;
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        int u = i / j - 1;
        if (j > 2) {
          dp[i] = max(dp[i], can[u] + 1);
        }
        can[i] = max(can[i], can[u] + 1);
        u = j - 1;
        if (i / j > 2) {
          dp[i] = max(dp[i], can[u] + 1);
        }
        can[i] = max(can[i], can[u] + 1);
      }
    }
  }

  int tc;
  cin >> tc;
  int test = 0;
  while (tc--) {
    test++;
    cout << "Case #" << test << ": ";
    int n;
    cin >> n;
    cout << dp[n] << '\n';
  }
  return 0;
}
