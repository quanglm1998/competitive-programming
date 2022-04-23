#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 250010;
const long long INF = 1e18;

vector<pair<long long, int>> maxVal[N];
vector<int> changedLs;
bool hasChanged[N];
long long res[N];

struct CentroidTree {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<bool> isDead;
    vector<int> sz;
    vector<long long> dist;
    vector<pair<int, long long>> distToCentroid[N];

    CentroidTree(int n = 0) : n(n) {
        adj.assign(n + 1, vector<pair<int, int>>());
        isDead.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        dist.assign(n + 1, 0ll);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int findRoot(int u, int p, int centroidSz) {
        sz[u] = 1;
        bool f = 1;
        for (auto e : adj[u]) {
            int v = e.first;
            int w = e.second;
            if (v == p || isDead[v]) continue;
            int now = findRoot(v, u, centroidSz);
            if (now) return now;
            sz[u] += sz[v];
            f &= sz[v] * 2 <= centroidSz;
        }
        f &= (centroidSz - sz[u]) * 2 <= centroidSz;
        return f ? u : 0;
    }

    void initRegion(int u, int p, int centroid, vector<int> &ls) {
        ls.push_back(u);
        sz[u] = 1;
        distToCentroid[u].push_back({centroid, dist[u]});
        for (auto e : adj[u]) {
            int v = e.first;
            int w = e.second;
            if (v == p || isDead[v]) continue;
            dist[v] = dist[u] + w;
            initRegion(v, u, centroid, ls);
            sz[u] += sz[v];
        }
    }

    void solve(int centroid, int centroidSz, const CentroidTree* t) {
        centroid = findRoot(centroid, 0, centroidSz);
        dist[centroid] = 0;
        vector<int> ls;
        initRegion(centroid, 0, centroid, ls);
        // cout << "centroid " << centroid << endl;
        // for (int u : ls) {
        //     cout << "d " << u << ' ' << dist[u] << endl;
        // }

        if (t) {
            for (int u : ls) {
                // if (centroid == 2) cout << u << endl;
                for (auto val : t->distToCentroid[u]) {
                    int x = val.first;
                    long long totDist = dist[u] + val.second;
                    if (!hasChanged[x]) {
                        hasChanged[x] = 1;
                        changedLs.push_back(x);
                    }
                    maxVal[x].insert(lower_bound(maxVal[x].begin(), maxVal[x].end(), make_pair(totDist, u)), make_pair(totDist, u));
                    assert(is_sorted(maxVal[x].begin(), maxVal[x].end()));
                    if (maxVal[x].size() >= 3) maxVal[x].pop_back();
                }
            }
            for (int u : ls) {
                for (auto val : t->distToCentroid[u]) {
                    int x = val.first;
                    long long totDist = dist[u] + val.second;
                    assert(!maxVal[x].empty());
                    if (maxVal[x][0].second != u) {
                        res[u] = min(res[u], totDist + maxVal[x][0].first);
                    } else if (maxVal[x].size() == 2) {
                        res[u] = min(res[u], totDist + maxVal[x][1].first);
                    }
                }
            }
            for (int u : changedLs) {
                maxVal[u].clear();
                hasChanged[u] = 0;
            }
            changedLs.clear();
        }

        isDead[centroid] = 1;
        for (auto e : adj[centroid]) {
            int v = e.first;
            int w = e.second;
            if (isDead[v]) continue;
            solve(v, sz[v], t);
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    fill(res + 1, res + n + 1, INF);
    CentroidTree t1(n), t2(n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t1.addEdge(u, v, w);
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t2.addEdge(u, v, w);
    }
    t1.solve(1, n, NULL);
    // cout << "-------------------------\n";
    t2.solve(1, n, &t1);
    for (int i = 1; i <= n; i++) {
        cout << res[i] << '\n';
    }
//     for (int i = 1; i <= n; i++) {
//         cout << "# " << i << endl;
//         for (auto val : t1.distToCentroid[i]) cout << val.first << ' ' << val.second << endl;
//     }
//     cout << "-------------------------\n";

// for (int i = 1; i <= n; i++) {
//         cout << "# " << i << endl;
//         for (auto val : t1.distToCentroid[i]) cout << val.first << ' ' << val.second << endl;
//     }
    return 0;
}