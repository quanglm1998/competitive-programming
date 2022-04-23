#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  int n;
  char k;
  cin >> n >> k;
  string s, t;
  cin >> s >> t;
  
  auto Add = [&](string &s) {
    for (int i = (int)s.size() - 1; i >= 0; i--) {
      if (s[i] == 'z') s[i] = 'a';
      else {
        s[i]++;
        break;
      }
    }
  };

  Add(s);

  while (s < t) {
    if (s.find(k) != string::npos) {
      cout << s << '\n';
      return;
    }
    Add(s);
  }
  cout << "NO\n";
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) solve(test);
  return 0;
}