#include <bits/stdc++.h>

using namespace std;

const int N = 800010;

int n;
vector<int> adj[N];
vector<int> ls[N];
int p[N];
int h[N];
int used[N];

void Dfs(int u, int par) {
  p[u] = par;
  h[u] = h[par] + 1;
  for (int v : adj[u]) {
    if (v != par) {
      Dfs(v, u);
    }
  } 
}

int GetNxt(int u) {
  if (!used[u]) return u;
  return p[u] = GetNxt(p[u]);
}

void Join(int u, int v) {
  while (1) {
    u = GetNxt(u);
    v = GetNxt(v);
    if (u == v) break;
    if (h[u] < h[v]) swap(u, v);
    assert(!used[u]);
    used[u] = 1;
  }
}

void Solve(int test) {
  cout << "Case #" << test << ": ";
  cin >> n;
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    ls[i].clear();
    used[i] = 0;
    p[i] = 0;
    h[i] = 0;
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  Dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    int u;
    cin >> u;
    ls[u].push_back(i);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j + 1 < ls[i].size(); j++) {
      Join(ls[i][j], ls[i][j + 1]);
    }
  }

  int res = 0;
  for (int i = 2; i <= n; i++) {
    res += !used[i];
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