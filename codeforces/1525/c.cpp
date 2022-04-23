#include <bits/stdc++.h>

using namespace std;

struct Node {
  int x, dir, id;
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int n, m;
    cin >> n >> m;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i].x;
    }
    for (int i = 0; i < n; i++) {
      char u;
      cin >> u;
      a[i].dir = u == 'R';
      a[i].id = i;
    }
    sort(a.begin(), a.end(), [](const Node &x, const Node &y) {
      return x.x < y.x;
    });
    vector<int> res(n, -1);
    vector<Node> ls[2];
    for (auto u : a) {
      int id = u.x % 2;
      if (u.dir == 1) ls[id].push_back(u);
      else {
        if (ls[id].empty()) {
          u.dir = 0;
          u.x = -u.x;
          ls[id].push_back(u);
        } else {
          auto v = ls[id].back();
          ls[id].pop_back();
          auto w = (u.x - v.x) / 2;
          res[u.id] = res[v.id] = w;
        }
      }
    }
    for (int id = 0; id < 2; id++) {
      while (ls[id].size() >= 2) {
        auto u = ls[id].back();
        ls[id].pop_back();
        auto v = ls[id].back();
        ls[id].pop_back();
        u.x = m * 2 - u.x;
        res[u.id] = res[v.id] = (u.x - v.x) / 2;
      }
    } 
    for (auto u : res) {
      cout << u << ' ';
    }
    cout << '\n';
  }
  return 0;
}