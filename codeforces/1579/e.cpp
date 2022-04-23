#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N];

void Solve(int test) {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  deque<int> q;
  for (int i = 1; i <= n; i++) {
    if (q.empty()) q.push_back(a[i]);
    else {
      if (q.front() < a[i]) q.push_back(a[i]);
      else q.push_front(a[i]);
    }
  }
  while (!q.empty()) {
    cout << q.front() << ' ';
    q.pop_front();
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}