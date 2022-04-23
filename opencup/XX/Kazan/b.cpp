#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
const int MOD = 998244353;
const int LOG = 60;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

int n;
long long x;

struct Trie {
    int sz[N * LOG];
    int children[2][N * LOG];
    int numNode;

    Trie() {
        numNode = 1;
        children[0][0] = children[1][0] = 0;
    }

    int add(long long u, long long x) {
        int res = 1;
        int curNode = 1;
        for (int i = LOG - 1; i >= 0 && curNode; i--) {
            int xx = x >> i & 1;
            int uu = u >> i & 1;
            if (xx) {
                curNode = children[uu ^ 1][curNode];
            } else {    
                addTo(res, children[uu ^ 1][curNode] ? sz[children[uu ^ 1][curNode]] : 0);
                curNode = children[uu][curNode];
            }
        }
        if (curNode) addTo(res, sz[curNode]);
        curNode = 1;
        for (int i = LOG - 1; i >= 0; i--) {
            int uu = u >> i & 1;
            if (!children[uu][curNode]) {
                children[uu][curNode] = ++numNode;
                sz[numNode] = 0;
                children[0][numNode] = children[1][numNode] = 0;
            }
            addTo(sz[curNode], res);
            curNode = children[uu][curNode];
        }
        addTo(sz[curNode], res);
        return res;
    }
} t;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> x;
    vector<long long > a(n);
    for (long long &u : a) cin >> u;
    sort(a.begin(), a.end());
    int res = 0;
    for (long long u : a) addTo(res, t.add(u, x));
    cout << res << endl;
    return 0;
}