#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int n;
vector<int> adj[N];
int c[N], numChild[N];
int res[N];

void dfsInit(int u) {
    numChild[u] = 1;
    for (int v : adj[u]) {
        dfsInit(v);
        numChild[u] += numChild[v];
    }
}

void dfsCalc(int u, vector<int> ls) {
    if (c[u] >= ls.size()) {
        cout << "NO\n";
        exit(0);
    }
    res[u] = ls[c[u]];
    int cur = 0;
    for (int v : adj[u]) {
        vector<int> nxt;
        for (int i = 1; i <= numChild[v]; i++) {
            if (cur == c[u]) cur++;
            nxt.push_back(ls[cur]);
            cur++;
        }
        dfsCalc(v, nxt);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    int root = -1;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> c[i];
        if (p == 0) {
            root = i;
        } else {
            adj[p].push_back(i);
        }
    }
    dfsInit(root);
    vector<int> ls;
    for (int i = 1; i <= n; i++) ls.push_back(i);
    dfsCalc(root, ls);
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}