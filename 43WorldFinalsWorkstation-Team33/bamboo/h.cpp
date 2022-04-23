#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 6;
const int LOG = 21;

int nxt[N];
int par[LOG][N];
int posincycle[N];
int change[N];

vector<int> a[N];
int numcom;
int comid[N];
int deg[N];
bool incycle[N];

int depth[N];

int ans[N];

vector<int> cycle[N]; // cycle_id == comid
vector<int> pref[N];

int n, k;

void dfs_com(int u, int curcom) {
    comid[u] = curcom;
    for (int v : a[u]) {
        if (comid[v] == 0) dfs_com(v, curcom);
    }
}

void dfs_depth(int u) {
    for (int v : a[u]) {
        if (!incycle[v] && v != nxt[u]) {
            depth[v] = depth[u] + 1;
            dfs_depth(v);
        }
    }
}

void bfs_from_leaves() {
    for (int i = 1; i <= n; ++i) {
        incycle[i] = true;
    }

    queue<int> Q;
    for (int i = 1; i <= n; ++i) {
        deg[i] = a[i].size();
        if (deg[i] == 1) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        incycle[u] = false;
        par[0][u] = nxt[u];
        deg[nxt[u]] -= 1;
        if (deg[nxt[u]] == 1) {
            Q.push(nxt[u]);
        }
    }
}

void init_lca() {
    for (int i = 1; i <= n; ++i) {
        if (incycle[i]) {
            par[0][i] = i;
        }
    }
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            par[j][i] = par[j - 1][par[j - 1][i]];
        }
    }
}

int jump(int u, int step) {
    for (int i = LOG - 1; i >= 0; --i) if ((1 << i) <= step) {
        step -= 1 << i;
        //cerr << "jump " << u << ' ' << i << ' ' << par[i][u] << endl;
        u = par[i][u];
    }
    return u;
}

void gen_cycles() {
    vector<bool> was(numcom + 1);
    for (int i = 1; i <= n; ++i) if (incycle[i] && !was[comid[i]]) {
        was[comid[i]] = true;
        //cerr << "incycle true " << i << endl;
        cycle[comid[i]].push_back(i);
        for (int u = nxt[i]; u != i; u = nxt[u]) {
            cycle[comid[i]].push_back(u);
        }
    }

    for (int i = 1; i <= numcom; ++i) {
        //cerr << "cycle #" << i << ": ";
        for (int j = 0; j < cycle[i].size(); ++j) {
            posincycle[cycle[i][j]] = j;
            //cerr << cycle[i][j] << ' ';
        }
        //cerr << endl;
    }
}

void cycle_to_cycle() {
    vector<int> inc_cycle(numcom + 1);
    for (int i = 1; i <= numcom; ++i) {
        if (k >= cycle[i].size() - 1) {
            inc_cycle[i] = cycle[i].size();
        } else {
            inc_cycle[i] += k + 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (incycle[i]) {
            ans[i] += inc_cycle[comid[i]];
            //cerr << "after cycle_to_cycle " << i << ' ' << ans[i] << endl;
        }
    }
}

void inc_range(int id, int l, int r) {
    //cerr << "inc_range " << id << ' ' << l << ' ' << r << endl;
    //assert(l <= r);
    //assert(r < pref[id].size());
    pref[id][l] += 1;
    if (r + 1 < pref[id].size()) pref[id][r + 1] -= 1;
}

void update_cycle(int u, int step) {
    //cerr << "update_cycle " << u << ' ' << step << endl;
    int pos = posincycle[u];
    if (step >= cycle[comid[u]].size() - 1) {
        inc_range(comid[u], 0, cycle[comid[u]].size());
    } else if (pos + step < cycle[comid[u]].size()) {
        inc_range(comid[u], pos, pos + step);
    } else {
        inc_range(comid[u], pos, cycle[comid[u]].size() - 1);
        inc_range(comid[u], 0, pos + step - cycle[comid[u]].size());
    }
}

void update_path(int u) {
    int p = jump(u, k + 1);
    //cerr << "update_path parent " << u << ' ' << p << ' ' << k + 1 << endl;
    change[p] -= 1;
    change[u] += 1;

    int rem = k - depth[u];
    if (rem >= 0) update_cycle(p, rem);
}

void dfs_gather(int u) {
    for (int v : a[u]) {
        if (!incycle[v] && v != nxt[u]) {
            dfs_gather(v);
            change[u] += change[v];
        }
    }
    //cerr << "dfs_gather " << u << ' ' << change[u] << endl;
    ans[u] += change[u];
}

void tree_to_everywhere() {
    for (int i = 1; i <= numcom; ++i) {
        pref[i].resize(cycle[i].size());
    }

    for (int i = 1; i <= n; ++i) {
        if (!incycle[i]) {
            update_path(i);
        }
    }

    //cerr << "done update_path" << endl;
    //exit(0);

    for (int i = 1; i <= numcom; ++i) {
        for (int j = 1; j < cycle[i].size(); ++j) {
            //cerr << "pref " << j << ' ' << cycle[i][j] << ' ' << ans[cycle[i][j]] << ' ' << pref[i][j] << endl;
            pref[i][j] += pref[i][j - 1];
        }
        for (int j = 0; j < cycle[i].size(); ++j) {
            ans[cycle[i][j]] += pref[i][j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (incycle[i] && a[i].size() > 2) dfs_gather(i);
    }
}

void solve() {
    cycle_to_cycle();
    //cerr << "done cycle_to_cycle" << endl;
    tree_to_everywhere();
}

void gen(int _n) {
    n = _n;
    k = rand() % (n - 1) + 1;
    //k = 2;
    for (int i = 1; i <= n; ++i) {
        while (nxt[i] == 0 || nxt[i] == i) nxt[i] = rand() % n + 1;
    }
    /*
    cerr << "n=" << n << ' ' << "k=" << k << endl;
    for (int i = 1; i <= n; ++i) {
        cerr << "nxt " << i << ' ' << nxt[i] << endl;
    }
     */
}

vector<int> naive() {
    vector<int> res(n + 1);
    for (int i = 1; i <= n; ++i) {
        set<int> was;
        for (int u = i, step = 0; step <= k; u = nxt[u], ++step) {
            if (was.count(u)) break;
            was.insert(u);
            res[u]++;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> k; for (int i = 1; i <= n; ++i) cin >> nxt[i];
    //gen(10000);

    for (int i = 1; i <= n; ++i) {
        a[i].push_back(nxt[i]);
        a[nxt[i]].push_back(i);
    }

    numcom = 0;
    for (int i = 1; i <= n; ++i) {
        if (comid[i] == 0) {
            numcom += 1;
            dfs_com(i, numcom);
        }
    }

    bfs_from_leaves();
    for (int i = 1; i <= n; ++i) if (incycle[i] && a[i].size() > 2) {
            dfs_depth(i);
        }
    init_lca();

    gen_cycles();

    //cerr << "done init" << endl;

    solve();
    //return  0;

    //cerr << "here " << endl;

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }

    //cerr << "done" << endl;

    /*
    vector<int> res = naive();
    for (int i = 1; i <= n; ++i) {
        cerr << i << ' ' << ans[i] << ' ' << res[i] << endl;
        assert(ans[i] == res[i]);
    }*/

    return 0;
}