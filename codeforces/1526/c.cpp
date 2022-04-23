#include <bits/stdc++.h>

using namespace std;

/*
  Complete Node
  Change default values to WORST
  Change SegmentTree.init
*/
struct Node {
  long long sum;
  long long min_pref;
  long long delta;

  Node() {
    sum = min_pref = delta = 0;
  }

  template<typename T>
  void apply(int l, int r, const T &val) {
    delta += val;
    sum += val;
    min_pref += val;
  }

  void pull(const Node &u, const Node &v) {
    sum = u.sum + v.sum;
    min_pref = min(u.min_pref, v.min_pref + u.sum);
  }

  void push(int l, int r, Node &u, Node &v) {
    int m = l + r >> 1;
    u.apply(l, m, delta);
    v.apply(m + 1, r, delta);
    delta = 0;
  }
};

struct SegmentTree {
  void init(int node, int l, int r) {
    if (l == r) {
      t[node].apply(l, r, 0); // <-- change this
      return;
    }
    int m = l + r >> 1;
    init(node << 1, l, m);
    init(node << 1 | 1, m + 1, r);
    t[node].pull(t[node << 1], t[node << 1 | 1]);
  }

  /*------------------------------------------------------------------*/
  int n;
  vector<Node> t;
  
  SegmentTree(int n) : n(n) {
    t.assign(n << 2 | 1, {});
    init(1, 1, n);
  }

  template<typename T>
  void update(int node, int l, int r, int x, int y, const T &val) {
    if (x > r || y < l) return;
    if (x <= l && r <= y) {
      t[node].apply(l, r, val);
      return;
    }
    int m = l + r >> 1;
    t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
    update(node << 1, l, m, x, y, val);
    update(node << 1 | 1, m + 1, r, x, y, val);
    t[node].pull(t[node << 1], t[node << 1 | 1]);
  }

  Node get(int node, int l, int r, int x, int y) {
    if (x > r || y < l) return Node();
    if (x <= l && r <= y) return t[node];
    int m = l + r >> 1;
    t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
    Node p1 = get(node << 1, l, m, x, y);
    Node p2 = get(node << 1 | 1, m + 1, r, x, y);
    Node res;
    res.pull(p1, p2);
    return res;
  }
};


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  SegmentTree st(n);
  vector<int> a(n + 1, 0);
  vector<pair<int, int>> negs;
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i] >= 0) {
      st.update(1, 1, n, i, i, a[i]);
      res++;
    } else {
      negs.push_back({-a[i], i});
    }
  }
  sort(negs.begin(), negs.end());
  for (auto [u, id] : negs) {
    st.update(1, 1, n, id, id, -u);
    auto foo = st.get(1, 1, n, 1, n);
    if (foo.min_pref < 0) {
      st.update(1, 1, n, id, id, u);
    } else res++;
  }
  cout << res << endl;
  return 0;
}