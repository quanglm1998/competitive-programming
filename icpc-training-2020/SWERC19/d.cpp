#include <bits/stdc++.h>

using namespace std;

// make sure that BASE > maxValue
const int BASE = 1000000003;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int NUM = 3;
const int MOD[NUM] = {1000000007, 1000000009, 998224353};

inline int add(int u, int v, int MOD) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v, int MOD) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v, int MOD) {return (long long)u * v % MOD;}
inline int power(int u, int v, int MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, MOD)) if (v & 1) res = mul(res, u, MOD); return res;}
inline int inv(int u, int MOD) {return power(u, MOD - 2, MOD);}
inline void addTo(int &u, int v, int MOD) {u = add(u, v, MOD);}
inline void subTo(int &u, int v, int MOD) {u = sub(u, v, MOD);}
inline void mulTo(int &u, int v, int MOD) {u = mul(u, v, MOD);}

struct Hash {
    int a[NUM];
    Hash(int u = 0) {
        for (int i = 0; i < NUM; i++) {
            a[i] = u % MOD[i];
        }
    }
    Hash operator + (const Hash &u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = add(a[i], u.a[i], MOD[i]);
        }
        return res;
    }
    Hash operator - (const Hash &u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = sub(a[i], u.a[i], MOD[i]);
        }
        return res;
    }
    Hash operator * (const int u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = mul(a[i], u, MOD[i]);
        }
        return res;
    }
    Hash operator * (const Hash &u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = mul(a[i], u.a[i], MOD[i]);
        }
        return res;
    }
    bool operator == (const Hash &u) const {
        for (int i = 0; i < NUM; i++) {
            if (a[i] != u.a[i]) return 0;
        }
        return 1;
    }

    void debug() {
        for (int i = 0; i < NUM; i++) cout << a[i] << ' ';
            cout << endl;
    }
};

const int N = 10003;
const int M = 100000;

Hash powBase[M];

struct Node {
    Hash hash;
    int len;
    Node *l, *r;

    Node(int val) {
        hash = val;
        len = 1;
        l = r = NULL;
    }

    Node(Node *_l, Node *_r) {
        l = _l;
        r = _r;
        // len = l->len + r->len + 1;
        len = 2;
        hash = l->hash * powBase[2] + Hash(N + 1) * powBase[1] + r->hash;
    }
};

vector<Hash> solve(string s) {
    deque<Node*> q;
    for (int i = 1; i <= N; i++) {
        Node *u = new Node(i);
        q.push_back(u);
    }
    for (char u : s) {
        // for (int i = 0; i < q.size(); i++) {
        //     q[i]->hash.debug();
        // }
        if (u == 'C') {
            q.push_front(q.front());
        } else if (u == 'D') {
            q.pop_front();
        } else if (u == 'L') {
            if (q[0]->len == 1) return vector<Hash>();
            else {
                Node *foo = q.front();
                q.pop_front();
                q.push_front(foo->l);
            }
        } else if (u == 'P') {
            Node *u = q.front();
            q.pop_front();
            Node *v = q.front();
            q.pop_front();
            Node *w = new Node(u, v);
            q.push_front(w);
        } else if (u == 'R') {
            if (q[0]->len == 1) return vector<Hash>();
            else {
                Node *foo = q.front();
                q.pop_front();
                q.push_front(foo->r);
            }
        } else if (u == 'S') {
            Node *u = q.front();
            q.pop_front();
            Node *v = q.front();
            q.pop_front();
            q.push_front(u);
            q.push_front(v);
        } else if (u == 'U') {
            if (q[0]->len == 1) return vector<Hash>();
            else {
                Node *foo = q.front();
                q.pop_front();
                q.push_front(foo->r);
                q.push_front(foo->l);
            }
        } else {
            assert(0);
        }
    }
    vector<Hash> res;
    while (!q.empty()) {
        Node* now = q.front();
        q.pop_front();
        res.push_back(now->hash);
    }
    return res;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    powBase[0] = 1;
    for (int i = 1; i < M; i++) {
        powBase[i] = powBase[i - 1] * BASE;
    }
    string s, t;
    cin >> s;
    cin >> t;
    vector<Hash> ss = solve(s);
    vector<Hash> tt = solve(t);
    // for (auto u : ss) {
    //     u.debug();
    // }
    // cout << endl;
    // for (auto u : tt) {
    //     u.debug();
    // }
    if (ss == tt) cout << "True\n";
    else cout << "False\n"; 
    return 0;
}