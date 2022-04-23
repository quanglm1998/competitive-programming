#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  cout << "Case #" << test << ": ";
  int n;
  cin >> n;
  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  const int INF = 1e9;
  pair<int, int> res(INF, 0);

  set<pair<int, int>> s;
  for (int row = 0; row < n; row++) {
    int num = 0;
    bool f = 0;
    int pos = -1;
    for (int col = 0; col < n; col++) {
      if (a[row][col] == 'O') {
        f = 1;
        break;
      }
      if (a[row][col] == '.') {
        num++;
        pos = col;
      }
    }
    if (!f) {
      if (num == 1 && s.count({row, pos})) {
        continue;  
      }
      s.insert({row, pos});
      if (res.first > num) {
        res = {num, 1};
      } else if (res.first == num) {
        res.second++;
      }
    }
  }

for (int col = 0; col < n; col++) {
    int num = 0;
    bool f = 0;
    int pos = -1;
    for (int row = 0; row < n; row++) {
      if (a[row][col] == 'O') {
        f = 1;
        break;
      }
      if (a[row][col] == '.') {
        num++;
        pos = row;
      }
     }
    if (!f) {
      if (num == 1 && s.count({pos, col})) {
        continue;  
      }
      s.insert({pos, col});
      if (res.first > num) {
        res = {num, 1};
      } else if (res.first == num) {
        res.second++;
      }
    }
  }


  if (res.first == INF) cout << "Impossible\n";
  else cout << res.first << ' ' << res.second << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}