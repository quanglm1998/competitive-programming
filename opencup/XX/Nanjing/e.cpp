#include <bits/stdc++.h>

using namespace std;

const int N = 3010;

struct Point {
  int x, y, id, type;

  Point operator-(const Point &other) const {
    Point res;
    return {x - other.x, y - other.y, 0, 0};
  }
  
  long long operator%(const Point &other) const {
    return 1ll * x * other.y - 1ll * y * other.x;
  }
};

int n, m;
Point a[N + N];
vector<pair<int, int>> res[2];

long long CCW(Point u, Point v, Point w) {
  u = v - u;
  v = w - v;
  return u % v;
}

bool IsInside(const Point &x, const Point &u, const Point &v, const Point &w) {
  auto foo = CCW(x, u, v);
  auto bar = CCW(x, v, w);
  auto baz = CCW(x, w, u);
  return foo != 0 && bar != 0 && baz != 0 && foo > 0 == bar > 0 && bar > 0 == baz > 0;
}

void Solve(Point u, Point v, Point w, vector<Point> ls) {
  if (ls.empty()) return;
  int pos = -1;
  for (int i = 0; i < ls.size(); i++) {
    if (ls[i].type == u.type) {
      pos = i;
      break;
    }
  }
  if (pos != -1) {
    res[u.type].push_back({u.id, ls[pos].id});
    vector<Point> ls_x, ls_y, ls_z;
    for (int i = 0; i < ls.size(); i++) {
      if (i == pos) continue;
      if (IsInside(ls[i], u, ls[pos], v)) ls_x.push_back(ls[i]);
      else if (IsInside(ls[i], u, ls[pos], w)) ls_y.push_back(ls[i]);
      else ls_z.push_back(ls[i]);
    }
    Solve(v, u, ls[pos], ls_x);
    Solve(w, u, ls[pos], ls_y);
    Solve(ls[pos], v, w, ls_z);
  } else {
    sort(ls.begin(), ls.end(), [&](Point x, Point y) {
      return CCW(v, x, y) > 0;
    });
    for (auto p : ls) {
      res[v.type].push_back({v.id, p.id});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
    a[i].id = i;
    a[i].type = 0;
  }
  for (int i = n + 1; i <= n + m; i++) {
    cin >> a[i].x >> a[i].y;
    a[i].id = i;
    a[i].type = 1;
  }
  sort(a + 1, a + n + m + 1, [](const Point &u, const Point &v) {
    if (u.x != v.x) return u.x < v.x;
    return u.y < v.y;
  });

  vector<Point> hull;

  for (int i = 1; i <= n + m; i++) {
    while (hull.size() >= 2 && CCW(hull[hull.size() - 2], hull.back(), a[i]) >= 0) {
      hull.pop_back();
    }
    hull.push_back(a[i]);
  }
  int sz = hull.size();
  for (int i = n + m - 1; i >= 1; i--) {
    while (hull.size() > sz && CCW(hull[hull.size() - 2], hull.back(), a[i]) >= 0) {
      hull.pop_back();
    }
    hull.push_back(a[i]);
  }
  hull.pop_back();
  int diff_pos = -1;
  for (int i = 0; i < hull.size(); i++) {
    if (hull[i].type != hull[(i + 1) % hull.size()].type) {
      diff_pos = (i + 1) % hull.size();
      break;
    }
  }

  if (diff_pos == -1) {
    int pos = -1;
    for (int i = 1; i <= n + m; i++) {
      if (a[i].type != hull[0].type) {
        pos = i;
        break;
      }
    }
    assert(pos != -1);
    for (int i = 0; i < hull.size(); i++) {
      Point &root = a[pos];
      Point &x = hull[i];
      Point &y = hull[(i + 1) % hull.size()];
      if (i + 1 < hull.size()) {
        res[x.type].push_back({x.id, y.id});
      }
      vector<Point> ls;
      for (int j = 1; j <= n + m; j++) {
        if (IsInside(a[j], root, x, y)) ls.push_back(a[j]);
      }
      Solve(root, x, y, ls);
    }
  } else {
    rotate(hull.begin(), hull.begin() + diff_pos, hull.end());
    int num_diff = 0;
    diff_pos = -1;
    for (int i = 0; i + 1 < hull.size(); i++) {
      num_diff += hull[i].type != hull[i + 1].type;
      if (diff_pos == -1 && hull[i].type != hull[i + 1].type) {
        diff_pos = i + 1;
      }
    }
    assert(diff_pos != -1);
    if (num_diff > 1) {
      cout << "Impossible\n";
      return 0;
    }
    for (int i = 0; i + 1 < diff_pos; i++) {
      Point &root = hull[diff_pos];
      Point &x = hull[i];
      Point &y = hull[(i + 1) % hull.size()];
      res[x.type].push_back({x.id, y.id});
      vector<Point> ls;
      for (int j = 1; j <= n + m; j++) {
        if (IsInside(a[j], root, x, y)) ls.push_back(a[j]);
      }
      Solve(root, x, y, ls);
    }
    for (int i = diff_pos; i + 1 < hull.size(); i++) {
      Point &root = hull[0];
      Point &x = hull[i];
      Point &y = hull[(i + 1) % hull.size()];
      res[x.type].push_back({x.id, y.id});
      vector<Point> ls;
      for (int j = 1; j <= n + m; j++) {
        if (IsInside(a[j], root, x, y)) ls.push_back(a[j]);
      }
      Solve(root, x, y, ls);
    }
  }
  for (auto u : res[0]) {
    cout << u.first << ' ' << u.second << '\n';
  }
  for (auto u : res[1]) {
    cout << u.first - n << ' ' << u.second - n << '\n';
  }
  return 0;
}