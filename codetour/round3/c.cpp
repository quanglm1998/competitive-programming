#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
const int N = 410;

int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

int sub(int u, int v) {
    return (u -= v) < 0 ? u + MOD : u;
}

int mul(int u, int v) {
    return (long long)u * v % MOD;
}

int n;
char s[N];
int f[N][N], g[N][N], foo[N][N];
int ff[N], gg[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof foo);
    f[1][1] = g[1][1] = 1;
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        memset(foo, 0, sizeof foo);
        if (s[i] == 'U') {
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    if (!f[j][k]) continue;
                    foo[j][k] = add(foo[j][k], f[j][k]);
                    if (k < j) foo[j][k + 1] = add(foo[j][k + 1], f[j][k]);
                    else if (j + 1 < N) foo[j + 1][k + 1] = add(foo[j + 1][k + 1], f[j][k]);
                }
            }
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    f[j][k] = foo[j][k];
                }
            }
        }
        if (s[i] == 'D') {
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    if (!f[j][k]) continue;
                    foo[j][k] = add(foo[j][k], f[j][k]);
                    if (k > 1) foo[j][k - 1] = add(foo[j][k - 1], f[j][k]);
                    else if (j + 1 < N) foo[j + 1][1] = add(foo[j + 1][1], f[j][k]);
                }
            }
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    f[j][k] = foo[j][k];
                }
            }
        }
        if (s[i] == 'L') {
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    if (!g[j][k]) continue;
                    foo[j][k] = add(foo[j][k], g[j][k]);
                    if (k < j) foo[j][k + 1] = add(foo[j][k + 1], g[j][k]);
                    else if (j + 1 < N) foo[j + 1][k + 1] = add(foo[j + 1][k + 1], g[j][k]);
                }
            }
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    g[j][k] = foo[j][k];
                }
            }
        }
        if (s[i] == 'R') {
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    if (!g[j][k]) continue;
                    foo[j][k] = add(foo[j][k], g[j][k]);
                    if (k > 1) foo[j][k - 1] = add(foo[j][k - 1], g[j][k]);
                    else if (j + 1 < N) foo[j + 1][1] = add(foo[j + 1][1], g[j][k]);
                }
            }
            for (int j = 1; j < N; j++) {
                for (int k = 1; k <= j; k++) {
                    g[j][k] = foo[j][k];
                }
            }
        }
    }
    for (int j = 1; j < N; j++) {
        for (int k = 1; k <= j; k++) {
            ff[j] = add(ff[j], f[j][k]);
            gg[j] = add(gg[j], g[j][k]);
        }
    }
    int res = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            int now = mul(ff[i], gg[j]);
            now = mul(now, i);
            now = mul(now, j);
            res = add(res, now);
        }
    }
    cout << res << endl;
    return 0;
}