#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, m;
vector<int> adj[N];
int num[N], low[N], cnt;
int isDead[N];
vector<int> st;

int belong[N], numComp;
vector<int> compLs[N];
int deg[N];

void dfs(int u) {
    num[u] = low[u] = ++cnt;
    st.push_back(u);
    for (int v : adj[u]) {
        if (isDead[v]) continue;
        if (!num[v]) dfs(v);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        numComp++;
        while (1) {
            int v = st.back();
            st.pop_back();
            isDead[v] = 1;
            belong[v] = numComp;
            compLs[numComp].push_back(v);
            if (u == v) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int u : adj[i]) {
            if (belong[u] != belong[i]) {
                deg[belong[u]]++;
            }
        }
    }
    vector<int> ls;
    for (int i = 1; i <= numComp; i++) {
        if (!deg[i]) {
            ls.push_back(i);
        }
    }
    if (ls.size() >= 2) {
        cout << 0 << endl;
        return 0;
    } else {
        cout << compLs[ls[0]].size() << '\n';
        sort(compLs[ls[0]].begin(), compLs[ls[0]].end());
        for (int u : compLs[ls[0]]) {
            cout << u << ' ';
        }
        cout << '\n';
    }
    return 0;
}