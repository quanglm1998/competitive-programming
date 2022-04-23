#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, d;
int a[N];
int dist[N];

void Solve(int test) {
  cin >> n >> d;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  fill(dist, dist + n, -1);
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) {
      dist[i] = 0;
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int v = (u + n - d) % n;
    if (dist[v] == -1) {
      dist[v] = dist[u] + 1;
      q.push(v);
    }
  }
  for (int i = 0; i < n; i++) {
    if (dist[i] == -1) {
      cout << -1 << '\n';
      return;
    }
  }
  cout << *max_element(dist, dist + n) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}