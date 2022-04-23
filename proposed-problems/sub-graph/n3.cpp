#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n, m;
vector<int> adj[N];
bool used[N];

int Dfs(int u, int l, int r) {
  used[u] = 1;
  int res = 1;
  for (auto v : adj[u]) {
    if (v < l || v > r) continue;
    if (used[v]) continue;
    res += Dfs(v, l, r);
  }
  return res;
}

bool Check(int l, int r) {
  fill(used + l, used + r + 1, 0);
  int num = Dfs(l, l, r);
  if (num != r - l + 1) return false;
  int edges = 0;
  for (int i = l; i <= r; i++) {
    for (int j : adj[i]) {
      if (j >= l && j <= r) edges++;
    }
  }
  assert(edges % 2 == 0);
  return edges / 2 + 1 == num;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int res = 0;
  for (int i = 1; i <= n; i++) {
    int num = 0;
    for (int j = i; j <= n; j++) {
      res += Check(i, j);
    }
  }
  cout << res << endl;
  return 0;
}