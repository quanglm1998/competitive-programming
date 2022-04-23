#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
  cout << "Case #" << test << ": ";
  int n, c;
  cin >> n >> c;
  deque<int> q;
  c -= n - 1;
  if (c < 0) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  for (int i = n; i; i--) {
    int len = min(n - i, c);
    c -= len;
    q.push_front(i);
    reverse(q.begin(), q.begin() + len + 1);
  }
  if (c > 0) {
    cout << "IMPOSSIBLE\n";
  } else {
    for (int u : q) {
      cout << u << ' ';
    }
    cout << '\n';
  }
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