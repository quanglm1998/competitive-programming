#include <bits/stdc++.h>

using namespace std;

#define long long int

const int N = 110;

/*
  U = max capacity
  Complexity: O(V^2 * E)
  O(min(E^{1/2}, V^{2/3}) * E) if U = 1
  O(V^{1/2} * E)$ for bipartite matching.
*/
template <typename flow_t = int>
struct DinicFlow {
  const flow_t INF = numeric_limits<flow_t>::max() / 2; // 1e9
 
  int n, s, t;
  vector<vector<int>> adj;
  vector<int> d, cur;
  vector<int> to;
  vector<flow_t> c, f;
 
  DinicFlow(int n, int s, int t) : n(n), s(s), t(t), adj(n, vector<int>()), d(n, -1), cur(n, 0) {}
 
  int addEdge(int u, int v, flow_t _c) {
    adj[u].push_back(to.size()); 
    to.push_back(v); f.push_back(0); c.push_back(_c);
    adj[v].push_back(to.size());
    to.push_back(u); f.push_back(0); c.push_back(0);
    return (int)to.size() - 2;
  }
 
  bool bfs() {
    fill(d.begin(), d.end(), -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto edgeId : adj[u]) {
        int v = to[edgeId];
        if (d[v] == -1 && f[edgeId] < c[edgeId]) {
          d[v] = d[u] + 1;
          if (v == t) return 1;
          q.push(v);
        }
      }
    }
    return d[t] != -1;
  }
 
  flow_t dfs(int u, flow_t res) {
    if (u == t || !res) return res;
    for (int &i = cur[u]; i < adj[u].size(); i++) {
      int edgeId = adj[u][i];
      int v = to[edgeId];
      if (d[v] == d[u] + 1 && f[edgeId] < c[edgeId]) {
        flow_t foo = dfs(v, min(res, c[edgeId] - f[edgeId]));
        if (foo) {
          f[edgeId] += foo;
          f[edgeId ^ 1] -= foo;
          return foo;
        }
      }
    }
    return 0;
  }
 
  flow_t maxFlow() {
    flow_t res = 0;
    while (bfs()) {
      fill(cur.begin(), cur.end(), 0);
      while (flow_t aug = dfs(s, INF)) res += aug;
    }
    return res;
  }
};


int n, m, k;
vector<int> adj[N];
int x[N], y[N];
bool to[N], from[N];
vector<vector<int>> best_action;
int res = -1;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  for (int i = 1; i <= k; i++) {
    cin >> x[i] >> y[i];
  }
  vector<vector<int>> cur_action;

  auto Update = [&](vector<vector<int>> action, int point) {
    if (res < point) {
      res = point;
      best_action = action;
    }
  };

  auto GetMin = [&]() {
    DinicFlow<> f(n * 2 + 2, 0, n * 2 + 1);
    for (int i = 1; i <= n; i++) {
      for (auto u : adj[i]) {
        f.addEdge(i, u + n, 1);
      }
      if (!from[i]) f.addEdge(f.s, i, 1);
      if (!to[i]) f.addEdge(i + n, f.t, 1);
    }
    auto u = f.maxFlow();
    return n - u;
  };

  int cur_point = 0;
  pair<int, int> min_cost(1e9, 1e9);
  for (int i = 1; i <= k; i++) {
    // block all
    vector<vector<int>> foo = cur_action;
    vector<int> this_action;
    for (int i = 1; i <= n; i++) {
      if (!from[i]) this_action.push_back(i);
      if (!to[i]) this_action.push_back(-i);
    }
    foo.push_back(this_action);
    int this_point = cur_point;
    for (int j = i + 1; j <= k; j++) {
      this_point += x[j];
    }
    Update(foo, this_point);

    min_cost = min(min_cost, {y[i], i});
    cur_point += x[i];
    cur_action.push_back(vector<int>());
    while (GetMin() <= i) {
      pair<int, int> best(1e9, 1e9);
      for (int i = 1; i <= n; i++) {
        if (!from[i]) {
          from[i] = 1;
          auto val = GetMin();
          best = min(best, {val, i});
          from[i] = 0;
        }
        if (!to[i]) { 
          to[i] = 1;
          auto val = GetMin();
          best = min(best, {val, -i});
          to[i] = 0;
        }
      }
      if (best.second < 0) to[-best.second] = 1;
      else from[best.second] = 1;
      cur_point -= min_cost.first;
      cur_action[cur_point - 1].push_back(best.second);
      cout << "added " << cur_point << ' ' << best.second << endl;
    }
  }
  Update(cur_action, cur_point);
  cout << res << endl;
  for (auto u : best_action) {
    for (auto v : u) cout << v << ' ';
      cout << endl;
  }
  return 0;
}