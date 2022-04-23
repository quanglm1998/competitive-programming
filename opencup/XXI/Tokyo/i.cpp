#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
inline int add(int u, int v, int m = MOD) { return (u += v) >= m ? u - m : u; }
inline int sub(int u, int v, int m = MOD) { return (u -= v) < 0 ? u + m : u; }
inline int mul(int u, int v, int m = MOD) { return (long long)u * v % m; }
inline int power(int u, int v, int m = MOD) {
  int res = 1;
  for (; v; v >>= 1, u = mul(u, u, m)) if (v & 1) res = mul(res, u, m);
  return res;
}
inline int neg(int u, int m = MOD) { return sub(0, u, m); }
inline int inv(int u, int m = MOD) { return power(u, m - 2, m); }
inline int add_to(int &u, int v, int m = MOD) { return u = add(u, v, m); }
inline int sub_to(int &u, int v, int m = MOD) { return u = sub(u, v, m); }
inline int mul_to(int &u, int v, int m = MOD) { return u = mul(u, v, m); }

const int N = 250010;

int n, m;
int a[N];
bool used[N];

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
    used[a[i]] = 1;
  }
  int first_pos = m;
  for (int i = 1; i < m; i++) {
    if (a[i] > a[i + 1]) {
      first_pos = i;
      break;
    }
  }
  int cur_num = 0;
  int cur_pos = 0;
  int res = 1;
  for (int i = 1; i <= n; i++) {
    if (used[i]) continue;
    while (cur_pos + 1 <= first_pos && a[cur_pos + 1] < i) {
      cur_pos++;
    }
    cur_num++;
    if (cur_pos == first_pos) cur_pos++;
    mul_to(res, cur_pos - 1 + cur_num);
  }
  cout << res << endl;
  return 0;
}