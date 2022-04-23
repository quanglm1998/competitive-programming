#include <bits/stdc++.h>

using namespace std;

const int N = 20;
const int MOD = (int)1e9 + 7;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, long long v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void add_to(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void sub_to(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mul_to(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

int c[N][N];
// ways[x][y] is number of ways to arrange fans to x teams that has y different team subset
int ways[N][N];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 || j == i) c[i][j] = 1;
      else c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
    }
  }
  for (int i = 1; i <= 4; i++) {
    for (int mask = 0; mask < (1 << (1 << i)); mask++) {
      vector<int> val(i, 0);
      int cnt = 0;
      for (int pos = 0; pos < (1 << i); pos++) {
        if (mask >> pos & 1) {
          cnt++;
          for (int j = 0; j < i; j++) {
            if (pos >> j & 1) {
              val[j] |= 1 << pos;
            }
          }
        }
      }

      val.push_back(0);
      val.push_back(mask);
      sort(val.begin(), val.end());
      bool flag = false;
      for (int i = 0; i + 1 < val.size(); i++) {
        if (val[i] == val[i + 1]) {
          flag = true;
          break;
        }
        for (int j = i + 1; j < val.size(); j++) {
          if (!binary_search(val.begin(), val.end(), val[i] | val[j])) {
            flag = true;
            break;
          }
          if (!binary_search(val.begin(), val.end(), val[i] & val[j])) {
            flag = true;
            break;
          }
        }
      }
      if (!flag) {
        ways[i][cnt]++;
      }
    }
  }
  int tc;
  cin >> tc;
  while (tc--) {
    int m;
    long long n;
    cin >> n >> m;
    if (m == 2) {
      cout << 2 << '\n';
    } else {
      int res = 0;
      for (int k = 0; k <= (1 << m - 2); k++) {
        int cur = 0;
        for (int i = 0; i <= k; i++) {
          int now = mul(c[k][i], power(i, n));
          if ((k - i) % 2) sub_to(cur, now);
          else add_to(cur, now);
        }
        mul_to(cur, ways[m - 2][k]);
        add_to(res, cur);
      }
      mul_to(res, m);
      mul_to(res, m - 1);
      cout << res << '\n';
    }
  }
  return 0;
}