#include <bits/stdc++.h>

using namespace std;

const int N = 550;

int n;
int a[N * 2][N];

void solve(int test) {
  cin >> n;
  for (int i = 1; i <= n * 2; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n * 2; i++) {
      for (int j = i + 1; j <= n * 2; j++) {
        if (a[i][k] == a[j][k]) {
          cout << i << ' ' << j << ' ' << k << endl;
        }
      }
    }
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