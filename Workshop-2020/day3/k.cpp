#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const int M = 5010;

int n, m;

struct Edge {
    int u, v, id;
};

struct DSU {
    int root[N];

    void init() {
        memset(root, 0, sizeof root);
    }

    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }

    bool unite(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        return 1;
    }
} dsu;

Edge e[M];
bool hasColor[N];
bool inSet[M];
bool can[2][M];
vector<int> adj[M];
bool used[M];
int pre[M];
int dist[M];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].id;
    }
    vector<int> s;
    while (1) {
        // init
        memset(hasColor, 0, sizeof hasColor);
        memset(used, 0, sizeof used);
        memset(pre, 0, sizeof pre);
        memset(can, 0, sizeof can);
        memset(dist, 0, sizeof dist);
        for (int i = 1; i <= m; i++) {
            adj[i].clear();
        }

        // build exchange graph
        // color
        for (int u : s) {
            assert(!hasColor[e[u].id]);
            hasColor[e[u].id] = 1;
        }
        for (int i = 1; i <= m; i++) {
            if (inSet[i]) continue;
            if (hasColor[e[i].id]) {
                for (int u : s) {
                    if (e[u].id == e[i].id) adj[i].push_back(u);
                }
            } else {
                can[0][i] = 1;
                for (int u : s) {
                    adj[i].push_back(u);
                }
            }
        }
        // graph
        dsu.init();
        for (int u : s) {
            assert(dsu.unite(e[u].u, e[u].v));
        }
        for (int i = 1; i <= m; i++) {
            if (inSet[i]) continue;
            int x = dsu.getRoot(e[i].u);
            int y = dsu.getRoot(e[i].v);
            if (x != y) {
                can[1][i] = 1;
                for (int u : s) adj[u].push_back(i);
            }
        }

        for (int u : s) {
            dsu.init();
            for (int v : s) {
                if (u == v) continue;
                dsu.unite(e[v].u, e[v].v);
            }
            for (int i = 1; i <= m; i++) {
                if (inSet[i] || can[1][i]) continue;
                int x = dsu.getRoot(e[i].u);
                int y = dsu.getRoot(e[i].v);
                if (x != y) {
                    adj[u].push_back(i);
                }       
            }
        }

        // cout << "#s: ";
        // for (int u : s) cout << u << ' ';
        //     cout << endl;
        // for (int i = 1; i <= m; i++) {
        //     cout << "adj " << i << endl;
        //     for (int u : adj[i]) cout << u << ' ';
        //         cout << endl;
        // }
        // for (int i = 1; i <= m; i++) {
        //     cout << can[0][i] << ' ';
        // }
        // cout << endl;
        // for (int i = 1; i <= m; i++) {
        //     cout << can[1][i] << ' ';
        // }
        // cout << endl;
        

        queue<int> q;
        for (int i = 1; i <= m; i++) {
            if (can[1][i]) {
                used[i] = 1;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (used[v]) continue;
                used[v] = 1;
                pre[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        int pos = -1;
        for (int i = 1; i <= m; i++) {
                // cout << "can " << i << ' ' << used[i] << ' ' << dist[i] << endl;
            if (can[0][i] && used[i]) {
                if (pos == -1 || dist[pos] > dist[i]) pos = i;
                // break;
            }
        }
        if (pos == -1) break;
        while (pos) {
            // cout << pos << endl;
            inSet[pos] ^= 1;
            pos = pre[pos];
        }
        s.clear();
        for (int i = 1; i <= m; i++) {
            if (inSet[i]) s.push_back(i);
        }
    }
    cout << s.size() << '\n';
    for (int u : s) cout << u << ' ';
    cout << endl; 
    return 0;
}