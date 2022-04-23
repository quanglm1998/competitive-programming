#include <bits/stdc++.h>

using namespace std;

const int N = 5000;

int n;
string s[N];
int used[N];
string x[N], y[N], z[N];
map<string, vector<int>> lsX, lsY, lsZ;

void dfs(int u) {
    used[u] = 1;
    for (int v : lsX[x[u]]) {
        if (!used[v]) dfs(v);
    }
    for (int v : lsY[y[u]]) {
        if (!used[v]) dfs(v);
    }
    for (int v : lsZ[z[u]]) {
        if (!used[v]) dfs(v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        x[i] = s[i].substr(1, 2);
        y[i] = s[i].substr(3, 2);
        z[i] = s[i].substr(5, 2);
        lsX[x[i]].push_back(i);
        lsY[y[i]].push_back(i);
        lsZ[z[i]].push_back(i);
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            res++;
            dfs(i);
        }
    }
    cout << res << endl;
    return 0;
}