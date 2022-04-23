#include <bits/stdc++.h>

using namespace std;

#define int long long

const int V = 5500;

inline int pos(int u) { return u << 1; }
inline int neg(int u) { return u << 1 | 1; }
// ZERO-indexed
// color[i] = 1 means we choose i
struct TwoSAT {
  int n;
  int numComp;
  vector<int> adj[V];
  int low[V], num[V], root[V], cntTarjan;
  vector<int> stTarjan;
  int color[V];

  TwoSAT(int n) : n(n * 2) {
    memset(root, -1, sizeof root);
    memset(low, -1, sizeof low);
    memset(num, -1, sizeof num);
    memset(color, -1, sizeof color);
    cntTarjan = 0;
    stTarjan.clear();
  }

  // u | v
  void addEdge(int u, int v) {
    adj[u ^ 1].push_back(v);
    adj[v ^ 1].push_back(u);
  }

  void tarjan(int u) {
    stTarjan.push_back(u);
    num[u] = low[u] = cntTarjan++;
    for (int v : adj[u]) {
      if (root[v] != -1) continue;
      if (low[v] == -1) tarjan(v);
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
      while (1) {
        int v = stTarjan.back();
        stTarjan.pop_back();
        root[v] = numComp;
        if (u == v) break;
      }
      numComp++;
    }
  }

  bool solve() {
    for (int i = 0; i < n; i += 2) if (root[i] == -1) tarjan(i);
    for (int i = 1; i < n; i += 2) if (root[i] == -1) tarjan(i);
    for (int i = 0; i < n; i += 2) {
      if (root[i] == root[i ^ 1]) return 0;
      color[i >> 1] = (root[i] < root[i ^ 1]);
    }
    return 1;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;

  struct Rect {
    int x, y, w, h;
  };

  struct Line {
    int x, y, z;
  };

  vector<Rect> a(n);
  for (auto &u : a) {
    cin >> u.x >> u.y >> u.w >> u.h;
    u.x *= 2;
    u.y *= 2;
  }

  // rotate = neg
  TwoSAT s(n);

  auto AddAnd = [&](int u, int v) {
    return s.addEdge(u ^ 1, v ^ 1);
  };

  auto Check = [&](Rect u, Rect v) {
    for (int i = 0; i < 2; i++) {
      if (u.y - u.h >= v.y + v.h) return false;
      if (u.x - u.w >= v.x + v.w) return false;
      swap(u, v);
    }
    return true;
  };

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int ri = 0; ri < 2; ri++) {
        for (int rj = 0; rj < 2; rj++) {
          if (Check(a[i], a[j])) {
            auto id_i = ri ? neg(i) : pos(i);
            auto id_j = rj ? neg(j) : pos(j);
            AddAnd(id_i, id_j);
          }
          swap(a[j].w, a[j].h);
        }
        swap(a[i].w, a[i].h);
      }
    }
  }
  if (!s.solve()) {
    cout << "No\n";
  } else {
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
      cout << (s.color[i] ? 'K' : 'Q');
    }
    cout << '\n';
  }
  return 0;
}