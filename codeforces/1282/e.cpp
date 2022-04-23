#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
vector<int> a[N];
set<int> triaLs[N];
set<pair<int, int>> s;
set<int> adj[N];
int deg[N];
int used[N];
vector<int> res;

void addDeg(int u, int v) {
    s.erase({deg[u], u});
    deg[u]++;
    triaLs[u].insert(v);   
    s.insert({deg[u], u});
}

void delDeg(int v) {
    for (int u : a[v]) {
        s.erase({deg[u], u});
        deg[u]--;
        if (deg[u]) s.insert({deg[u], u});
        triaLs[u].erase(v);
    }
}

void go() {
    if (s.size() == 3) {
        vector<int> ls;
        for (auto u : s) ls.push_back(u.second);
        res.push_back(*triaLs[ls[0]].begin());
        adj[ls[0]].insert(ls[1]);
        adj[ls[0]].insert(ls[2]);

        adj[ls[1]].insert(ls[0]);
        adj[ls[1]].insert(ls[2]);

        adj[ls[2]].insert(ls[0]);
        adj[ls[2]].insert(ls[1]);
        return;
    }
    int u = s.begin()->second;
    int v = *triaLs[u].begin();
    s.erase(s.begin());
    res.push_back(v);
    delDeg(v);
    go();
    sort(a[v].begin(), a[v].end(), [&](int u, int v) {
        return adj[u].size() < adj[v].size();
    });
    adj[a[v][0]].insert(a[v][1]);
    adj[a[v][0]].insert(a[v][2]);
    adj[a[v][1]].insert(a[v][0]);
    adj[a[v][2]].insert(a[v][0]);

    adj[a[v][1]].erase(a[v][2]);
    adj[a[v][2]].erase(a[v][1]);
}

void dfs(int u) {
    used[u] = 1;
    cout << u << ' ';
    for (auto v : adj[u]) {
        if (!used[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        res.clear();
        for (int i = 1; i <= n; i++) {
            triaLs[i].clear();
            adj[i].clear();
            deg[i] = 0;
            used[i] = 0;
        }
        s.clear();
        for (int i = 1; i <= n; i++) {
            s.insert({0, i});
        }
        for (int i = 1; i <= n - 2; i++) {
            a[i].assign(3, 0);
            for (int &u : a[i]) {
                cin >> u;
                addDeg(u, i);
            }
        }
        go();
        dfs(1);
        cout << '\n';
        for (int u : res) cout << u << ' ';
            cout << '\n';
    }
    return 0;
}