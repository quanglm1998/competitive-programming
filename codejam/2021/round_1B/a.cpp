#include <bits/stdc++.h>

using namespace std;

#define bigInt __int128_t
bigInt MOD = 360 * 120000000000ll;
bigInt INV11 = 15709090909091ll;

bool Check(int *order, long long *a) {
  bigInt h = a[order[0]];
  bigInt m = a[order[1]];
  bigInt s = a[order[2]];

  bigInt foo = (m - (h * 12) % MOD + MOD) % MOD;
  bigInt delta = foo * INV11 % MOD;

  bigInt left = (s + delta) % MOD;
  bigInt right = 720 * (h + delta) % MOD;

  if (left != right) return false;
  h = (h + delta) % MOD;

  // cout << (long long )delta << endl;

  cout << (long long)(h / 1000000000ll / 60 / 60) << ' ';
  cout << (long long)(h / 1000000000ll / 60) % 60 << ' ';
  cout << (long long)(h / 1000000000ll) % 60 << ' ';
  cout << (long long)(h % 1000000000ll) << '\n';
  return true;
}

void solve(int test) {
  cout << "Case #" << test << ": ";
  long long a[3];
  cin >> a[0] >> a[1] >> a[2];
  int order[3];
  iota(order, order + 3, 0);
  while (1) {
    if (Check(order, a)) break;
    if (!next_permutation(order, order + 3)) break;
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