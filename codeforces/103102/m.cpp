#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int n, m, k;
int cnt[N];

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> k >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
  }
  for (int i = 1; i <= n * k; i++) {
    int u;
    cin >> u;
    cout << ++cnt[u] << ' ';
  }
  cout << endl;
  return 0;
}