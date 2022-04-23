#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  int k, n, m;
  cin >> k >> n >> m;
  queue<int> a, b;
  vector<int> res;
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    a.push(u);
  }
  for (int i = 0; i < m; i++) {
    int u;
    cin >> u;
    b.push(u);
  }
  while (!a.empty() || !b.empty()) {
    int choose = -1;
    int value = -1;
    if (a.empty()) {
      choose = 1;
      value = b.front();
    } else if (b.empty()) {
      choose = 0;
      value = a.front();
    } else {
      value = min(a.front(), b.front());
      choose = a.front() > b.front();
    }
    if (value > k) {
      cout << -1 << '\n';
      return;
    }
    if (value == 0) k++;
    if (choose) b.pop();
    else a.pop();
    res.push_back(value);
  }
  for (auto u : res) cout << u << ' ';
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