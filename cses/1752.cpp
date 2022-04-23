#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int INF = 1e9;

int n, d;
vector<int> adj[N];
pair<int, int> f[N];
set<int> s;
int head[N];

void dfs(int u, int p) {
    f[u] = {INF, 0};
    if (p != 0) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
    for (int v : adj[u]) {
        assert(v != p);
        dfs(v, u);
    }
    sort(adj[u].begin(), adj[u].end(), [&](int x, int y) {
        return f[x] > f[y];
    });
    for (int v : adj[u]) {
        if (f[u].first + f[v].first + 1 >= d) {
            f[u].first = f[v].first + 1;
            f[u].second += f[v].second;
            head[u] = head[v];
        } else {
            f[u].second += f[v].second - 1;
            s.erase(head[v]);
        }
    }
    
    if (f[u].first >= d) {
        f[u].first = 0;
        f[u].second++;
        head[u] = u;
        s.insert(u);
    }
    // cout << "# " << u << ' ' << f[u].first << ' ' << f[u].second << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> d;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << f[1].second << '\n';
    for (int u : s) cout << u << ' ';
        cout << endl;
    return 0;
}