#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
    }   
    vector<int> cnt(n + 1, 0);
    multiset<pair<long long, int>> s;
    s.insert({0, 1});
    while (!s.empty()) {
        int u;
        long long dist;
        tie(dist, u) = *s.begin();
        s.erase(s.begin());
        if (cnt[u] >= k) continue;
        // cout << "dist " << u << ' ' << dist << endl;
        if (u == n) cout << dist << ' ';
        cnt[u]++;
        // if (u == n) continue;
        for (auto edge : adj[u]) {
            int v, c;
            tie(v, c) = edge;
            if (cnt[v] < k) {
                s.insert({dist + c, v});
            }
        }
    }
    cout << '\n';
    return 0;
}