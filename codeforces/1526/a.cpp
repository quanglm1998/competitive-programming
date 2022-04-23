#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    vector<int> a(n * 2);
    for (int &u : a) {
      cin >> u;
    }
    sort(a.begin(), a.end());
    vector<int> b(n * 2);
    for (int i = 0; i < n; i++) {
      b[i * 2] = a[i];
    }
    for (int i = 0; i < n; i++) {
      b[i * 2 + 1] = a[i + n];
    }
    for (auto u : b) cout << u << ' ';
      cout << '\n';
  }
  return 0;
}