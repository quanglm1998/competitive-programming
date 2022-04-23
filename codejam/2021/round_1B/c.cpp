#include <bits/stdc++.h>

using namespace std;

int n, b;
long long p;

void solve(int test) {
  vector<int> h(n + 1, 0);
  int p[4] = {1, 1, 1, 1};
  for (int i = 1; i <= n * b; i++) {
    int d;
    cin >> d;
    while (p[0] <= n && h[p[0]] >= b) p[0]++;
    while (p[1] <= n && h[p[1]] >= b - 1) p[1]++;
    while (p[2] <= n && h[p[2]] >= b - 2) p[2]++;
    while (p[3] <= n && h[p[3]] >= b - 3) p[3]++;
    if (d == 9) {
      h[p[0]]++;
      cout << p[0] << endl;
    } else if (d >= 8) {
      if (p[1] <= n) {
        h[p[1]]++;
        cout << p[1] << endl;
      } else {
        h[p[0]]++;
        cout << p[0] << endl;
      }
    } else if (d >= 7) {
      if (p[2] <= n) {
        h[p[2]]++;
        cout << p[2] << endl;
      } else if (p[1] <= n) {
        h[p[1]]++;
        cout << p[1] << endl;
      } else {
        h[p[0]]++;
        cout << p[0] << endl;
      }
    } else {
      if (p[3] <= n) {
        h[p[3]]++;
        cout << p[3] << endl;
      } else if (p[2] <= n) {
        h[p[2]]++;
        cout << p[2] << endl;
      } else if (p[1] <= n) {
        h[p[1]]++;
        cout << p[1] << endl;
      } else {
        h[p[0]]++;
        cout << p[0] << endl;
      }
    }
  }
}

int main() {
  // ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  cin >> n >> b >> p;
  for (int test = 1; test <= tc; ++test) {
    solve(test); 
  }
  int ver;
  cin >> ver;
  return 0;
}
