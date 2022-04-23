#include <bits/stdc++.h>

using namespace std;

int main() {
  int t, n;
  cin >> t >> n;
  while (t--) {
    for (int i = 1; i < n; i++) {
      cout << "M " << i << ' ' << n << endl;
      int u;
      cin >> u;
      if (i < u) {
        cout << "S " << i << ' ' << u << endl;
        int st;
        cin >> st;
        assert(st == 1);
      }
    }
    cout << "D" << endl;
    int st;
    cin >> st;
    assert(st == 1);
  }
  return 0;
}