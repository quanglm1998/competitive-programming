#include <bits/stdc++.h>

using namespace std;

const int N = 510;
int MOD;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void addTo(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void subTo(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mulTo(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

int n, m;
int fac[N], invFac[N];
int f[N], g[N][N], h[N][N];

int binom(int n, int k) {
    if (k < 0 || k > n) return 0;
    return mul(fac[n], mul(invFac[k], invFac[n - k]));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> MOD;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = mul(fac[i - 1], i);
    }
    invFac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; i--) {
        invFac[i] = mul(invFac[i + 1], i + 1);
    }

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            int foo = mul(f[j - 1], f[i - j]);
            mulTo(foo, binom(i - 1, j - 1));
            mulTo(foo, i + 1);
            addTo(f[i], foo);
        }
    }

    g[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 1; k <= i; k++) {
                if (j - i + k >= 0) {
                    int foo = mul(g[k - 1][j - i + k], f[i - k]);
                    mulTo(foo, binom(j, i - k));
                    addTo(g[i][j], foo);
                }
            }
        }
        g[i][i] = f[i];
    }

    for (int r = 1; r <= n; r++) {
        for (int l = 1; l + 2 <= r; l++) {
            int now = mul(r - l, r - l - 1);
            mulTo(now, invFac[r - l - 1]);
            mulTo(now, f[r - l - 1]);
            for (int j = 0; j < l; j++) {
                int foo = now;
                mulTo(foo, invFac[j]);
                mulTo(foo, g[l - 1][j]);
                addTo(h[r][r - l + j - 1], foo);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= m; i++) {
        for (int r = 1; r <= n; r++) {
            for (int delta = 1; delta <= r; delta++) {
                if (i - 1 - delta >= 0) {
                    int foo = mul(g[n - r][i - 1 - delta], binom(i - 1, i - 1 - delta));
                    mulTo(foo, h[r][delta]);
                    addTo(res, foo);
                }
            }
        }

        for (int j = 2; j <= i; j++) {
            int now = mul(g[n - j][i - j], f[j - 1]);
            mulTo(now, binom(i - 1, j - 1));
            mulTo(now, mul(j - 1, j));
            addTo(res, now);
        }   
    }
    cout << res << '\n';
    return 0;
}