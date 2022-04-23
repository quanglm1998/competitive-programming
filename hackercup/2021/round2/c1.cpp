#include <bits/stdc++.h>

using namespace std;


void Solve(int test) {
  cout << "Case #" << test << ": ";
  int r, c, k;
  cin >> r >> c >> k;
  k--;
  vector<string> a(r);
  for (auto &s : a) {
    cin >> s;
  }
  vector<vector<int>> up(r, vector<int>(c, 0));
  vector<vector<int>> down(r, vector<int>(c, 0));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      up[i][j] = a[i][j] == 'X';
      if (i > 0) up[i][j] += up[i - 1][j];
    }
  }
  for (int i = r - 1; i >= 0; i--) {
    for (int j = 0; j < c; j++) {
      down[i][j] = a[i][j] == 'X';
      if (i + 1 < r) down[i][j] += down[i + 1][j];
    }
  }

  int res = c;
  for (int x = 0; x <= r; x++) {
    int cnt = x;
    for (int j = 0; j < c; j++) {
      if (down[max(0, k - x)][j] >= r - k) {
        cnt++;
      } else {
        if (k - x >= 0 && a[k - x][j] == 'X') cnt++;
      }
    }
    res = min(res, cnt);
  }

  for (int x = 0; x <= r; x++) {
    int cnt = x;
    for (int j = 0; j < c; j++) {
      if (up[min(r - 1, k + x)][j] >= k + 1) {
        cnt++;
      } else {
        if (k + x < r && a[k + x][j] == 'X') cnt++;
      }
    }
    res = min(res, cnt);
  }

  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}