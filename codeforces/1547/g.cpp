#include <bits/stdc++.h>

using namespace std;

// 1-indexed
// O(N + M)
struct SCC {
  int n;
  vector<vector<int>> adj;

  vector<int> belong;
  vector<int> low;
  vector<int> num;
  int cnt_tarjan;
  vector<int> st_tarjan;

  int num_SCC;
  vector<vector<int>> nodes_in_SCC;
  vector<vector<int>> SCC_adj;

  SCC(int n) : n(n), adj(n + 1, vector<int>()) {}

  // make sure that adj's size is n + 1
  SCC(int n, vector<vector<int>> adj) : n(n), adj(adj) {}

  SCC(int n, vector<int> *adj_) : n(n) {
    adj.assign(n + 1, vector<int>());
    for (int i = 1; i <= n; i++) adj[i] = adj_[i];
  }

  void AddEdge(int u, int v) { adj[u].push_back(v); }

  void Dfs(int u) {
    low[u] = num[u] = ++cnt_tarjan;
    st_tarjan.push_back(u);
    for (int v : adj[u]) {
      if (belong[v]) continue;  // v has already been in a SCC
      if (num[v])
        low[u] = min(low[u], num[v]);
      else {
        Dfs(v);
        low[u] = min(low[u], low[v]);
      }
    }
    if (low[u] == num[u]) {
      num_SCC++;
      nodes_in_SCC.push_back(vector<int>());
      while (1) {
        int v = st_tarjan.back();
        st_tarjan.pop_back();
        belong[v] = num_SCC;
        nodes_in_SCC[num_SCC].push_back(v);
        if (u == v) break;
      }
    }
  }

  // we can loop through all SCCs on DAG's reverse order
  void Solve(bool build_scc_graph = false, bool compress = true) {
    belong.assign(n + 1, 0);
    low.assign(n + 1, 0);
    num.assign(n + 1, 0);
    cnt_tarjan = 0;
    st_tarjan.clear();
    num_SCC = 0;
    nodes_in_SCC.resize(1);  // SCC is 1-indexed

    for (int i = 1; i <= n; i++) {
      if (!num[i]) Dfs(i);
    }

    if (build_scc_graph) BuildSCCGraph(compress);
  }

  // build SCC adjacent vector
  // if compress is set, remove all redundant elements from SCC_adj
  void BuildSCCGraph(bool compress = true) {
    SCC_adj.resize(num_SCC + 1);
    for (int i = 1; i <= n; i++) {
      for (auto j : adj[i]) {
        SCC_adj[belong[i]].push_back(belong[j]);
      }
    }
    if (compress) {
      for (int i = 1; i <= num_SCC; i++) {
        sort(SCC_adj[i].begin(), SCC_adj[i].end());
        SCC_adj[i].resize(unique(SCC_adj[i].begin(), SCC_adj[i].end()) -
                          SCC_adj[i].begin());
      }
    }
  }
};


void solve(int test) {
  int n;
  cin >> n;
  SCC scc(n);
  int m;
  cin >> m;
  vector<bool> is_loop(n + 1, false);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    if (u == v) is_loop[u] = true;
    scc.AddEdge(u, v);
  }
  scc.Solve(true, true);
  
  vector<int> res(n + 1, 0);
  
  vector<int> val(scc.num_SCC + 1, 0);

  for (int i = scc.num_SCC; i; i--) {
    bool has_one = false;
    for (auto u : scc.nodes_in_SCC[i]) {
      if (u == 1) {
        has_one = true;
        break;
      }
    }
    if (has_one) val[i] = 1;

    if (val[i] && (scc.nodes_in_SCC[i].size() > 1 || is_loop[scc.nodes_in_SCC[i][0]])) {
      val[i] = 3;
    }

    for (int u : scc.SCC_adj[i]) {
      if (val[i] >= 2) {
        val[u] = max(val[u], val[i]);
      } else if (val[i] == 1) {
        if (val[u] == 1) val[u] = max(val[u], 2);
        else val[u] = max(val[u], 1);
      }
    }

    for (auto u : scc.nodes_in_SCC[i]) {
      res[u] = val[i];
    }
  }

  for (int i = 1; i <= n; i++) {
    if (res[i] == 3) res[i] = -1;
    cout << res[i] << ' ';
  }
  cout << '\n';
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