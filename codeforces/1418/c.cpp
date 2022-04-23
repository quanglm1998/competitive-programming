#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n + 1, 0);
        for (int i = 1; i <= n; i++) cin >> a[i];
        vector<vector<int>> dp(2, vector<int>(n + 1, 0));
        dp[0][0] = 0;
        dp[1][0] = 1e9;
        for (int i = 1; i <= n; i++) {
            dp[0][i] = dp[1][i - 1];
            if (i > 1) dp[0][i] = min(dp[0][i], dp[1][i - 2]);

            dp[1][i] = dp[0][i - 1] + (a[i] == 1);
            if (i > 1) dp[1][i] = min(dp[1][i], dp[0][i - 2] + (a[i] == 1) + (a[i - 1] == 1));
        }
        cout << min(dp[0][n], dp[1][n]) << endl;
    }
    return 0;
}