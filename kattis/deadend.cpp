#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int n, m;
vector<int> adj[N];
int low[N], num[N], g[N];
int cntGroup, cntTarjan;
vector<int> stTarjan;
vector<int> lsGroup[N];
vector<pair<int, int>> res;
int used[N];
bool notDead[N];

void dfs(int u, int p) {
    num[u] = low[u] = ++cntTarjan;
    stTarjan.push_back(u);
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!low[v]) dfs(v, u);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        cntGroup++;
        lsGroup[cntGroup].clear();
        while (1) {
            int v = stTarjan.back(); stTarjan.pop_back();
            g[v] = cntGroup;
            lsGroup[cntGroup].push_back(v);
            if (u == v) break;
        }
    }
}

bool dfsCalc(int u) {
    used[u] = 1;
    int found = lsGroup[u].size() > 1;
    for (int uu : lsGroup[u]) for (int vv : adj[uu]) {
        int v = g[vv];
        if (used[v]) continue;
        bool now = dfsCalc(v);
        found |= now;
    }
    return notDead[u] = found;
}

void dfsRes(int u) {
    used[u] = 1;
    for (int uu : lsGroup[u]) for (int vv : adj[uu]) {
        int v = g[vv];
        if (used[v]) continue;
        if (!notDead[v]) res.push_back({uu, vv});
        else dfsRes(v);
    }
}

void calc(int u) {
    cntGroup = cntTarjan = 0;
    stTarjan.clear();
    dfs(u, 0);
    int root = -1;
    for (int i = 1; i <= cntGroup; i++) {
        if (lsGroup[i].size() > 1) {
            root = i;
            break;
        }
    }
    if (root == -1) {
        for (int i = 1; i <= cntGroup; i++) {
            int u = lsGroup[i][0];
            if (adj[u].size() == 1) res.push_back({u, adj[u][0]});
        }          
        return;
    }
    fill(used + 1, used + cntGroup + 1, 0);
    fill(notDead + 1, notDead + cntGroup + 1, 0);
    dfsCalc(root);
    fill(used + 1, used + cntGroup + 1, 0);
    dfsRes(root);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (low[i]) continue;
        calc(i);
    }
    sort(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto u : res) cout << u.first << ' ' << u.second << '\n';
    return 0;   
}