#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  string s;
  cin >> s;
  for (int i = (int)s.size() - 1; i >= 0; i--) {
    if (s[0] - 'a' == i) {
      s = s.substr(1);
      continue;
    }
    if (s.back() - 'a' == i) {
      s.pop_back();
      continue;
    }
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);
  }
  return 0;
}