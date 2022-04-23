#include <bits/stdc++.h>

using namespace std;

const int N = 200;
const int INF = 1e9;

char s[N], t[N];
int n, m;
pair<int, int> dp[N][N][N], g[N][N][N];

struct Trace {
    int u, v, w;
    int equalS, equalT;
};

Trace trace[N][N][N];

void update(pair<int, int> &dp, pair<int, int> cur, Trace &trace, Trace &curTrace) {
    if (cur < dp) {
        dp = cur;
        trace = curTrace;
    }
}

void go(int u, int v, int w) {
    // cout << u << ' ' << v << ' ' << w << endl;
    if (u == 0) return;
    int uu, vv, ww;
    int ss, tt;
    uu = trace[u][v][w].u;
    vv = trace[u][v][w].v;
    ww = trace[u][v][w].w;
    ss = trace[u][v][w].equalS;
    tt = trace[u][v][w].equalT;
    go(uu, vv, ww);
    if (ss) cout << s[v];
    else cout << t[w];
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> (s + 1);
    cin >> (t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);

    for (int i = 0; i <= n + m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= m; k++) {
                dp[i][j][k] = {INF, INF};
                trace[i][j][k] = {-1, -1, -1};
            }
        }
    }
    dp[0][0][0] = {0, 0};

    for (int i = 0; i <= n + m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= m; k++) {

                for (int ii = i - 1; ii <= i; ii++) {
                    for (int jj = j - 1; jj <= j; jj++) {
                        for (int kk = k - 1; kk <= k; kk++) {
                            if (ii >= 0 && jj >= 0 && kk >= 0 && (ii < i || jj < j || kk < k)) {
                                pair<int, int> cur = dp[ii][jj][kk];
                                Trace curTrace = {ii, jj, kk, 0, 0};
                                update(dp[i][j][k], {cur.first + 2, cur.second}, trace[i][j][k], curTrace);

                                if (ii == i - 1) {
                                    if (jj == j - 1) {
                                        if (kk == k - 1) {
                                            if (s[j] == t[k]) {
                                                Trace curTrace = {ii, jj, kk, 1, 1};
                                                update(dp[i][j][k], {cur.first, cur.second}, trace[i][j][k], curTrace);
                                            } else {
                                                Trace curTrace = {ii, jj, kk, 1, 0};
                                                update(dp[i][j][k], {cur.first + 1, cur.second + 1}, trace[i][j][k], curTrace);
                                                
                                                if (cur.second > 0) {
                                                    Trace curTrace = {ii, jj, kk, 0, 1};
                                                    update(dp[i][j][k], {cur.first + 1, cur.second - 1}, trace[i][j][k], curTrace);    
                                                }
                                            }
                                        } else {
                                            Trace curTrace = {ii, jj, kk, 1, 0};
                                            update(dp[i][j][k], {cur.first + 1, cur.second + 1}, trace[i][j][k], curTrace);
                                        }
                                    } else {
                                        if (kk == k - 1 && cur.second > 0) {
                                            Trace curTrace = {ii, jj, kk, 0, 1};
                                            update(dp[i][j][k], {cur.first + 1, cur.second - 1}, trace[i][j][k], curTrace);
                                        } else {
                                            // pass
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }


    pair<int, int> now(INF, INF);
    int res = -1;
    for (int i = 0; i <= n + m; i++) {
        if (res == -1 || now > dp[i][n][m]) {
            res = i;
            now = dp[i][n][m];
        }
    }
    cout << now.first << ' ' << now.second << endl;
    go(res, n, m);
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}