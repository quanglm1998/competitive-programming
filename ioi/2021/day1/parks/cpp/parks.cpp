#include <bits/stdc++.h>
#include "parks.h"

using namespace std;

/*
    U = max capacity
    Complexity: O(V^2 * E)
    O(min(E^{1/2}, V^{2/3}) * E) if U = 1
    O(V^{1/2} * E)$ for bipartite matching.
*/
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
        for (int &i = cur[u]; i < adj[u].size(); i++) {
            int edgeId = adj[u][i];
            int v = to[edgeId];
            if (d[v] == d[u] + 1 && f[edgeId] < c[edgeId]) {
                flow_t foo = dfs(v, min(res, c[edgeId] - f[edgeId]));
                if (foo) {
                    f[edgeId] += foo;
                    f[edgeId ^ 1] -= foo;
                    return foo;
                }
            }
        }
        return 0;
    }
 
    flow_t maxFlow() {
        flow_t res = 0;
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            while (flow_t aug = dfs(s, INF)) res += aug;
        }
        return res;
    }
};

struct DSU {
  int numComp;
  vector<int> root;
  vector<int> sz;

  DSU(int n = 0) : numComp(n), root(n, -1), sz(n, 1) {}

  int GetRoot(int u) {
    return root[u] != -1 ? root[u] = GetRoot(root[u]) : u;
  }

  bool Unite(int u, int v) {
    u = GetRoot(u); v = GetRoot(v);
    if (u == v) return 0;
    sz[v] += sz[u];
    root[u] = v;
    numComp--;
    return 1;
  }
};

struct Point {
    int x, y, id;
};

map<pair<int, int>, int> pos_to_id;

const int X[] = {0, 0, 1, -1, 0, 0};
const int Y[] = {1, -1, 0, 0, 1, -1};

int Solve(std::vector<int> x, std::vector<int> y, vector<Point> a, int base) {
    int n = x.size();
    DSU dsu(n);
    
    vector<pair<int, int>> edges;
    vector<pair<int, int>> benches;

    map<pair<int, int>, int> bench_to_id;
    vector<pair<int, int>> connections;

    auto GenBenches = [&](int u, int v) {
        vector<pair<int, int>> res;
        if (x[u] == x[v]) {
            res.push_back({x[u] - 1, (y[u] + y[v]) / 2});
            res.push_back({x[u] + 1, (y[u] + y[v]) / 2});
        } else {
            res.push_back({(x[u] + x[v]) / 2, y[u] - 1});
            res.push_back({(x[u] + x[v]) / 2, y[u] + 1});
        }
        return res;
    };

    for (int i = 0; i < n; i++) {
        auto [x, y, id] = a[i];
        for (int dir = base; dir < base + 4; dir++) {
            auto xx = x + X[dir] * 2;
            auto yy = y + Y[dir] * 2;
            if (!pos_to_id.count({xx, yy})) continue;
            auto id2 = pos_to_id[{xx, yy}];
            if (!dsu.Unite(id, id2)) continue;
            auto now = GenBenches(id, id2);
            for (auto val : now) {
                if (!bench_to_id.count(val)) {
                    bench_to_id[val] = benches.size();
                    benches.push_back(val);
                }
                connections.push_back({edges.size(), bench_to_id[val]});
            }   
            edges.push_back({id, id2});
        }
    }

    if (dsu.numComp > 1) return 0;

    int tot = edges.size() + benches.size();

    DinicFlow f(2 + tot, tot, tot + 1);

    vector<int> edges_in_flow(connections.size(), 0);

    for (int i = 0; i < connections.size(); i++) {
        auto [u, v] = connections[i];
        edges_in_flow[i] = f.addEdge(u, edges.size() + v, 1);
    }
    for (int i = 0; i < edges.size(); i++) {
        f.addEdge(f.s, i, 1);
    }
    for (int i = 0; i < benches.size(); i++) {
        f.addEdge(edges.size() + i, f.t, 1);
    }
    int max_flow = f.maxFlow();
    if (max_flow < edges.size()) {
        return 0;
    }


    vector<int> res;
    for (int i = 0; i < connections.size(); i++) {
        if (f.f[edges_in_flow[i]] == 1) {
            res.push_back(i);
        }
    }

    {
        vector<int> u, v, a, b;
        for (auto id : res) {
            auto [edge_id, bench_id] = connections[id];
            u.push_back(edges[edge_id].first);
            v.push_back(edges[edge_id].second);
            a.push_back(benches[bench_id].first);
            b.push_back(benches[bench_id].second);
        }
        build(u, v, a, b);
    }
    return 1;
}

int construct_roads(std::vector<int> x, std::vector<int> y) {
    int n = x.size();
    vector<Point> a;
    for (int i = 0; i < n; i++) {
        a.push_back({x[i], y[i], i});
        pos_to_id[{x[i], y[i]}] = i;
    }
    sort(a.begin(), a.end(), [](Point u, Point v) {
        if (u.x != v.x) return u.x < v.x;
        return u.y < v.y;
    });

    if (Solve(x, y, a, 0)) return 1;
    if (Solve(x, y, a, 2)) return 1;

    sort(a.begin(), a.end(), [](Point u, Point v) {
        if (u.y != v.y) return u.y < v.y;
        return u.x < v.x;
    });

    if (Solve(x, y, a, 0)) return 1;
    if (Solve(x, y, a, 2)) return 1;

    return 0;
}
