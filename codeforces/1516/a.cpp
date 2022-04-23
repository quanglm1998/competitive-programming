#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &u : a) {
      cin >> u;
    }
    while (k--) {
      int id = 0;
      while (id < a.size() && a[id] == 0) id++;
      a[id]--;
      a.back()++;
    }
    for (auto u : a) cout << u << ' ';
      cout << '\n';
  }
  return 0;
}