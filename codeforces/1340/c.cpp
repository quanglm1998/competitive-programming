#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 10010;
const int M = 2010;
const long long INF = 1e18;
 
int n, m;
int d[N];
int g, r;
int period;
long long dp[N][M];
bool used[N][M];
 
int encode(int u, int v) {
    return u * period + v;
}
 
pair<int, int> decode(int u) {
    return {u / period, u % period};
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> d[i];
    }
    cin >> g >> r;
    period = g + r;
    
    sort(d + 1, d + m + 1);
    m = unique(d + 1, d + m + 1) - d - 1;
 
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < period; j++) {
            dp[i][j] = INF;
        }
    }

    dp[1][0] = 0;
    priority_queue<pair<long long, int>> s;
    s.push({0ll, encode(1, 0)});
    
    while (!s.empty()) {
        int u, t;
        tie(u, t) = decode(s.top().second);
        s.pop();
 
        if (u == m) {
            cout << dp[u][t] << endl;
            return 0;
        }
 
        if (used[u][t]) continue;
        used[u][t] = 1;
 
        if (t < g) {
            if (u > 1) {
                int newT = t + d[u] - d[u - 1];
                if (newT <= g) {
                    if (dp[u - 1][newT] > dp[u][t] + d[u] - d[u - 1]) {
                        dp[u - 1][newT] = dp[u][t] + d[u] - d[u - 1];
                        s.push({-dp[u - 1][newT], encode(u - 1, newT)});
                    }
                }
            }
            if (u < m) {
                int newT = t + d[u + 1] - d[u];
                if (newT <= g) {
                    if (dp[u + 1][newT] > dp[u][t] + d[u + 1] - d[u]) {
                        dp[u + 1][newT] = dp[u][t] + d[u + 1] - d[u];
                        s.push({-dp[u + 1][newT], encode(u + 1, newT)});
                    }
                }
            }
        } else {
            if (dp[u][0] > dp[u][t] + r) {
                dp[u][0] = dp[u][t] + r;
                s.push({-dp[u][0], encode(u, 0)});
            }
        }
    }
    cout << -1 << endl;
    return 0;       
}