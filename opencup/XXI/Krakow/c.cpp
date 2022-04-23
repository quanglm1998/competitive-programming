#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
vector<int> adj[N];
int par[N];
bool used[N];
bool is_in_circle[N];
vector<int> circle_ls;

bool Dfs(int u, int p) {
  par[u] = p;
  used[u] = true;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (used[v]) {
      while (u != v) {
        is_in_circle[u] = true;
        circle_ls.push_back(u);
        u = par[u];
      }
      is_in_circle[u] = true;
      circle_ls.push_back(u);
      return true;
    }
    if (Dfs(v, u)) return true;
  }
  return false;
}

int Go(int u, int p) {
  int res = 0;
  if (adj[u].size() == 1) return 1;
  for (int v : adj[u]) {
    if (v == p || is_in_circle[v]) continue;
    res += Go(v, u);
  }
  return res;
}

void Solve(int test) {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    is_in_circle[i] = false;
    used[i] = false;
  }
  circle_ls.clear();
  for (int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  Dfs(1, 0);
  if (circle_ls.size() == n) {
    cout << 3 << '\n';
    return;
  }
  vector<bool> has_tree(circle_ls.size());
  int res = 0;
  int pos = -1;
  for (int i = 0; i < circle_ls.size(); i++) {
    auto u = circle_ls[i];
    if (adj[u].size() == 2) continue;
    res += Go(u, 0);
    has_tree[i] = true;
    pos = i;
  }
  assert(pos != -1);
  rotate(has_tree.begin(), has_tree.begin() + pos, has_tree.end());
  assert(has_tree[0]);
  int mx = 0;
  int cur = 0;
  for (auto u : has_tree) {
    if (u) cur = 0;
    else cur++;
    mx = max(mx, cur);
    if (mx == 2) break;
  }
  res += mx;
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}