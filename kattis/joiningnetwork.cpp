#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 50010;
const double INF = 1e20;

struct Tree {
    int n;
    vector<int> adj[N];
    int numChild[N];
    ll sum[N], sumUp[N];
    ll sumSq[N], sumSqUp[N];
    int ls[N];

    void init() {
        cin >> n;
        for (int i = 1; i < n; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v); adj[v].push_back(u);
        }
        dfs_down(1, 0);
        dfs_up(1, 0);
        for (int i = 1; i <= n; i++) {
            ls[i] = i;
        }
        sort(ls + 1, ls + n + 1, [&](int u, int v) {
            return getSum(u) < getSum(v);
        });
    }

    void dfs_down(int u, int p) {
        numChild[u] = 1;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_down(v, u);
            numChild[u] += numChild[v];
            sum[u] += sum[v];
            sumSq[u] += sumSq[v] + 2ll * sum[v];
        }
        sum[u] += numChild[u] - 1;
        sumSq[u] += numChild[u] - 1;
    }

    void dfs_up(int u, int p) {
        for (int v : adj[u]) {
            if (v == p) continue;
            ll sumW = sum[u] - sum[v] - numChild[u] + 1;
            ll sumSqW = sumSq[u] - sumSq[v] - 2ll * sumW - 2ll * sum[v] - numChild[u] + 1;
            sumUp[v] = sumUp[u] + sum[u] - sum[v] + n - 2ll * numChild[v];
            sumSqUp[v] = sumSqUp[u] + 2ll * sumUp[u] + n - numChild[u] + 1 + sumSqW + 4ll * sumW + 4ll * (numChild[u] - 1 - numChild[v]);
            dfs_up(v, u);
        }
    }

    ll getSum(int u) { 
        return sum[u] + sumUp[u]; 
    }

    ll getSumSq(int u) {
        return sumSq[u] + sumSqUp[u]; 
    }
} A, B;

struct ConvexHull {
    struct Line {
        long long a, b;
        double x;
    };
    deque<Line> q;

    void add(long long A, long long B) {
        double X = -INF;
        while (!q.empty()) {
            Line cur = q.back();
            if (cur.a == A) {
                if (B < cur.b) q.pop_back();
                return;
            }
            X = 1.0 * (B - cur.b) / (cur.a - A);
            if (X <= cur.x) q.pop_back();
            else break;
        }
        q.push_back({A, B, X});
    }

    long long get(long long u) {
        while (q.size() >= 2 && q[1].x <= u) q.pop_front();
        return q[0].a * u + q[0].b;
    }
} h;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    A.init(); B.init(); 
    for (int i = B.n; i >= 1; i--) {
        int id = B.ls[i];
        h.add(2ll * B.getSum(id), B.getSumSq(id) * A.n + B.getSum(id) * 2ll * A.n);
    }
    ll res = (1ll << 63) - 1ll;
    for (int i = 1; i <= A.n; i++) {
        int id = A.ls[i];
        res = min(res, h.get(A.getSum(id)) + A.getSumSq(id) * B.n + A.getSum(id) * 2ll * B.n + 1ll * A.n * B.n);
    }
    ll ans = 0;
    for (int i = 1; i <= A.n; i++) {
        ans += A.getSumSq(i);
    }
    for (int i = 1; i <= B.n; i++) {
        ans += B.getSumSq(i);
    }
    ans /= 2;
    cout << res + ans << '\n';
    return 0;
}