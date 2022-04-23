#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.push_back({u, v, c});
    }
    for (int i = 1; i <= n; i++) {
        edges.push_back({0, i, 0});
    }
    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    vector<int> last(n + 1, -1);
    dist[0] = 0;
    for (int it = 0; it < n; it++) {
        for (auto edge : edges) {
            int u, v, c;
            tie(u, v, c) = edge;
            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                last[v] = u;
            }
        }
    }

    for (auto edge : edges) {
        int u, v, c;
        tie(u, v, c) = edge;
        if (dist[v] > dist[u] + c) {
            cout << "YES\n";
            vector<int> used(n + 1, - 1);
            vector<int> res;
            while (used[v] == -1) {
                used[v] = res.size();
                res.push_back(v);
                v = last[v];
            }
            res = vector<int>(res.begin() + used[v], res.end());
            reverse(res.begin(), res.end());
            cout << v;
            for (int u : res) cout << ' ' << u;
                cout << '\n';
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}