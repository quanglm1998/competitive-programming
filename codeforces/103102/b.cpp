#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  int cur = s.size() - 1;
  int res = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == '0') continue;
    res += cur - i;
    cur--;
    res %= 3;
  }
  cout << (res ? "Alice" : "Bob") << '\n';
  return 0;
}