#include <bits/stdc++.h>

using namespace std;

void Solve(int test) {
  string s;
  cin >> s;
  int numA, numB, numC;
  numA = numB = numC = 0;
  for (auto u : s) {
    numA += u == 'A';
    numB += u == 'B';
    numC += u == 'C';
  }
  cout << (numA + numC == numB ? "YES" : "NO") << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}