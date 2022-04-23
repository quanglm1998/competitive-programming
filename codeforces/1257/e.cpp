#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n[3];
vector<int> a[3];
vector<pair<int, int>> b;
vector<int> sum, dp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 3; i++) {
        cin >> n[i];
    }
    for (int i = 0; i < 3; i++) {
        a[i].resize(n[i]);
        for (int &u : a[i]) {
            cin >> u;
            if (i > 0) b.push_back({u, i});
        }
        sort(a[i].begin(), a[i].end());
    }
    sort(b.begin(), b.end());
    sum.resize(b.size() + 1);
    dp.resize(b.size() + 1);
    sum[b.size()] = dp[b.size()] = 0;
    for (int i = b.size() - 1; i >= 0; i--) {
        sum[i] = sum[i + 1] + (b[i].second == 1);
        dp[i] = min(dp[i + 1] + (b[i].second == 2), sum[i]);
    }
    int curB = 0;
    int cur[3] = {0, 0, 0};
    int tot = n[0] + n[1] + n[2];
    int res = N;
    for (int i = 0; i <= tot; i++) {
        for (int j = 0; j < 3; j++) {
            while (cur[j] < a[j].size() && a[j][cur[j]] <= i) cur[j]++;
        }
        while (curB < b.size() && b[curB].first <= i) curB++;
        int now = 0;
        now += a[0].size() - cur[0];
        now += cur[1] + cur[2];
        now += dp[curB];
        res = min(res, now);
    }
    cout << res << '\n';
    return 0;
}