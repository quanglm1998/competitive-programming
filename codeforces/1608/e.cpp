#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
  int n;
  vector<int> cnt[2];

  explicit SegmentTree(int n) : n(n) {
    cnt[0].assign(n << 2 | 1, 0);
    cnt[1].assign(n << 2 | 1, 0);
  }

  void Update(int node, int l, int r, int x, int zero, int one) {
    if (x < l || x > r) return;
    if (l == r) {
      cnt[0][node] += zero;
      cnt[1][node] += one;
      return;
    }
    int m = l + r >> 1;
    Update(node << 1, l, m, x, zero, one);
    Update(node << 1 | 1, m + 1, r, x, zero, one);
    cnt[0][node] = cnt[0][node << 1] + cnt[0][node << 1 | 1];
    cnt[1][node] = cnt[1][node << 1] + cnt[1][node << 1 | 1];
  }

  int GetMin(int node, int l, int r, int zero, int one) {
    if (l == r) {
      return min(zero + cnt[0][node], one);
    }
    int m = l + r >> 1;
    int res = 0;
    auto cur_zero = zero + cnt[0][node << 1];
    auto cur_one = one + cnt[1][node << 1 | 1];
    res = max(res, min(cur_zero, cur_one));
    if (cur_zero > cur_one) {
      res = max(res, GetMin(node << 1, l, m, zero, cur_one));
    } else {
      res = max(res, GetMin(node << 1 | 1, m + 1, r, cur_zero, one));
    }
    return res;
  }
};

struct Point {
  int x, y, c;
};

string to_string(Point u) {
  return "{" + to_string(u.x) + ", " + to_string(u.y) + "," + to_string(u.c) + "}";
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<Point> a(n);
  vector<int> vals;
  for (auto &u : a) {
    cin >> u.x >> u.y >> u.c;
    vals.push_back(u.x);
    vals.push_back(u.y);
    u.c--;
  }

  auto Normalize = [&](vector<int> &a) {
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
  };

  Normalize(vals);

  auto m = vals.size();
  for (auto &u : a) {
    u.x = lower_bound(vals.begin(), vals.end(), u.x) - vals.begin();
    u.y = lower_bound(vals.begin(), vals.end(), u.y) - vals.begin();
  }

  int res = 0;

  auto Solve = [&](const vector<Point> &b) {
    int num = n / 3;
    int cur = 0;

    SegmentTree t_x(m);
    SegmentTree t_y(m);

    for (int i = 0; i < m; i++) {
      while (cur < n && b[cur].x <= i) {
        if (b[cur].c == 0) {
          num--;
        } else if (b[cur].c == 1) {
          t_x.Update(1, 0, m - 1, b[cur].x, 1, 0);
          t_y.Update(1, 0, m - 1, b[cur].y, 1, 0);
        } else if (b[cur].c == 2) {
          t_x.Update(1, 0, m - 1, b[cur].x, 0, 1);
          t_y.Update(1, 0, m - 1, b[cur].y, 0, 1);
        } else {
          exit(1);
        }
        cur++;
      }

      res = max(res, min(num, t_x.GetMin(1, 0, m - 1, 0, 0)));
      res = max(res, min(num, t_y.GetMin(1, 0, m - 1, 0, 0)));
    }
  };

  auto SolveAll = [&](const vector<Point> &a) {
    vector<int> id(3);
    iota(id.begin(), id.end(), 0);
    while (1) {
      auto b = a;
      for (auto &p : b) {
        p.c = id[p.c];
      }
      Solve(b);
      if (!next_permutation(id.begin(), id.end())) break;
    }
  };

  for (int z = 0; z < 2; z++) {
    for (auto &p : a) {
      if (z) swap(p.x, p.y);
    }
    sort(a.begin(), a.end(), [&](const Point & u, const Point & v) {
      return u.x < v.x;
    });
    SolveAll(a);
    for (auto &p : a) {
      p.x = m - p.x - 1;
    }
    reverse(a.begin(), a.end());
    SolveAll(a);
  }

  cout << res * 3 << '\n';
  return 0;
}