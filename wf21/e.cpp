#include <bits/stdc++.h>

using namespace std;

void solve() {
  int h, p;
  cin >> h >> p;
  long long n = (1ll << h) - 1;
  long long cur = 1;
  long long res = 0;
  while (cur <= n) {
    long long nxt = min(n, cur + p - 1);
    if (nxt < cur * 2) {
      long long need = n - cur + 1;
      res += (need + p - 1) / p;
      break;
    } else {
      nxt = cur * 2 - 1;
      res++;
      cur *= 2;
    }
  }
  cout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--) {
    solve();
  }
  return 0;

}