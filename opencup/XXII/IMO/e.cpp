#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  int n;
  cin >> n;
  vector<int> all(n);
  iota(all.begin(), all.end(), 0);

  auto Query = [&](const vector<int> &a) {
    cout << "? " << a.size();
    for (auto u : a) {
      cout << ' ' << u + 1;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
  };

  auto tot = Query(all);
  for (int i = 0; i < 20; i++) {
    vector<int> a, b;
    for (int j = 0; j < n; j++) {
      if ((j + 1) >> i & 1) {
        a.push_back(j);
      } else {
        b.push_back(j);
      }
    }
    if ((tot - Query(a) - Query(b)) % 2) {
      cout << "! NO\n";
      return 0;
    }
  }

  cout << "! YES\n";
  return 0;
}