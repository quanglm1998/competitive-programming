#include <bits/stdc++.h>

using namespace std;

const int N = 55;
const int V = N * N * 4;
const int X[] = {0, -1, 0, 1};
const int Y[] = {1, 0, -1, 0};

int n, m;
char s[N][N];

inline int pos(int u) { return u << 1; }
inline int neg(int u) { return u << 1 | 1; }
// ZERO-indexed
// color[i] = 1 means we choose i
struct TwoSAT {
    int n;
    int numComp;
    vector<int> adj[V];
    int low[V], num[V], root[V], cntTarjan;
    vector<int> stTarjan;
    int color[V];

    TwoSAT(int n) : n(n * 2) {
        memset(root, -1, sizeof root);
        memset(low, -1, sizeof low);
        memset(num, -1, sizeof num);
        memset(color, -1, sizeof color);
        cntTarjan = 0;
        stTarjan.clear();
    }

    // u | v
    void addEdge(int u, int v) {
        adj[u ^ 1].push_back(v);
        adj[v ^ 1].push_back(u);
    }

    void tarjan(int u) {
        stTarjan.push_back(u);
        num[u] = low[u] = cntTarjan++;
        for (int v : adj[u]) {
            if (root[v] != -1) continue;
            if (low[v] == -1) tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            while (1) {
                int v = stTarjan.back();
                stTarjan.pop_back();
                root[v] = numComp;
                if (u == v) break;
            }
            numComp++;
        }
    }

    bool solve() {
        for (int i = 0; i < n; i++) if (root[i] == -1) tarjan(i);
        for (int i = 0; i < n; i += 2) {
            if (root[i] == root[i ^ 1]) return 0;
            color[i >> 1] = (root[i] < root[i ^ 1]);
        }
        return 1;
    }
};

int encode(int u, int v) {
    return u * m + v;
}

pair<int, int> decode(int u) {
    return {u / m, u % m};
}

bool isInside(int u, int v) {
    return u >= 0 && u < n && v >= 0 && v < m;
}

vector<int> adj[N * N * 2];
bool can[N * N * 2][N * N * 2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    TwoSAT t(n * m * 2);

    // even -> horizontal
    // odd -> vertical

    pair<int, int> root;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'O') root = {i, j};
            if (s[i][j] == '#') continue;
            bool fHorizontal = 0;
            bool fVertical = 0;
            for (int dir = 0; dir < 4; dir++) {
                int ii = i + X[dir];
                int jj = j + Y[dir];
                if (!isInside(ii, jj) || s[ii][jj] == '#') {
                    if (dir & 1) fVertical = 1;
                    else fHorizontal = 1;
                } else {
                    adj[encode(i, j) << 1 | (dir % 2)].push_back(encode(ii, jj) << 1 | (dir % 2));
                }
            }
            if (fHorizontal) adj[encode(i, j) << 1].push_back(encode(i, j) << 1 | 1);
            if (fVertical) adj[encode(i, j) << 1 | 1].push_back(encode(i, j) << 1);
        
            if (s[i][j] == 'O' || s[i][j] == '*') {
                t.addEdge(pos(encode(i, j) << 1), pos(encode(i, j) << 1 | 1));
            }
        }
    }

    for (int i = 0; i < n * m * 2; i++) {
        queue<int> q;
        q.push(i);
        can[i][i] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!can[i][v]) {
                    can[i][v] = 1;
                    q.push(v);
                }
            }
        }
    }
    for (int i = 0; i < n * m * 2; i++) {
        for (int j = i + 1; j < n * m * 2; j++) {
            if (!can[i][j] && !can[j][i]) {
                t.addEdge(neg(i), neg(j));
            }
        }
    }

    for (int it = 0; it < 2; it++) {
        int node = encode(root.first, root.second) << 1 | it;
        for (int i = 0; i < n * m * 2; i++) {
            if (!can[node][i]) {
                t.addEdge(neg(node), neg(i));
            }
        }
    }
    if (t.solve()) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}