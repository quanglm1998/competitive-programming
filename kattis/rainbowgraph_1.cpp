#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const string COLOR = "RBG";
const int INF = 1e9;

int n, m;

struct DSU {
    int root[N];
    int numComp;
    
    void init() {
        fill(root + 1, root + n + 1, 0);
        numComp = n;
    }


    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }

    bool unite(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        numComp--;
        return 1;
    }
} dsu;

struct Edge {
    int u, v, w, c;
};

Edge edges[N];
bool inSet[N];
int res[N];
vector<pair<int, int>> adj[N];
int canAdd[2][N];
int dist[N], pre[N], weightedDist[N];

void buildDSU(int forbidentColor) {
    dsu.init();
    for (int i = 1; i <= m; i++) {
        if (inSet[i] || edges[i].c == forbidentColor) continue;
        dsu.unite(edges[i].u, edges[i].v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    int sum = 0;
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 1; i <= m; i++) {
        char c;
        cin >> edges[i].u >> edges[i].v >> edges[i].w >> c;
        edges[i].c = COLOR.find(c);
        sum += edges[i].w;
    }
    bool isGood = true;
    buildDSU(0);
    isGood &= dsu.numComp == 1;
    buildDSU(1);
    isGood &= dsu.numComp == 1;
    if (!isGood) {
        for (int i = 1; i <= m; i++) {
            cout << -1 << '\n';
        }
        return 0;
    }
    fill(res + 1, res + m + 1, -1);
    res[m] = sum;
    for (int it = m - 1; it > 0; it--) {
        // cout << "IT-----------------------" << it << endl << endl;
        // for (int i = 1; i <= m; i++) {
        //     if (inSet[i]) cout << i << ' ';
        // }
        // cout << endl;
        // init
        fill(canAdd[0] + 1, canAdd[0] + m + 1, 0);
        fill(canAdd[1] + 1, canAdd[1] + m + 1, 0);
        for (int i = 1; i <= m; i++) {
            adj[i].clear();
        }
        // build exchange graph
        for (int i = 1; i <= m; i++) {
            if (inSet[i]) continue;
            inSet[i] = 1;
            buildDSU(0);
            if (dsu.numComp == 1) {
                canAdd[0][i] = 1;
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i) adj[j].push_back({i, -edges[i].w});
                }
            } else if (dsu.numComp == 2) {
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i && edges[j].c != 0) {
                        int u = dsu.getRoot(edges[j].u);
                        int v = dsu.getRoot(edges[j].v);
                        if (u != v) adj[j].push_back({i, -edges[i].w});
                    }
                }
            }
            buildDSU(1);
            if (dsu.numComp == 1) {
                canAdd[1][i] = 1;
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i) adj[i].push_back({j, edges[j].w});
                }
            } else if (dsu.numComp == 2) {
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i && edges[j].c != 1) {
                        int u = dsu.getRoot(edges[j].u);
                        int v = dsu.getRoot(edges[j].v);
                        if (u != v) adj[i].push_back({j, edges[j].w});
                    }
                }
            }
            inSet[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            dist[i] = INF;
            weightedDist[i] = INF;
            pre[i] = -1;
            if (canAdd[0][i]) {
                weightedDist[i] = -edges[i].w;
                dist[i] = 0;
                pre[i] = 0;
            }
        }
        for (int t = 1; t < m; t++) {
            bool found = 0;
            for (int i = 1; i <= m; i++) {
                if (weightedDist[i] >= INF) continue;
                for (auto u : adj[i]) {
                    if (weightedDist[u.first] > weightedDist[i] + u.second) {
                        found = 1;
                        weightedDist[u.first] = weightedDist[i] + u.second;
                        dist[u.first] = dist[i] + 1;
                        pre[u.first] = i;
                    }
                }
            }
            if (!found) break;
        }
        pair<pair<int, int>, int> bestNode({INF, INF}, -1);
        // cout << "DIST" << endl;
        for (int i = 1; i <= m; i++) {
            if (canAdd[1][i]) {
                bestNode = min(bestNode, {{weightedDist[i], dist[i]}, i});
                // cout << i << ' ' << weightedDist[i] << ' ' << dist[i] << endl;
            }
        }
        // cout << "BEST " << bestNode.first.first << ' ' << bestNode.first.second << endl;
        // for (int i = 1; i <= m; i++) {
        //     if (canAdd[1][i]) {
        //         if (i != bestNode.second && weightedDist[i] == bestNode.first.first) {
        //             cout << "FOUND " << i << ' ' << weightedDist[i] << ' ' << dist[i] << endl;
        //         }
        //     }
        // }
        if (bestNode.second == -1) break;
        sum += bestNode.first.first;
        res[it] = sum;
        int curNode = bestNode.second;
        set<int> has;
        // cout << "ADJ 8" << endl;
        // for (auto u : adj[8]) cout << u.first << ' ' << u.second << endl;
        // cout << "ADJ 11" << endl;
        // for (auto u : adj[11]) cout << u.first << ' ' << u.second << endl;
        while (curNode) {
            // cout << curNode << endl;
            assert(curNode != -1);
            assert(!has.count(curNode));
            has.insert(curNode);
            inSet[curNode] ^= 1;
            curNode = pre[curNode];
        }
    }
    for (int i = 1; i <= m; i++) cout << res[i] << '\n';
    return 0;
}
