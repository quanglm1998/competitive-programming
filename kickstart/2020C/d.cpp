#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N];

struct Node {
    long long sweet;
    long long sumAlt;
    int num;
    Node() {
        sweet = sumAlt = num = 0;
    }
    void init(int u) {
        sweet = sumAlt = u;
        num = 1;
    }
};

struct ST {
    Node t[N << 2];

    Node unite(Node u, Node v) {
        if (u.num == 0) return v;
        if (v.num == 0) return u;
        Node res;
        res.num = u.num + v.num;
        res.sumAlt = u.sumAlt + (u.num % 2 == 0 ? 1ll : -1ll) * v.sumAlt;
        long long now = v.sweet + v.sumAlt * u.num;
        res.sweet = u.sweet + (u.num % 2 == 0 ? 1ll : -1ll) * now;
        return res;
    }

    void init(int node, int l, int r) {
        if (l == r) {
            t[node].init(a[l]);
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        t[node] = unite(t[node << 1], t[node << 1 | 1]);
    }

    void update(int node, int l, int r, int x) {
        if (x > r || x < l) return;
        if (l == r) {
            t[node].init(a[l]);
            return;
        }
        int m = l + r >> 1;
        update(node << 1, l, m, x);
        update(node << 1 | 1, m + 1, r, x);
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
} st;

void solve(int test) {
    cout << "Case #" << test << ": ";
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    st.init(1, 1, n);
    long long res = 0;
    while (q--) {
        char op;
        cin >> op;
        if (op == 'U') {
            int x, v;
            cin >> x >> v;
            a[x] = v;
            st.update(1, 1, n, x);
        } else {
            int l, r;
            cin >> l >> r;
            Node now = st.get(1, 1, n, l, r);
            res += now.sweet;
        }
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}