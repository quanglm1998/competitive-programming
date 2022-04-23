#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;
  int sum = 0;
  for (auto u : s) {
    if (u == 'F' || u == 'B' || u == 'N' || u == 'A' || u == 'C' || u == 'W' || u == 'R' || u == 'D' || u == 'S') {
      sum ^= 1;
    }
  }
  cout << (sum ? "NO" : "YES") << endl;
  return 0;
}
