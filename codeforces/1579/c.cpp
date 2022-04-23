#include <bits/stdc++.h>

using namespace std;

const int N = 30;

int n, m, k;
char s[N][N];
bool used[N][N];

bool IsInside(int u, int v) {
  return u >= 1 && u <= n && v >= 1 && v <= m;
}

void Solve(int test) {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> (s[i] + 1);
  }
  for (int i = 1; i <= n; i++) {
    fill(used[i] + 1, used[i] + m + 1, 0);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == '.') continue;
      int len = 1;
      while (IsInside(i - len, j - len) && s[i - len][j - len] == '*' &&
             IsInside(i - len, j + len) && s[i - len][j + len] == '*') {
        len++;
      }
      len--;
      if (len >= k) {
        for (int x = 0; x <= len; x++) {
          used[i - x][j + x] = used[i - x][j - x] = 1;
        }
      } 
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == '*' && used[i][j] == 0) {
        cout << "NO\n";
        return;
      }
    }
  }
  cout << "YES\n";
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}