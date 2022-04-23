#include <bits/stdc++.h>

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  string s;
  cin >> s;

  if (s.size() < 3) {
    cout << "no\n";
    return 0;
  }
  auto ss = s.substr(s.size() - 3);
  if (ss[0] != '.') {
    cout << "no\n";
    return 0;
  }
  if (ss[1] != 'p' && ss[1] != 'P') {
    cout << "no\n";
    return 0;
  }
  if (ss[2] != 'y' && ss[2] != 'Y') {
    cout << "no\n";
    return 0;
  }
  cout << "yes\n";
  return 0;
}