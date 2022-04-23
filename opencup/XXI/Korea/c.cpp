#include <bits/stdc++.h>

using namespace std;

const int N = 18;

int n;
int a[N][N];
int tot = 0;
int f[1 << N][N][N][2];
int g[1 << N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i][j] == -1) continue;
            int val = min(a[i][j], a[j][i]);
            tot += val;
            a[i][j] -= val;
            a[j][i] -= val;
        }
    }
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    g[1] = 0;

    auto update = [&](int &u, int v) {
        if (u == -1 || u > v) u = v;
    };

    for (int mask = 1; mask < 1 << n; mask++) {
        for (int u = 0; u < n; u++) if (mask >> u & 1) {
            for (int v = 0; v < n; v++) if (mask >> v & 1) {
                for (int flag = 0; flag < 2; flag++) {
                    if (f[mask][u][v][flag] == -1) continue;
                    for (int w = 0; w < n; w++) {
                        if (a[u][w] == -1) continue;
                        if (w == v && flag) {
                            update(g[mask], f[mask][u][v][flag] + a[u][w]);
                        }
                        if (mask >> w & 1) continue;
                        update(f[mask | 1 << w][w][v][1], f[mask][u][v][flag] + a[u][w]);
                    }
                }
            }
        }

        if (g[mask] == -1) continue;
        for (int u = 0; u < n; u++) if (mask >> u & 1) {
            for (int v = 0; v < n; v++) if (mask >> v & 1) {
                for (int w = 0; w < n; w++) if (!(mask >> w & 1)) {
                    if (a[u][w] == -1) continue;
                    update(f[mask | 1 << w][w][v][0], g[mask] + a[u][w]);
                }
            }
        }
    }

    if (g[(1 << n) - 1] == -1) cout << -1 << '\n';
    else cout << g[(1 << n) - 1] + tot << '\n';
    return 0;
}