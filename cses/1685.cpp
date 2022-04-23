#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 200010;
 
int n, m;
vector<int> adj[N];
int low[N], num[N], dead[N], belong[N];
int cntTarjan = 0;
vector<int> st;
vector<int> adjSCC[N];
 
void tarjan(int u) {
    low[u] = num[u] = ++cntTarjan;
    st.push_back(u);
    for (int v : adj[u]) {
        if (dead[v]) continue;
        if (!num[v]) tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        while (1) {
            int v = st.back();
            st.pop_back();
            belong[v] = u;
            dead[v] = 1;
            if (u == v) break;
        }
    }
}
 
int inDeg[N];
bool used[N];
vector<pair<int, int>> res;
 
void dfs(int u, vector<int> &now) {
    if (used[u]) return;
    used[u] = 1;
    if (adjSCC[u].empty()) {
        now.push_back(u);
        return;
    }   
    for (int v : adjSCC[u]) {
        dfs(v, now);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) tarjan(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int v : adj[i]) if (belong[i] != belong[v]) {
            adjSCC[belong[i]].push_back(belong[v]);
        }
    }
    for (int i = 1; i <= n; i++) {
        sort(adjSCC[i].begin(), adjSCC[i].end());
        adjSCC[i].resize(unique(adjSCC[i].begin(), adjSCC[i].end()) - adjSCC[i].begin());
        for (int u : adjSCC[i]) inDeg[u]++;
    }
    vector<int> ls;
    for (int i = 1; i <= n; i++) {
        if (!inDeg[i] && low[i] == num[i]) {
            ls.push_back(i);
        }
    }
    vector<int> x, y;
    for (int u : ls) {
        vector<int> now;
        dfs(u, now);
        while (!x.empty() && !now.empty()) {
            res.push_back({x.back(), now.back()});
            x.pop_back();
            now.pop_back();
        }
        if (!x.empty() && y.size() > 1) {
            res.push_back({u, y.back()});
            y.pop_back();
        } else {
            x.push_back(u);
        }
        for (int v : now) y.push_back(v);
    }
    for (int u : x) for (int v : y) res.push_back({u, v});
    cout << res.size() << '\n';
    for (auto u : res) cout << u.second << ' ' << u.first << '\n';
    return 0;
}