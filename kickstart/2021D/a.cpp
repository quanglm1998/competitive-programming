#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  cout << "Case #" << test << ": ";
  vector<vector<int>> a(3, vector<int>(3, 0));
  cin >> a[0][0] >> a[0][1] >> a[0][2];
  cin >> a[1][0] >> a[1][2];
  cin >> a[2][0] >> a[2][1] >> a[2][2];
  int res = 0;
  res += (a[0][0] - a[0][1]) == (a[0][1] - a[0][2]);
  res += (a[2][0] - a[2][1]) == (a[2][1] - a[2][2]);
  res += (a[0][0] - a[1][0]) == (a[1][0] - a[2][0]);
  res += (a[0][2] - a[1][2]) == (a[1][2] - a[2][2]);
  map<int, int> m;
  if ((a[0][1] + a[2][1]) % 2 == 0) {
    m[(a[0][1] + a[2][1]) / 2]++;
  }
  if ((a[1][0] + a[1][2]) % 2 == 0) {
    m[(a[1][0] + a[1][2]) / 2]++;
  }
  if ((a[0][0] + a[2][2]) % 2 == 0) {
    m[(a[0][0] + a[2][2]) / 2]++;
  }
  if ((a[2][0] + a[0][2]) % 2 == 0) {
    m[(a[2][0] + a[0][2]) / 2]++;
  }
  int ans = 0;
  for (auto  [u, v] : m) {
    ans = max(ans, v);
  }
  cout << res + ans << '\n';
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