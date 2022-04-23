#include <bits/stdc++.h>

using namespace std;

const int N = 16;

int n;
vector<int> adj[1 << N];
int cur[1 << N];
vector<int> res;

void dfs(int u) {
    while (cur[u]) {
        int v = adj[u][--cur[u]];
        dfs(v);
    }
    res.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;   
    if (n == 1) {
        cout << "01" << '\n';
        return 0;
    }
    int mask = (1 << n - 1) - 1;
    for (int i = 0; i < (1 << n - 1); i++) {
        int nextMask = (i << 1) & mask;
        adj[i].push_back(nextMask);
        adj[i].push_back(nextMask | 1);
        cur[i] = 2;
    }
    dfs(0);
    while (res.size() < (1 << n) + n - 1) res.push_back(res[res.size() - (1 << n)]);
    for (int u : res) cout << (u & 1);
        cout << endl;
    return 0;
}