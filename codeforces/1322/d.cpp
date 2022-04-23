#include <bits/stdc++.h>

using namespace std;

const int N = 2020;
const int LOG = 12;
const int INF = 1e9;

int n, m;
int l[N], s[N];
int c[N + N];
int f[N + N][1 << LOG];
int g[1 << LOG];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    for (int i = 1; i <= m + n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= m + n; i++) {
        for (int j = 1; j < (1 << LOG); j++) f[i][j] = -INF;
        f[i][0] = 0;
    }
    int res = 0;
    int mask = (1 << LOG) - 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << LOG); j++) g[j] = -INF;
        for (int j = 0; j < (1 << LOG); j++) {
            int newRev = f[l[i]][j] - s[i] + c[l[i]];
            for (int k = 0; k < LOG; k++) {
                if ((j >> k & 1) == 0) break;
                newRev += c[l[i] + k + 1];
            }
            g[(j + 1) & mask] = max(g[(j + 1) & mask], newRev);
        }
        for (int j = 0; j < (1 << LOG); j++) {
            f[l[i]][j] = max(f[l[i]][j], g[j]);
            res = max(res, f[l[i]][j]);
        }
        int cur = 1;
        for (int ii = l[i]; ii > 0; ii--) {
            for (int j = 0; j < (1 << LOG); j += cur) {
                f[ii - 1][(j << 1) & mask] = max(f[ii - 1][(j << 1) & mask], f[ii][j]);
            }
            cur = min(1 << LOG, cur * 2);
        }
    }
    cout << res << '\n';
    return 0;
}