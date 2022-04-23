#include <bits/stdc++.h>

using namespace std;

const int N = 310;
const long long INF = 1e18;

int n, k;
int h[N];
long long dp[N][N][N];
vector<int> vals;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    vals.push_back(0);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        vals.push_back(h[i]);
    }
    sort(vals.begin(), vals.end()); vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 1; i <= n; i++) h[i] = lower_bound(vals.begin(), vals.end(), h[i]) - vals.begin();
    for (int i = 0; i <= n; i++) for (int j = 0; j <= k; j++) for (int x = 0; x < vals.size(); x++) dp[i][j][x] = INF;
    dp[0][0][0] = 0;
    long long res = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int x = 0; x < vals.size(); x++) {
                // not use
                dp[i][j][h[i]] = min(dp[i][j][h[i]], dp[i - 1][j][x] + max(0, vals[h[i]] - vals[x]));
                // use
                if (j < k) {
                    dp[i][j + 1][x] = min(dp[i][j + 1][x], dp[i - 1][j][x]);
                    dp[i][j + 1][0] = min(dp[i][j + 1][0], dp[i - 1][j][x]);
                }
            }
        }
    }
    for (int j = 0; j <= k; j++) {
        for (int x = 0; x < vals.size(); x++) {
            res = min(res, dp[n][j][x]);
        }
    }
    cout << res << endl;
    return 0;
}