#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const string COLOR = "RBG";
const int INF = 1e9;

int n, m;

struct Edge {
    int u, v, w, c;
} edges[N];

struct DSU {
    int numComp = 0;
    int root[N];

    void init() {
        numComp = n;
        fill(root + 1, root + n + 1, 0);
    }

    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }

    bool unite(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        numComp--;
        root[u] = v;
        return 1;
    }
} dsu;

bool inSet[N];
int res[N];
vector<int> adj[N];
int canAdd[2][N];
pair<int, int> dist[N];
int pre[N];

void buildDSU(int forbiddenColor) {
    dsu.init();
    for (int i = 1; i <= m; i++) {
        if (edges[i].c != forbiddenColor && !inSet[i]) {
            dsu.unite(edges[i].u, edges[i].v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        char c;
        cin >> edges[i].u >> edges[i].v >> edges[i].w >> c;
        edges[i].c = COLOR.find(c);
        sum += edges[i].w;
    }
    fill(res + 1, res + m + 1, -1);
    bool isConnected = true;
    buildDSU(0);
    isConnected &= dsu.numComp == 1;
    buildDSU(1);
    isConnected &= dsu.numComp == 1;
    if (!isConnected) {
        for (int i = 1; i <= m; i++) {
            cout << res[i] << '\n';
        }
        return 0;
    }
    res[m] = sum;
    for (int it = m - 1; it >= 1; it--) {
        // init
        for (int i = 1; i <= m; i++) {
            adj[i].clear();
            canAdd[0][i] = canAdd[1][i] = 0;
        }

        // build exchange graph and find both entry
        for (int i = 1; i <= m; i++) {
            if (inSet[i]) continue;
            inSet[i] = 1;
            buildDSU(0);
            if (dsu.numComp == 1) {
                canAdd[0][i] = 1;
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i) adj[j].push_back(i);
                }
            } else if (dsu.numComp == 2) {
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i && edges[j].c != 0) {
                        int u = dsu.getRoot(edges[j].u);
                        int v = dsu.getRoot(edges[j].v);
                        if (u != v) adj[j].push_back(i);
                    }
                }
            }
            buildDSU(1);
            if (dsu.numComp == 1) {
                canAdd[1][i] = 1;
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i) adj[i].push_back(j);
                }
            } else if (dsu.numComp == 2) {
                for (int j = 1; j <= m; j++) {
                    if (inSet[j] && j != i && edges[j].c != 1) {
                        int u = dsu.getRoot(edges[j].u);
                        int v = dsu.getRoot(edges[j].v);
                        if (u != v) adj[i].push_back(j);
                    }
                }
            }

            inSet[i] = 0;
        }

        // find path using Bellman-Ford
        fill(dist + 1, dist + m + 1, make_pair(INF, INF));
        fill(pre + 1, pre + m + 1, -1);
        for (int i = 1; i <= m; i++) {
            if (canAdd[0][i]) {
                dist[i] = {-edges[i].w, 0};
                pre[i] = 0;
            }
        }
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 1; i <= m; i++) {
                if (dist[i].first >= INF) continue;
                for (int u : adj[i]) {
                    int costNow = dist[i].first + (inSet[u] ? edges[u].w : -edges[u].w);
                    if (dist[u] > make_pair(costNow, 0)) {
                        changed = true;
                        dist[u] = {costNow, 0};
                        pre[u] = i;
                    }
                }
            }
        }
        int bestNode = -1;
        for (int i = 1; i <= m; i++) {
            if (canAdd[1][i] && dist[i].first < INF) {
                if (bestNode == -1 || dist[bestNode] > dist[i]) {
                    bestNode = i;
                }
            }
        }
        if (bestNode == -1) break;

        // update independent set
        sum += dist[bestNode].first;
        res[it] = sum;
        int curNode = bestNode;
        while (curNode) {
            inSet[curNode] ^= 1;
            curNode = pre[curNode];
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << res[i] << '\n';
    }
    return 0;
}