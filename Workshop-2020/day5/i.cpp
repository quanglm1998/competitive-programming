#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, k, t;
int a[N];
long long sum[N];
long long dp[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }   
    deque<int> x, y;
    x.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (!x.empty() && sum[i] - sum[x.front()] > t) x.pop_front();
        while (!y.empty() && sum[i] - sum[y.front()] > t) y.pop_front();
        dp[i] = 1e18;
        if (!x.empty()) dp[i] = min(dp[i], sum[i] + dp[x.front()] - sum[x.front()]);
        if (!y.empty()) dp[i] = min(dp[i], dp[y.front()]);

        while (!x.empty() && dp[x.back()] - sum[x.back()] >= dp[i] - sum[i]) x.pop_back();
        x.push_back(i);
        if (i - k >= 0) {
            while (!y.empty() && dp[y.back()] >= dp[i - k]) y.pop_back();
            y.push_back(i - k);
        }
    }
    long long res = 1e18;
    for (int i = 0; i <= n; i++) {
        if (sum[n] - sum[i] <= t) {
            res = min(res, dp[i]);
        }
    }
    cout << res << '\n';
    return 0;
}