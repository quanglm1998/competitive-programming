#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }

  const int INF = 100010;
  vector<vector<int>> divs(INF, vector<int>());
  for (int i = 1; i < INF; i++) {
    for (int j = i; j < INF; j += i) {
      divs[j].push_back(i);
    }
  }

  long long res = 0;
  int cur = INF;
  for (int i = a.size() - 1; i >= 0; i--) {
    if (a[i] <= cur) {
      cur = a[i];
    } else {
      for (int j = divs[a[i]].size() - 1; j >= 0; j--) {
        if (divs[a[i]][j] <= cur) {
          cur = divs[a[i]][j];
          break;
        }
      }
    }
    res += a[i] / cur;
  }
  cout << res << '\n';
  return 0;
}