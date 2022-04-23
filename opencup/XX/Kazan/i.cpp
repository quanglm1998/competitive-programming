#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
vector<int> adj[N];
int sz[N];
int isDead[N];

int ask(int x, const vector<int> &u) {
    cout << "? " << u.size() << ' ' << x << ' ';
    for (int v : u) cout << v << ' ';
        cout << endl;
    int res;
    cin >> res;
    return res;
}

int dfsFindCentroid(int u, int p, int allSize) {
    sz[u] = 1;
    int isGood = 1;
    for (int v : adj[u]) {
        if (v == p || isDead[v]) continue;
        int now = dfsFindCentroid(v, u, allSize);
        if (now) return now;
        sz[u] += sz[v];
        isGood &= (sz[v] * 2 <= allSize);
    }
    isGood &= ((allSize - sz[u]) * 2 <= allSize);
    return isGood ? u : 0;
}

void dfsInit(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || isDead[v]) continue;
        dfsInit(v, u);
        sz[u] += sz[v];
    }
}

void solve(int u, int allSize) {
    if (allSize == 1) {
        cout << "! " << u << endl;
        return;
    }
    u = dfsFindCentroid(u, 0, allSize);
    dfsInit(u, 0);
    vector<int> ls;
    for (int v : adj[u]) {
        if (!isDead[v]) ls.push_back(v);
    }

    if (ask(u, ls)) {
        cout << "! " << u << endl;
        return;
    }


    sort(ls.begin(), ls.end(), [&](int u, int v) {
        return sz[u] > sz[v];
    });
    int curSize = allSize - 1;
    int l = 0, r = ls.size() - 1;
    while (r > l) {
        int m = l;
        int now = 0;
        vector<int> lsToAsk;
        while (m <= r && (now + sz[ls[m]]) * 2 < curSize) {
            now += sz[ls[m]];
            lsToAsk.push_back(ls[m]);
            m++;
        }
        now += sz[ls[m]];
        lsToAsk.push_back(ls[m]);
        if (!ask(u, lsToAsk)) {
            curSize = now;
            r = m;
        } else {
            curSize -= now;
            l = m + 1;
        }
    }
    assert(l == r);
    isDead[u] = 1;
    solve(ls[l], sz[ls[l]]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve(1, n);
    return 0;
}