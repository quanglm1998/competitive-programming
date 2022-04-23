#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int x;
    cin >> x;
    while (x % 11 && x >= 111) {
      x -= 111;
    }
    if (x % 11 == 0) x = 0;
    cout << (x ? "NO" : "YES") << '\n';
  }
  return 0;
}