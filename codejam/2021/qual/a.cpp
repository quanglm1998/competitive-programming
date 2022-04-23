#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  cout << "Case #" << test << ": ";
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &u : a) {
    cin >> u;
  }
  int res = 0;
  for (int i = 0; i + 1 < n; i++) {
    int min_pos = i;
    for (int j = i + 1; j < n; j++) {
      if (a[min_pos] > a[j]) {
        min_pos = j;
      }
    }
    res += min_pos - i + 1;
    reverse(a.begin() + i, a.begin() + min_pos + 1);
  }
  cout << res << '\n';
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