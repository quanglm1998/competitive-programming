#include <bits/stdc++.h>

using namespace std;

const int N = 88;
const int M = 200010;
const int INF = 2e9;

int n, m;
int dp[M];
pair<int, int> a[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a + 1, a + n + 1);
    vector<pair<int, int>> stMin;
    stMin.push_back({0, 0});
    int res = INF;
    for (int i = 1; i <= m * 2; i++) {
        dp[i] = INF;
        for (int j = 1; j <= n && a[j].first <= i; j++) {
            int last = a[j].first * 2 - i - 1;
            last = min(last, a[j].first - a[j].second - 1);
            int cost = max(0, (i - last) / 2 - a[j].second);
            int id = lower_bound(stMin.begin(), stMin.end(), make_pair(last, -1)) - stMin.begin();
            dp[i] = min(dp[i], stMin[id].second + cost);
        }
        while (!stMin.empty() && stMin.back().second >= dp[i]) stMin.pop_back();
        stMin.push_back({i, dp[i]});
        if (i >= m) res = min(res, dp[i]);
    }
    cout << res << endl;
    return 0;
}