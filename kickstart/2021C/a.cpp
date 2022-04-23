#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void add_to(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void sub_to(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mul_to(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

const int N = 100010;

int n, k;
char s[N];

void solve(int test) {
  cout << "Case #" << test << ": ";
  cin >> n >> k;
  cin >> (s + 1);
  
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