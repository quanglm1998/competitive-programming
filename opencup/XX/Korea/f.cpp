#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

struct Node {
    // to push
    pair<int, int> lazy;
    // to pull
    bool hasInf;
    long long numPeople;

    Node(pair<int, int> lazy = {1, 0}, bool hasInf = 0, long long numPeople = 0) : lazy(lazy), hasInf(hasInf), numPeople(numPeople) {
        
    }

    template<typename T>
    void apply(int l, int r, const T &val) {
        mulTo(lazy.first, val.lazy.first);
        lazy.second = add(mul(val.lazy.first, lazy.second), val.lazy.second);
        hasInf |= val.hasInf;
        numPeople += val.numPeople;
    }

    void pull(const Node &u, const Node &v) {
        hasInf = u.hasInf | v.hasInf;
        numPeople = u.numPeople + v.numPeople;
    }

    void push(int l, int r, Node &u, Node &v) {
        Node now(lazy, 0, 0);
        u.apply(l, r, now);
        v.apply(l, r, now);
        lazy = {1, 0};
    }
};

struct SegmentTree {
    int search(int node, int l, int r, long long &val) {
        // cout << node << ' ' << l << ' ' << r << ' ' << val << endl;
        // cout << t[node].hasInf << ' ' << t[node].numPeople << endl;
        if (val == 0) {
            if (t[node].numPeople == 0) return -1;
        }
        if (!t[node].hasInf && t[node].numPeople <= val) {
            val -= t[node].numPeople;
            return -1;
        }
        if (l == r) {
            if (t[node].hasInf) {
                if (val & 1) return l;
                val >>= 1;
                return -1;
            } else {
                return l;
            }
        }
        int m = l + r >> 1;
        int res = search(node << 1 | 1, m + 1, r, val);
        if (res != -1) return res;
        return search(node << 1, l, m, val);
    }

    void init(int node, int l, int r) {
        if (l == r) {
            t[node].apply(l, r, Node());
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        t[node].pull(t[node << 1], t[node << 1 | 1]);
    }

    /*------------------------------------------------------------------*/
    int n;
    vector<Node> t;
    
    SegmentTree(int n) : n(n) {
        t.assign(n << 2 | 1, {});
        init(1, 1, n);
    }

    template<typename T>
    void update(int node, int l, int r, int x, int y, const T &val) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            t[node].apply(l, r, val);
            return;
        }
        int m = l + r >> 1;
        t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
        update(node << 1, l, m, x, y, val);
        update(node << 1 | 1, m + 1, r, x, y, val);
        t[node].pull(t[node << 1], t[node << 1 | 1]);
    }

    Node get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return Node();
        if (x <= l && r <= y) return t[node];
        int m = l + r >> 1;
        t[node].push(l, r, t[node << 1], t[node << 1 | 1]);
        Node p1 = get(node << 1, l, m, x, y);
        Node p2 = get(node << 1 | 1, m + 1, r, x, y);
        if (y <= m) return p1;
        else if (x > m) return p2;
        else {
            Node res;
            res.pull(p1, p2);
            return res;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    SegmentTree st(n + 1);
    st.update(1, 0, n, 0, 0, Node({1, 0}, 0, 1e18));
    int cnt = 0;
    vector<int> isInf(1, 0);
    for (int i = 1; i <= n; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int k;
            cin >> k;
            cnt++;
            if (k) {
                isInf.push_back(0);
                st.update(1, 0, n, 0, cnt - 1, Node({1, k}, 0, 0));
                st.update(1, 0, n, cnt, cnt, Node({1, 0}, 0, k));
            } else {
                isInf.push_back(1);
                st.update(1, 0, n, 0, cnt, Node({2, 0}, 0, 0));
                st.update(1, 0, n, cnt, cnt, Node({1, 1}, 1, 0));
            }
        } else if (op == 2) {
            int g, x;
            cin >> g >> x;
            Node now = st.get(1, 0, n, g, g);
            cout << add(now.lazy.second, mul(now.lazy.first, x - 1)) << '\n';
        } else {
            long long x;
            cin >> x;
            // int r = n;
            // while (r) {
            //     r = st.search(1, 0, n, 0, r, x);
            //     // cout << r << ' ' << isInf[r] << ' ' << x << endl;
            //     if (!isInf[r]) break;
            //     if (x % 2 == 0) break;
            //     x = (x + 1) / 2;
            //     r--;
            // }
            cout << st.search(1, 0, n, x) << '\n';
            // return 0;
        }
    }
    return 0;
}