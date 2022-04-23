#include <bits/stdc++.h>

using namespace std;

const int N = 800010;

int n;
int used[N];
int isFixed[N];
int dp[N];
vector<pair<int, int>> adj[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        adj[r + 1].push_back({l, -1});
        adj[l].push_back({r + 1, 1});
    }
    memset(dp, 0x3f, sizeof dp);
    dp[4 * n - 1] = 0;
    set<pair<int, int>> s;
    s.insert({0, -(4 * n - 1)});
    while (!s.empty()) {
        int u = -s.begin()->second;
        s.erase(s.begin());
        if (used[u]) continue;
        used[u] = 1;
        cout << u << ' ' << dp[u] << endl;
        for (auto [v, w] : adj[u]) {
            if (dp[v] < dp[u] + w) {
                cout << -1 << endl;
                return 0;
            }
            if ((isFixed[v] || used[v]) && dp[v] > dp[u] + w) {
                cout << "#1" << endl;
                cout << -1 << endl;
                return 0;
            }
            if (dp[v] > dp[u] + w) {
                dp[v] = dp[u] + w;
                isFixed[v] = 1;
                s.insert({dp[v], -v});
            }
        } 
        if (u > 0) {
            if ((isFixed[u - 1] || used[u - 1]) && dp[u - 1] > dp[u]) {
                cout << "#2" << endl;
                cout << -1 << endl;
                return 0;
            }
            if (dp[u - 1] > dp[u]) {
                dp[u - 1] = dp[u];
                s.insert({dp[u - 1], -u + 1});
            }
        }
        if (u < 4 * n - 1) {
            if ((isFixed[u + 1] || used[u + 1]) && dp[u + 1] > dp[u] + 1) {
                cout << "#3" << endl;
                cout << -1 << endl;
                return 0;
            }
            if (dp[u + 1] > dp[u] + 1) {
                dp[u + 1] = dp[u] + 1;
                s.insert({dp[u + 1], -u - 1});
            }
        }
    }
    vector<int> res;
    for (int i = 0; i < 4 * n - 1; i++) {
        if (dp[i] < dp[i + 1]) {
            res.push_back(i);
        }
    }
    cout << res.size() << '\n';
    for (auto u : res) cout << u << ' ';
        cout << '\n';
    return 0;
}