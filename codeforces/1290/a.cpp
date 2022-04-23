#include <bits/stdc++.h>

using namespace std;

const int N = 3500;

int n, m, k;
int dp[N][N], a[N];

int go(int id, int l, int r) {
    if (dp[l][r] >= 0) return dp[l][r];
    if (id == m) return dp[l][r] = max(a[l], a[r]);
    int& res = dp[l][r];
    if (id < m - k) {
        res = min(go(id + 1, l + 1, r), go(id + 1, l, r + 1));
    } else {
        res = max(go(id + 1, l + 1, r), go(id + 1, l, r + 1));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        memset(dp, -1, sizeof dp);
        cout << go(1, 1, n) << '\n';
    }
    return 0;
}