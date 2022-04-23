#include <bits/stdc++.h>

using namespace std;

const int X[] = {1, 0, -1, 0};
const int Y[] = {0, -1, 0, 1};

int n, m;
vector<vector<int>> a;
vector<vector<int>> used;
int cnt = 0;

bool IsInside(int u, int v) {
  return u >= 1 && u <= n && v >= 1 && v <= m;
}

void Dfs(int u, int v, int color, vector<pair<int, int>> &ls) {
  used[u][v] = cnt;
  ls.push_back({u, v});
  for (int i = 0; i < 4; i++) {
    int uu = u + X[i];
    int vv = v + Y[i];
    if (IsInside(uu, vv) && used[uu][vv] != cnt && a[uu][vv] == color) {
      Dfs(uu, vv, color, ls);
    }
  }
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  a.assign(n + 2, vector<int>(m + 2, 0));
  used.assign(n + 2, vector<int>(m + 2, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int u, v, c;
    cin >> u >> v >> c;
    vector<pair<int, int>> ls;
    cnt++;
    Dfs(u, v, a[u][v], ls);
    for (auto [u, v] : ls) {
      a[u][v] = c;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << a[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
