#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int n, m;
vector<int> adj[N];
int num[N], low[N], root[N];
int cnt;
vector<int> st;
int numCon;
int tot[N];
int inQueue[N];
bool isLeaf[N];
int numEdge, numVer;
vector<int> vers;
int deg[N];

void tarjan(int u, int p) {
    numVer++;
    vers.push_back(u);
    numEdge += adj[u].size();
    num[u] = low[u] = ++cnt;
    st.push_back(u);
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!num[v]) tarjan(v, u);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        numCon++;
        while (1) {
            int v = st.back();
            st.pop_back();
            root[v] = numCon;
            tot[numCon]++;
            if (u == v) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<pair<int, int>> res;
    for (int i = 1; i <= n; i++) deg[i] = adj[i].size();
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            numEdge = numVer = 0;
            vers.clear();
            tarjan(i, 0);
            numEdge /= 2;
//            cout << i << ' ' << numEdge << ' ' << numVer << endl;
            if (numEdge + 1 == numVer) {
                for (int u : vers) {
                    if (adj[u].size() == 1) {
                        res.push_back({u, adj[u][0]});
                    }
                }
            } else {
                queue<int> q;
                for (int u : vers) {
                    if (tot[root[u]] == 1 && adj[u].size() == 1) {
                        q.push(u);
                        inQueue[u] = 1;
                    }
                }
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v : adj[u]) {
                        deg[v]--;
                        if (tot[root[v]] == 1) {
                            if (deg[v] == 1) {
                                q.push(v);
                                inQueue[v] = 1;
                            }
                        }
                    }
                }
                for (int u : vers) {
                    if (inQueue[u]) {
                        for (int v : adj[u]) {
                            if (!inQueue[v]) res.push_back({v, u});
                        }
                    }
                }
            }
        }
    }
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for (auto u : res) {
        cout << u.first << ' ' << u.second << endl;
    }
    return 0;
}