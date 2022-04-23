#include <bits/stdc++.h>

using namespace std;

const int N = 25;
const int M = 50010;
const int MOD = 998244353;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void add_to(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void sub_to(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mul_to(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

int n, m;
int d[N][M];
int val[N];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> d[i][j];
    }
  }
  int fac = 1;
  for (int i = 1; i <= n; i++) {
    mul_to(fac, i);
  }
  int inv_fac = inv(fac);
  int res = 0;
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      val[j] = 0;
    }
    for (int j = 1; j <= n; j++) {
      val[d[j][i] - 1]++;
    }
    int num = 0;
    int ways = 1;
    for (int i = n; i; i--) {
      num += val[i];
      if (!num) {
        ways = 0;
        break;
      }
      mul_to(ways, num);
      num--;
    }
    add_to(res, sub(1, mul(ways, inv_fac)));
  }
  cout << res << endl;
  return 0;
}