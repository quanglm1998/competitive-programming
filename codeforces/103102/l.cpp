#include <bits/stdc++.h>

using namespace std;

int const N = 1e5 + 5;

struct politician
{
  int m, p, id;
  politician(){};
  politician(int m, int p, int id): m(m), p(p), id(id){};
};

politician a[N];

int n;

bool cmp(politician p, politician q) {
  int sum_p = p.m + p.p;
  int sum_q = q.m + q.p;
  if (sum_p != sum_q) {
    return sum_p > sum_q;
  }
  return p.m > q.m;
}

bool check(int mid) {
  multiset< int > set_left;
  multiset< int > set_right, rest_right;
  long long sum_left = 0, sum_right = 0;
  for (int i = 1; i <= mid; i++) {
    sum_left += a[i].m;
    set_left.insert(a[i].m);
  }

  for (int i = mid + 1; i <= n; i++) {
    set_right.insert(a[i].p);
    sum_right += a[i].p;
  }

  while (set_right.size() > mid) {
    auto it = prev(set_right.end());
    sum_right -= *it;
    rest_right.insert(*it);
    set_right.erase(it);
  }

  if (sum_left >= sum_right) {
    return true;
  }

  for (int i = mid + 1; i <= n - mid; i++) {
    int v = *set_left.begin();
    if (a[i].m > v) {
      set_left.erase(set_left.find(v));
      set_left.insert(a[i].m);
      sum_left += a[i].m - v;
    }

    if (rest_right.find(a[i].p) != rest_right.end()) {
      rest_right.erase(rest_right.find(a[i].p));
    } else {
      set_right.erase(set_right.find(a[i].p));
      int smallest = *rest_right.begin();
      set_right.insert(smallest);
      rest_right.erase(rest_right.find(smallest));
      sum_right += smallest - a[i].p;
    }
    if (sum_left >= sum_right) {
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].m;
    a[i].id = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i].p;
  }
  sort(a + 1, a + n + 1, cmp);

  int l = 0;
  int r = n / 2 + 1;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << l << endl;
}