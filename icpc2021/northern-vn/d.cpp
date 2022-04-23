#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    string s;
    cin >> s;
    int res = 0;
    int last = -1;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '1') {
        int f = 0;
        if (i > 0 && s[i - 1] == '0' && i - 1 != last) {
          f = 1;
          last = i - 1;
        } else if (i + 1 < s.size() && s[i + 1] == '0') {
          f = 1;
          last = i + 1;
        }
        res += 1 - f;
      }
    }
    cout << res << '\n';
  }
  return 0;
}