#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, k;
int dp[N];
vector<pair<int, int>> trace[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
        trace[i].push_back({0, 0});
    }
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        if (u == 1) {
            dp[0]++;
            trace[0].push_back({1, i});
        } else {
            if (dp[u - 2] == dp[u - 1]) {
                trace[u - 1].push_back({0, (int)trace[u - 2].size() - 1});
            } else {
                dp[u - 1]++;
                trace[u - 1].push_back({1, i});
            }
        }
    }
    int cur = k - 1;
    int id = trace[k - 1].size() - 1;
    vector<int> ans;
    while (cur >= 0) {
        while (trace[cur][id].first == 1) {
            ans.push_back(trace[cur][id].second);
            id--;
        }
        id = trace[cur][id].second;
        cur--;
    }
    reverse(ans.begin(), ans.end());
    cout << dp[k - 1] << '\n';
    for (auto u : ans) cout << u << ' ';
        cout << '\n';
    return 0;
}