#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> deg(n);
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < n; i++) {
    int out;
    cin >> out;
    string foo;
    for (int j = 0; j < out; j++) cin >> foo;
    int in;
    cin >> in;
    for (int j = 0; j < in; j++) {
      int u;
      string bar;
      cin >> u >> bar;
      u--;
      adj[u].push_back(i);
      deg[i]++;
    }
  }
  set<int> s;
  for (int i = 0; i < n; i++) {
    if (!deg[i]) {
      s.insert(i);
    }
  }
  vector<int> res;
  while (!s.empty()) {
    auto u = *s.rbegin();
    s.erase(u);
    res.push_back(u);
    for (int v : adj[u]) {
      deg[v]--;
      if (!deg[v]) {
        s.insert(v);
      }
    }
  }
  if (res.size() < n) {
    cout << "Impossible\n";
  } else {
    bool first = true;
    for (auto u : res) {
      if (!first) cout << ' ';
      first = false;
      cout << u + 1;
    }
    cout << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}