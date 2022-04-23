#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
inline int add(int u, int v, int m = MOD) { return (u += v) >= m ? u - m : u; }
inline int sub(int u, int v, int m = MOD) { return (u -= v) < 0 ? u + m : u; }
inline int mul(int u, int v, int m = MOD) { return (long long)u * v % m; }
inline int power(int u, long long v, int m = MOD) {
  int res = 1;
  for (; v; v >>= 1, u = mul(u, u, m)) if (v & 1) res = mul(res, u, m);
  return res;
}
inline int neg(int u, int m = MOD) { return sub(0, u, m); }
inline int inv(int u, int m = MOD) { return power(u, m - 2, m); }
inline int add_to(int &u, int v, int m = MOD) { return u = add(u, v, m); }
inline int sub_to(int &u, int v, int m = MOD) { return u = sub(u, v, m); }
inline int mul_to(int &u, int v, int m = MOD) { return u = mul(u, v, m); }

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int root = 2;
  while (power(root, 7) != 1) root++;
  vector<int> primitive_roots(7, 1);
  for (int i = 1; i < 7; i++) primitive_roots[i] = mul(primitive_roots[i - 1], root);

  int n;
  long long k;
  cin >> n >> k;

  const int SZ = 823543;
  const int INV_SZ = inv(SZ);

  vector<int> a(SZ, 0);
  for (int i = 0; i < n; i++) {
    int u;
    cin >> u;
    int now = 0;
    int cur = 1;
    for (int j = 0; j < 7; j++) {
      now += cur * (u % 2);
      u /= 2;
      cur *= 7;
    }
    a[now]++;
  }

  auto DFT = [&](vector<int> &a, bool inverse) {
    if (inverse) reverse(a.begin() + 1, a.end());
    vector<int> b = a;
    for (int i = 0; i < b.size(); i++) {
      int id = i;
      a[i] = 0;
      for (int j = 0; j < b.size(); j++) {
        add_to(a[i], mul(primitive_roots[(i * j) % 7], b[j]));
      }
    }
  };

  auto MDFT = [&](vector<int> &a, bool inverse) {
    for (int i = 1; i < SZ; i *= 7) {
      for (int j = 0; j < i; j++) {
        for (int k = j; k < SZ; k += i * 7) {
          vector<int> now(7);
          for (int x = 0; x < 7; x++) {
            now[x] = a[k + i * x];
          }
          DFT(now, inverse);
          for (int x = 0; x < 7; x++) {
            a[k + i * x] = now[x];
          }
        }
      }
    }
    if (inverse) {
      for (auto &u : a) mul_to(u, INV_SZ);
    }
  };

  MDFT(a, 0);
  for (auto &u : a) u = power(u, k);
  MDFT(a, 1);

  cout << a[0] << '\n';
  return 0;
}