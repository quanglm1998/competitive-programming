#include <bits/stdc++.h>

using namespace std;

const int N = 300010;

int n, m;
vector<int> adj[N];
vector<int> revAdj[N];
int l[N], r[N];
int res[N];
int deg[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        revAdj[v].push_back(u);
        deg[u]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : revAdj[u]) {
            r[v] = min(r[v], r[u] - 1);
            deg[v]--;
            if (!deg[v]) q.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        deg[i] = revAdj[i].size();
    }
    set<pair<int, int>> s1, s2;
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) s2.insert({l[i], i});
    }
    for (int i = 1; i <= n; i++) {
        while (!s2.empty() && s2.begin()->first <= i) {
            auto u = *s2.begin();
            s2.erase(s2.begin());
            s1.insert({r[u.second], u.second});
        }
        if (s1.empty()) {
            cout << -1 << endl;
            return 0;
        }
        auto u = *s1.begin();
        s1.erase(s1.begin());
        if (u.first < i) {
            cout << -1 << endl;
            return 0;
        }
        res[i] = u.second;
        for (int v : adj[u.second]) {
            deg[v]--;
            if (!deg[v]) s2.insert({l[v], v});
        }
    }
    for (int i = 1; i <= n; i++) cout << res[i] << '\n';
    return 0;
}