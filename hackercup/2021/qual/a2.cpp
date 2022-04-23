#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  cout << "Case #" << test << ": ";
  string s;
  cin >> s;
  int k;
  cin >> k;
  const int INF = 1e9;
  vector<vector<int>> dist(26, vector<int>(26, INF));
  for (int i = 0; i < 26; i++) {
    dist[i][i] = 0;
  }
  for (int i = 0; i < k; i++) {
    char a, b;
    cin >> a >> b;
    dist[a - 'A'][b - 'A'] = 1;
  }
  for (int x = 0; x < 26; x++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        dist[i][j] = min(dist[i][j], dist[i][x] + dist[x][j]);
      }
    }
  }
  int res = INF;
  for (char c = 'A'; c <= 'Z'; c++) {
    int num = 0;
    for (auto u : s) {
      num += dist[u - 'A'][c - 'A'];
      if (num >= INF) break;
    }
    res = min(res, num);
  }
  cout << (res >= INF ? -1 : res) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}