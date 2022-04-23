#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  vector<int> res(n, 0);
  res[0] = 0;
  for (int i = 1; i < n; i++) {
    int value = a[i] | a[i - 1];
    res[i] = value ^ a[i];
    a[i] = value;
  }
  for (auto u : res) {
    cout << u << ' ';
  }
  cout << '\n';
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