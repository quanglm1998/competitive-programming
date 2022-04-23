#include <bits/stdc++.h>

#define int long long

using namespace std;
const int N = 200010;

const long long INF = 1e18;

int n, m;
int a, b;
vector<pair<int, int>> adj[N], revAdj[N];
int dist1[N], distn[N];
bool used[N];

void dijkstra(int root, int *dist, vector<pair<int, int>> *adj) {
    fill(dist + 1, dist + n + 1, INF);
    fill(used + 1, used + n + 1, 0);
    dist[root] = 0;
    set<pair<int, int>> s;
    s.insert({dist[root], root});
    while (!s.empty()) {
        int u = s.begin()->second;
        s.erase(s.begin());
        if (used[u]) continue;
        used[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                s.insert({dist[v], v});
            }
        }
    }
}

vector<pair<int, int>> newAdj[N];

int num[N], low[N], cnt;
int isDead[N];
int numComp;
vector<int> lsComp[N];
int dp[N];
int belong[N];
vector<int> st;

void dfs(int u) {
    num[u] = low[u] = ++cnt;
    st.push_back(u);
    for (auto [v, w] : newAdj[u]) {
        if (isDead[v]) continue;
        if (!num[v]) dfs(v);
        low[u] = min(low[u], low[v]);
    }
    if (num[u] == low[u]) {
        numComp++;
        while (1) {
            int v = st.back();
            st.pop_back();
            isDead[v] = 1;
            lsComp[numComp].push_back(v);
            belong[v] = numComp;
            if (v == u) break;
        }
    }
}

bool checkLoop(int id) {
    for (int u : lsComp[id]) {
        for (auto [v, w] : newAdj[u]) {
            if (belong[u] == belong[v]) return 1;
        }
    }
    return 0;
}

bool check(int lim) {
    if (dist1[n] <= lim) return 1;
    // init
    for (int i = 1; i <= n; i++) {
        newAdj[i].clear();
        num[i] = low[i] = 0;
        isDead[i] = 0;
        lsComp[i].clear();
        dp[i] = 0;
        belong[i] = 0;
    }
    st.clear();
    numComp = cnt = 0;

    for (int u = 1; u <= n; u++) {
        if (distn[u] > lim) continue;
        for (auto [v, w] : adj[u]) {
            if (distn[v] > lim) continue;
            if (distn[v] + w <= lim) newAdj[u].push_back({v, w});
        }
    }

    for (int i = 1; i <= n; i++) {
        if (distn[i] <= lim && !num[i]) {
            dfs(i);
        }
    }
    // for (int i = 1; i <= numComp; i++) {
    //     cout << "comp " << i << endl;
    //     for (int u : lsComp[i]) cout << u << ' ';
    //         cout << endl;
    // }
    for (int i = 1; i <= numComp; i++) {
        if (checkLoop(i)) {
            dp[i] = INF;
        } else {
            for (int u : lsComp[i]) {
                for (auto [v, w] : newAdj[u]) {
                    if (belong[u] != belong[v]) {
                        dp[i] = max(dp[i], dp[belong[v]] + w);
                    }
                }
            }
        }

        for (int u : lsComp[i]) {
           // cout << "# " << u << ' ' << dist1[u] << ' ' << a + lim - distn[u] << endl;
           // cout << lim - distn[u] + dp[i] << ' ' <<  b - a << endl;
            if (dist1[u] > a + lim - distn[u]) continue;
            if (lim - distn[u] + dp[i] >= b - a) return 1;
        }
    }
    return 0;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        revAdj[v].push_back({u, w});
        // if (w <= 8) {
        //     cout << "edge " << u << ' ' << v << ' ' << w << endl;
        // }
    }
    dijkstra(1, dist1, adj);
    dijkstra(n, distn, revAdj);
    // for (int i = 1; i <= n; i++) cout << dist1[i] << ' ';
    //     cout << endl;
    // for (int i = 1; i <= n; i++) cout << distn[i] << ' ';
    //     cout << endl;
    // check(8);
    int low = -1, high = INF;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << endl;
    return 0;
}