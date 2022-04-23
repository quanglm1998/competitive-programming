#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng_64(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n = rng() % 4 + 3;
  cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    cout << rng() % n + 1 << ' ';
  }
  cout << '\n';
  return 0;
}