#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  cout << "Case #" << test << ": ";
  string s;
  cin >> s;
  int res = s.size() * 2;

  auto IsVowel = [&](char u) {
    return u == 'A' || u == 'E' || u == 'I' || u == 'O' || u == 'U';
  };

  for (auto c = 'A'; c <= 'Z'; c++) {
    int num = 0;
    for (auto u : s) {
      if (c != u) {
        num++;
        if (IsVowel(u) == IsVowel(c)) {
          num++;
        }
      }
    }
    res = min(res, num);
  }
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}