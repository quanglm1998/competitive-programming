#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  cout << "Case #" << test << ": ";
  int n, a, b;
  cin >> n >> a >> b;
  vector<int> num(n + 1);
  vector<vector<int>> dp;
  int first = -1;
  int g = 0;
  for (int i = 1; i <= n; i++) {
    cin >> num[i];
    if (num[i]) {
      if (first != -1) {
        g = __gcd(g, i - first);
      } else {
        first = i;
      }
    }
  }
  if (g % __gcd(a, b)) {
    cout << "IMPOSSIBLE" << '\n';
    return;
  }
  vector<int> zeros(n + 1, 0);
  for (int i = 0; i <= first; i++) dp.push_back(zeros);
  dp.back()[first] = 1;
  int cur = first;
  while (1) {
    cur++;
    vector<int> now(n + 1, 0);
    if (cur <= n) {
      now[cur] = 1;
      dp.push_back(now);
      continue;
    }
    int x = cur - a;
    int y = cur - b;

    auto Add = [](vector<int> &s, const vector<int> &t) {
      for (int i = 0; i < s.size(); i++) {
        s[i] += t[i];
      }
    };

    auto Normalize = [&](vector<int> &s) {
      for (int i = n; i > 0; i--) {
        if (s[i] > num[i]) {
          int delta = s[i] - num[i];
          int x = i - a;
          int y = i - b;
          if (x > 0) s[x] += delta;
          if (y > 0) s[y] += delta;
          s[i] = num[i];
        }
      }
    };

    auto Check = [&](const vector<int> &s) {
      for (int i = 0; i < s.size(); i++) {
        if (s[i] < num[i]) return false;
      }
      return true;
    };

    if (x > 0) Add(now, dp[x]);
    if (y > 0) Add(now, dp[y]);
    Normalize(now);
    if (Check(now)) break;

    dp.push_back(now);
  }
  cout << cur << endl;
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