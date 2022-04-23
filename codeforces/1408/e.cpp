#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
#define int long long

int n, m;
int a[N], b[N];
vector<int> ls[N];
int id[N];

struct DSU {
    int numComp;
    vector<int> root;

    DSU(int n = 0) {
        numComp = n;
        root.assign(n + 1, 0);
    }

    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }

    bool unite(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        numComp--;
        return 1;
    }
};


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        id[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    long long sum = 0;
    for (int i = 1; i <= m; i++) {
        int s;
        cin >> s;
        ls[i].assign(s, 0);
        sum += 1ll * s * a[i];
        for (int &u : ls[i]) {
            cin >> u;
            sum += b[u];
        }
    }
    sort(id + 1, id + m + 1, [&](int u, int v) {
        return a[u] > a[v];
    });
    DSU dsu(n);
    for (int i = 1; i <= m; i++) {
        int u = id[i];
        // cout << "# " << i << ' ' << u << endl;
        sort(ls[u].begin(), ls[u].end(), [&](int x, int y) {
            return dsu.getRoot(x) < dsu.getRoot(y);
        });
        for (int l = 0, r = 0; l < ls[u].size(); l = r) {
            while (r < ls[u].size() && dsu.getRoot(ls[u][l]) == dsu.getRoot(ls[u][r])) r++;
            long long maxVal = 0;
            for (int j = l; j < r; j++) {
                maxVal = max(maxVal, 1ll * b[ls[u][j]]);
            }
            sum -= (a[u] + maxVal);
            // cout << maxVal << endl;
        }
        for (int j = 0; j + 1 < ls[u].size(); j++) {
            dsu.unite(ls[u][j], ls[u][j + 1]);
        }
        // cout << sum << endl;
    }
    cout << sum << endl;
    return 0;
}