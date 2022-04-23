#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  sort(a.begin(), a.end());
  const int INF = 5001;
  vector<vector<int>> dp(INF, vector<int>(INF, -1));
  dp[0][0] = 0;
  queue<pair<int, int>> q;
  q.push({0, 0});
  while (!q.empty()) {
    auto [u, v] = q.front();
    q.pop();
    if (dp[u][v] >= n) continue;
    const auto &delta = a[dp[u][v]];
    if (u + delta < INF && dp[u + delta][v] == -1) {
      dp[u + delta][v] = dp[u][v] + 1;
      q.push({u + delta, v});
    }
    if (v + delta < INF && dp[u][v + delta] == -1) {
      dp[u][v + delta] = dp[u][v] + 1;
      q.push({u, v + delta});
    }
  }
  long long res = 0;
  for (int i = 0; i < INF; i++) {
    for (int j = 0; j < INF; j++) {
      if (i > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
      if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
      if (i > 0 && j > 0) res += (dp[i][j] ^ i ^ j);
    }
  }
  cout << res << '\n';
  return 0;
}