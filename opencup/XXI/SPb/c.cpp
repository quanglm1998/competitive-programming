#include <bits/stdc++.h>

using namespace std;

const int N = 600010;
const int MOD = 998244353;

int n, m;
vector<int> adj[N];
int num[N], low[N], cnt = 0;
vector<int> st;
int numNode;
vector<int> a[N];

void tarjan(int u, int p) {
    low[u] = num[u] = ++cnt;
    st.push_back(u);
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!num[v]) {
            tarjan(v, u);   
            if (low[v] >= num[u]) {
                numNode++;
                cout << "comp " << numNode << endl;
                while (1) {
                    int w = st.back();
                    cout << w << ' ';
                    a[numNode].push_back(w);
                    a[w].push_back(numNode);
                    if (w == u) break;
                    st.pop_back();
                }
                cout << endl;
                cout << "st: ";
                for (int u : st) cout << u << ' ';
                    cout << endl;

            }
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
    cout << "# " << u << ' ' << num[u] << ' ' << low[u] << endl;
}

int dp[N][2];

void dfs(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    for (int v : a[u]) {
        if (v == p) continue;
        dfs(v, u);
        if (u <= n) {
            dp[u][0] = (dp[u][0] + dp[v][0]) % MOD;
            dp[u][1] = 1ll * dp[u][1] * (dp[v][1] + 1) % MOD;
        } else {
            dp[u][0] = (dp[u][0] + dp[v][0]) % MOD;
            dp[u][0] = (dp[u][0] + dp[v][1]) % MOD;
            dp[u][1] = 1ll * dp[u][1] * dp[v][1] % MOD;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    numNode = n;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    tarjan(1, 0);
    dfs(1, 0);
    // for (int i = 1; i <= numNode; i++) {
        // cout << "# " << i << endl;
        // for (int u : a[i]) cout << u << ' ';
        //     cout << endl;
    // }
    cout << (1 + dp[1][0] + dp[1][1]) % MOD << endl;
    return 0;
}