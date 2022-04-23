#include <bits/stdc++.h>

using namespace std;

const int LOG = 20;
const int N = 100010;
const int MOD = (int)1e9 + 7;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void add_to(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void sub_to(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mul_to(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

int fac[N];
int inv_fac[N];
int lg2[N];

int Binom(int n, int k) {
  if (k < 0 || k > n) return 0;
  return mul(fac[n], mul(inv_fac[k], inv_fac[n - k]));
}

pair<int, int> rmq[LOG][N];

pair<int, int> GetRMQ(int l, int r) {
  int lg = lg2[r - l + 1];
  return min(rmq[lg][l], rmq[lg][r - (1 << lg) + 1]);
}

int Solve(int l, int r, int need) {
  if (l > r) return 1;
  // cout << "solve " << l << ' ' << r << ' ' << need << endl;
  auto [val, pos] = GetRMQ(l, r);
  pos = -pos;
  // cout << "pos = " << pos << endl;
  if (val != need) return 0;
  int res = Binom(r - l, pos - l);
  mul_to(res, Solve(l, pos - 1, need));
  mul_to(res, Solve(pos + 1, r, need + 1));
  return res;
}

void solve(int test) {
  cout << "Case #" << test << ": ";
  int n;
  cin >> n;
  vector<int> a(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    rmq[0][i] = {a[i], -i};
  }
  for (int i = 1; i < LOG; i++) {
    for (int j = 1; j + (1 << i) - 1 <= n; j++) {
      rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << i - 1)]);
    }
  }
  cout << Solve(1, n, 1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  lg2[1] = 0;
  for (int i = 2; i < N; i++) {
    lg2[i] = lg2[i >> 1] + 1;
  }

  fac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[N - 1] = inv(fac[N - 1]);
  for (int i = N - 2; i >= 0; i--) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }

  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);  
  }
  return 0;
}