#include <bits/stdc++.h>

using namespace std;

const int LOG = 60;
const int N = 5100;
const int NUM_BOX = 200;

int n, m;
pair<long long, int> a[N];
int numHeap = 0;
int numBox = 0;
bool inSet[N];
int hasBox[NUM_BOX];

long long basis[LOG];
long long mask[LOG];
vector<int> adj[N];
bool canAddColored[N];
int pre[N];
long long res[NUM_BOX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long u;
        cin >> u;
        a[++numHeap] = {u, ++numBox};
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        numBox++;
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            long long u;
            cin >> u;
            a[++numHeap] = {u, numBox};
        }
    }
    vector<int> independentSet;
    while (1) {
        // init
        for (int i = 0; i < LOG; i++) {
            basis[i] = mask[i] = 0;
        }
        for (int i = 1; i <= numHeap; i++) {
            adj[i].clear();
            canAddColored[i] = 0;
            pre[i] = -1;
        }
        // gauss
        for (int i = 0; i < independentSet.size(); i++) {
            long long u = a[independentSet[i]].first;
            long long curMask = 1ll << i;
            for (int j = 0; j < LOG; j++) {
                if (u >> j & 1) {
                    if (!basis[j]) {
                        basis[j] = u;
                        mask[j] = curMask;
                        break;
                    }
                    curMask ^= mask[j];
                    u ^= basis[j];
                }
            }
        }
        // linear matroid
        vector<int> canAddLinear;
        for (int i = 1; i <= numHeap; i++) {
            if (inSet[i]) continue;
            long long u = a[i].first;
            long long curMask = 0;
            for (int j = 0; j < LOG; j++) {
                if (u >> j & 1) {
                    if (!basis[j]) break;
                    curMask ^= mask[j];
                    u ^= basis[j];
                }
            }
            if (u) {
                canAddLinear.push_back(i);
                for (int u : independentSet) adj[u].push_back(i);
            } else {
                for (int j = 0; j < LOG; j++) {
                    if (curMask >> j & 1) {
                        adj[independentSet[j]].push_back(i);
                    }
                }
            }
        }
        // colored matroid
        for (int i = 1; i <= numHeap; i++) {
            if (inSet[i]) continue;
            if (!hasBox[a[i].second]) {
                canAddColored[i] = 1;
                for (int u : independentSet) adj[i].push_back(u);
            } else {
                for (int u : independentSet) if (a[u].second == a[i].second) adj[i].push_back(u);
            }
        }
        // find augmenting path
        int root = 0;
        queue<int> q;
        for (int u : canAddLinear) {
            if (canAddColored[u]) {
                root = u;
                pre[u] = 0;
                break;
            }
            q.push(u);
            pre[u] = 0;
        }
        while (!q.empty() && !root) {
            int u = q.front(); q.pop();
            if (canAddColored[u]) {
                root = u;
                break;
            }
            for (int v : adj[u]) {
                if (pre[v] == -1) {
                    pre[v] = u;
                    q.push(v);
                }
            }
        }
        if (!root) break;
        int rightSide = 1;
        while (root) {
            if (rightSide) {
                inSet[root] = 1;
                hasBox[a[root].second]++;
            } else {
                inSet[root] = 0;
                hasBox[a[root].second]--;   
            }
            root = pre[root];
            rightSide ^= 1;
        }
        independentSet.clear();
        for (int i = 1; i <= numHeap; i++) if (inSet[i]) independentSet.push_back(i);
    }
    if (independentSet.size() < n + m) {
        cout << -1 << endl;
    } else {
        for (int u : independentSet) {
            if (a[u].second > n) {
                res[a[u].second - n] = a[u].first;
            }
        }
        for (int i = 1; i <= m; i++) cout << res[i] << '\n';
    }
    return 0;
}