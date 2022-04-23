#include <bits/stdc++.h>

using namespace std;

template <typename flow_t = int>
struct DinicFlow {
    const flow_t INF = numeric_limits<flow_t>::max() / 2; // 1e9
 
    int n, s, t;
    vector<vector<int>> adj;
    vector<int> d, cur;
    vector<int> to;
    vector<flow_t> c, f;
 
    DinicFlow(int n, int s, int t) : n(n), s(s), t(t), adj(n, vector<int>()), d(n, -1), cur(n, 0) {}
 
    int addEdge(int u, int v, flow_t _c) {
        adj[u].push_back(to.size()); 
        to.push_back(v); f.push_back(0); c.push_back(_c);
        adj[v].push_back(to.size());
        to.push_back(u); f.push_back(0); c.push_back(0);
        return (int)to.size() - 2;
    }
 
    bool bfs() {
        fill(d.begin(), d.end(), -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto edgeId : adj[u]) {
                int v = to[edgeId];
                if (d[v] == -1 && f[edgeId] < c[edgeId]) {
                    d[v] = d[u] + 1;
                    if (v == t) return 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
 
    flow_t dfs(int u, flow_t res) {
        if (u == t || !res) return res;
        flow_t flow = 0;
        for (int &i = cur[u]; i < adj[u].size(); i++) {
            int edgeId = adj[u][i];
            int v = to[edgeId];
            if (d[v] == d[u] + 1 && f[edgeId] < c[edgeId]) {
                flow_t foo = dfs(v, min(res, c[edgeId] - f[edgeId]));
                if (foo) {
                    f[edgeId] += foo;
                    f[edgeId ^ 1] -= foo;

                    res -= foo;
                    flow += foo;
                    // return foo;
                }
            }
        }
        return flow;
    }
 
    flow_t maxFlow(int lim) {
        flow_t res = 0;
        while (res < lim && bfs()) {
            fill(cur.begin(), cur.end(), 0);
            while (flow_t aug = dfs(s, lim - res)) res += aug;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    srand(1);
    cin >> n >> m;
    // n = 2000;
    // m = 4000;
    vector<int> edgeId(n + 1);
    DinicFlow<> f(2 + n + m, 0, 1 + n + m);
    for (int i = 1; i <= n; i++) {
        edgeId[i] = f.addEdge(i + m, f.t, 2);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        // u = rand() % n + 1;
        // v = rand() % n + 1;
        // while (u == v) v = rand() % n + 1;
        if (u == v) {
            cout << "No\n";
            return 0;
        }
        f.addEdge(f.s, i, 1);
        f.addEdge(i, u + m, f.INF);
        f.addEdge(i, v + m, f.INF);
    }
    int flow = f.maxFlow(f.INF);
    for (int i = 1; i <= n; i++) {
        int cur = f.f[edgeId[i]];
        f.s = i + m; f.t = 0;
        flow -= f.maxFlow(cur);
        f.f[edgeId[i]] = f.f[edgeId[i] ^ 1] = f.c[edgeId[i]] = 0;
        f.s = 0; f.t = 1 + n + m;
        flow += f.maxFlow(cur);
        f.c[edgeId[i]] = 2;
        if (flow < m) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}