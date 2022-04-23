#include <bits/stdc++.h>
 
using namespace std;
 
const int K = 16;
 
map<int64_t, int> id;
map<int, int64_t> orig;
map<int64_t, int> belong;
vector<int> a[K];
int n, k;
 
vector<pair<int, int> > to;
 
int main() {
    ios::sync_with_stdio(false);
 
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        int ni; cin >> ni;
        a[i].resize(ni);
        for (int j = 0; j < ni; ++j) {
            cin >> a[i][j];
            belong[a[i][j]] = i;
        }
    }
 
    for (int i = 1; i <= k; ++i) {
        for (int v : a[i]) {
            if (id.count(v)) continue;
            id[v] = ++n;
            orig[n] = v;
        }
    }
 
    to.resize(n + 1);
 
    int64_t sum = 0;
    for (int i = 1; i <= k; ++i) {
        for (int v : a[i]) sum += v;
    }
 
    if (sum % k != 0) {
        cout << "No" << endl;
        return 0;
    }
 
    int64_t each = sum / k;
    for (int i = 1; i <= k; ++i) {
        int64_t cur = 0;
        for (int v : a[i]) cur += v;
        for (int v : a[i]) {
            int64_t u = each - cur + v;
            if (!id.count(u)) continue;
            if (u != v && belong[u] == belong[v]) continue;
            to[id[v]] = {id[u], i};
        }
    }
 
    vector<int> deg_in(n + 1);
    for (int i = 1; i <= n; ++i) if (to[i].first) {
        deg_in[to[i].first]++;
    }
    queue<int> Q;
    for (int i = 1; i <= n; ++i) if (deg_in[i] == 0) {
        Q.push(i);
    }
 
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        int v = to[u].first;
        if (v == 0) continue;
        --deg_in[v];
        if (deg_in[v] == 0) {
            Q.push(v);
        }
    }
 
    vector<bool> was(n + 1);
    vector<int> trace(1 << k);
    vector< vector<int> > cycle(1 << k);
    for (int i = 1; i <= n; ++i) if (deg_in[i] && !was[i]) {
        was[i] = true;
        int mask = 1 << (to[i].second - 1);
        vector<int> cur = {i};
        //cerr << "cycle " << orig[i] << ' ';
        bool fail = false;
        for (int u = to[i].first; u != i; u = to[u].first) {
            //cerr << orig[u] << ' ';
            was[u] = true;
            cur.push_back(u);
            if (mask >> (to[u].second - 1) & 1) {
                fail = true;
            }
            mask |= 1 << (to[u].second - 1);
        }
        if (fail) continue;
        //cerr << endl;
        //cerr << mask << endl;
        trace[mask] = mask;
        cycle[mask] = cur;
    }
 
    for (int mask = 1; mask < (1 << k); ++mask) if (!trace[mask]) {
        for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) if (cycle[sub].size()) {
            if (trace[mask ^ sub]) {
                trace[mask] = sub;
                //cerr << "trace " << mask << ' ' << sub << endl;
                break;
            }
        }
    }
 
    int all = (1 << k) - 1;
    if (!trace[all]) {
        cout << "No" << endl;
        return 0;
    }
 
    vector< pair<int, int> > ans(k + 1);
    for (int mask = all; mask; mask ^= trace[mask]) {
        int sub = trace[mask];
        for (int i = 0; i < cycle[sub].size(); ++i) {
            int j = i - 1;
            if (j < 0) j += cycle[sub].size();
            ans[to[cycle[sub][i]].second] = {orig[cycle[sub][i]], to[cycle[sub][j]].second};
        }
    }
 
    cout << "Yes" << endl;
    for (int i = 1; i <= k; ++i) {
        cout << ans[i].first << ' ' << ans[i].second << endl;
    }
}