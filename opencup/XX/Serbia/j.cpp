#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int NUM = 62;
const long long INF = (1ll << 62) + 10;

int n;
long long a[N];

struct Node {
    // long long base[NUM];
    long long minVal = 0;

    Node() {
        // memset(base, 0, sizeof base);
        minVal = INF;
    }

    void init(long long val) {
        // memset(base, 0, sizeof base);
        while (val % 2 == 0) val >>= 1;
        minVal = val;
        // int cur = 63 - __builtin_clzll(val);
        // for (int i = cur; i < NUM; i++) {
        //     base[i] = val;
        //     val <<= 1ll;
        // }
    }

    // void add(long long u) {
    //     for (int i = NUM - 1; i >= 0; i--) {
    //         if (u >> i & 1ll) {
    //             if (base[i] >> i & 1) u ^= base[i];
    //             else {
    //                 base[i] = u;
    //                 break;
    //             }
    //         }
    //     }
    // }

    void getMinVal() {
        // for (int i = 0; i < NUM; i++) {
        //     if (base[i] >> i & 1ll) {
        //         minVal = base[i];
        //         break;
        //     }
        // }
    }

    void debug() {
        // cout << "base " << endl;
        // for (int i = NUM - 1; i >= 0; i--) {
        //     cout << base[i] << endl;
        // }
    }
};

struct IT {
    Node t[N << 2];

    Node unite(Node u, Node v) {
        if (u.minVal >= INF) return v;
        if (v.minVal >= INF) return u;
        if (u.minVal > v.minVal) swap(u, v);
        long long x = u.minVal;
        long long y = v.minVal;
        int numy = 63 - __builtin_clzll(y);
        int numx = 63 - __builtin_clzll(x);
        for (int i = numy; i >= numx; i--) {
            if (y >> i & 1ll) {
                y ^= (x << (i - numx));
            }   
        }
        if (y) x = min(x, y);
        Node res;
        res.init(x);
        return res;

        // if (u.minVal >= INF) return v;
        // if (v.minVal >= INF) return u;
        // Node* uu = &u;
        // Node* vv = &v;
        // if (uu->minVal > vv->minVal) swap(uu, vv);
        // Node res = *uu;
        // res.add(vv->minVal);
        // res.getMinVal();
        // return res;
    }

    void init(int node, int l, int r) {
        if (l == r) {
            t[node].init(a[l]);
        } else {
            int m = l + r >> 1;
            init(node << 1, l, m);
            init(node << 1 | 1, m + 1, r);
            t[node] = unite(t[node << 1], t[node << 1 | 1]);
        }
    }

    void update(int node, int l, int r, int x, long long val) {
        if (x > r || x < l) return;
        if (l == r) {
            t[node].init(a[l]);
            // t[node].debug();
            return;
        }
        int m = l + r >> 1;
        update(node << 1, l, m, x, val);
        update(node << 1 | 1, m + 1, r, x, val);
        t[node] = unite(t[node << 1], t[node << 1 | 1]);
    }

    Node get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return Node();
        if (x <= l && r <= y) return t[node];
        int m = l + r >> 1;
        Node p1 = get(node << 1, l, m, x, y);
        Node p2 = get(node << 1 | 1, m + 1, r, x, y);
        return unite(p1, p2);
    }
} it;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    it.init(1, 1, n);
    int q;
    cin >> q;
    while (q--) {
        long long op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            a[x] = y;
            it.update(1, 1, n, x, y);
        } else {
            Node res = it.get(1, 1, n, x, y);
            // res.debug();
            cout << res.minVal << '\n';
        }
    }
    return 0;
}