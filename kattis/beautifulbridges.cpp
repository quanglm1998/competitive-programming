#include <bits/stdc++.h>

using namespace std;

const long long INF = 2e18;
const int N = 10010;

int n, h, aa, bb;
int x[N], y[N];
int l[N], r[N];
long long dp[N];

bool check(int u, int k, int v) {
    long long r = (x[v] - x[u]) / 2;
    long long delta1 = h - r;
    long long delta2 = (x[u] + x[v]) / 2;
    if (delta1 >= y[k]) return 0;
    return r * r - (delta2 - x[k]) * (delta2 - x[k]) < 1ll * (y[k] - delta1) * (y[k] - delta1); 
}

bool checkLeft(int u, int k, int v) {
    if (x[k] >= (x[u] + x[v]) / 2) return 0;
    return check(u, k, v);
}

bool checkRight(int u, int k, int v) {
    if (x[k] <= (x[u] + x[v]) / 2) return 0;
    return check(u, k, v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> h >> aa >> bb;
    h *= 2;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        y[i] *= 2;
        x[i] *= 2;
    }
    for (int i = 1; i <= n; i++) {
        l[i] = r[i] = i;
        for (int j = 1; j <= i; j++) {
            while (r[j] && checkLeft(r[j], j, i)) r[j]--;
            while (l[j] && !checkRight(l[j], j, i)) l[j]--;
        }
        int curL = l[i], curR = r[i];
        dp[i] = INF;
        for (int j = i - 1; j > 0; j--) {
            curL = max(curL, l[j]);
            curR = min(curR, r[j]);
            if (curL < j && j <= curR) {
                dp[i] = min(dp[i], dp[j] + 1ll * bb * (x[i] - x[j]) * (x[i] - x[j]));
            }
        }
        if (i == 1) dp[i] = 0;
        if (dp[i] < INF) dp[i] += 2ll * aa * (h - y[i]);
    }
    if (dp[n] >= INF) cout << "impossible" << endl;
    else cout << dp[n] / 4 << endl;
    return 0;
}