#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n, m;
int a[N], b[N];
int order[N];
int sum[N];

struct SegmentTree {
    struct Node {
        int minVal, maxVal, delta, minDelta;
    };

    Node t[N << 2];

    void pull(int node) {
        t[node].minVal = min(t[node << 1].minVal, t[node << 1 | 1].minVal);
        t[node].maxVal = max(t[node << 1].maxVal, t[node << 1 | 1].maxVal);
        t[node].delta = t[node << 1].delta + t[node << 1 | 1].delta;
        t[node].minDelta = min(t[node << 1].minDelta, t[node << 1].delta + t[node << 1 | 1].minDelta);
    }

    void init(int node, int l, int r) {
        if (l == r) {
            t[node].minVal = t[node].maxVal = a[order[l]];
            t[node].delta = t[node].minDelta = sum[l] - a[order[l]];
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        pull(node);
    }

    void add(int node, int l, int r, int val) {
        if (l == r) {
            assert(t[node].minVal == val);
            t[node].minVal++;
            t[node].maxVal++;
            t[node].delta--;
            t[node].minDelta--;
            return;
        }
        int m = l + r >> 1;
        if (t[node << 1].minVal <= val) add(node << 1, l, m, val);
        else add(node << 1 | 1, m + 1, r, val);
        pull(node);
    }

    void sub(int node, int l, int r, int val) {
        if (l == r) {
            assert(t[node].minVal == val);
            t[node].minVal--;
            t[node].maxVal--;
            t[node].delta++;
            t[node].minDelta++;
            return;
        }
        int m = l + r >> 1;
        if (t[node << 1 | 1].maxVal >= val) sub(node << 1 | 1, m + 1, r, val);
        else sub(node << 1, l, m, val);
        pull(node);
    }

    void update(int node, int l, int r, int x, int val) {
        if (x > r || x < l) return;
        if (l == r) {
            t[node].delta += val;
            t[node].minDelta += val;
            return;
        }
        int m = l + r >> 1;
        update(node << 1, l, m, x, val);
        update(node << 1 | 1, m + 1, r, x, val);
        pull(node);
    }

    bool getAns() {
        return t[1].minDelta >= 0;
    }
} st;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    iota(order + 1, order + n + 1, 1);
    sort(order + 1, order + n + 1, [&](int u, int v) {
        return a[u] > a[v];
    });

    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        sum[min(n, b[i])]++;
    }

    for (int i = n - 1; i; i--) {
        sum[i] += sum[i + 1];
    }

    st.init(1, 1, n);
    int q;
    cin >> q;
    while (q--) {
        int op, u;
        cin >> op >> u;
        if (op == 1) {
            st.add(1, 1, n, a[u]);
            a[u]++;
        } else if (op == 2) {
            st.sub(1, 1, n, a[u]);
            a[u]--;
        } else if (op == 3) {
            b[u]++;
            if (b[u] <= n) st.update(1, 1, n, b[u], +1);
        } else {
            if (b[u] <= n) st.update(1, 1, n, b[u], -1);
            b[u]--;
        }
        cout << st.getAns() << '\n';
        // cout << "delta " << st.t[1].minDelta << '\n';
    }
    return 0;
}