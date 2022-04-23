#include <bits/stdc++.h>

using namespace std;

const int N = 14;
const int MOD = 998244353;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

struct custom_hash {
    static uint32_t splitmix(uint32_t x) {
        // x += 0x7f4a7c15;
        // x = (x ^ (x >> 15)) * 0x1ce4e5b9;
        // x = (x ^ (x >> 12)) * 0x133111eb;
        // return x ^ (x >> 16);
        return x;
    }

    size_t operator()(uint32_t x) const {
        static const uint32_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix(x + FIXED_RANDOM);
    }
};

int n, m;
vector<int> adj[N];
// unordered_map<int, int, custom_hash> ff, gg, hh;
int ff[N][1 << N], gg[N][1 << N];
int hh[N][N][1 << N];
int a[N][N];

int f(int u, int mask);
int g(int u, int mask);
int h(int u, int v, int mask);

// inline int encode(int u, int mask) {
//     return u << n | mask;
// }

// inline int encode(int u, int v, int mask) {
//     return u << n + 4 | v << n | mask;
// }

int f(int u, int mask) {
    // assert(!(mask >> u & 1));
    if (mask == 0) return 1;
    // int uu = encode(u, mask);
    // if (ff.find(uu) != ff.end()) return ff[uu];
    if (ff[u][mask] != -1) return ff[u][mask];
    int v = __builtin_ctz(mask);
    mask ^= (1 << v);
    int res = 0;
    for (int subMask = mask; ; subMask = (subMask - 1) & mask) {
        int otherMask = mask ^ subMask ^ (1 << v);
        addTo(res, mul(f(u, subMask), g(u, otherMask)));
        if (!subMask) break;
    }
    mask ^= (1 << v);
    // ff[uu] = res;
    ff[u][mask] = res;
    // cout << "F " << u << ' ' << mask << ' ' << res << endl;
    return res;
}

int g(int u, int mask) {
    // assert(!(mask >> u & 1));
    if (mask == 0) return 1;
    // int uu = encode(u, mask);
    // if (gg.find(uu) != gg.end()) return gg[uu];
    if (gg[u][mask] != -1) return gg[u][mask];
    int res = 0;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if ((mask >> v & 1) == 0) continue;
        addTo(res, f(v, mask ^ (1 << v)));
        for (int j = i + 1; j < adj[u].size(); j++) {
            int w = adj[u][j];
            if ((mask >> w & 1) == 0) continue;
            addTo(res, h(v, w, mask ^ (1 << v) ^ (1 << w)));
        }
    }
    // gg[uu] = res;
    gg[u][mask] = res;
    // cout << "G " << u << ' ' << mask << ' ' << res << endl;
    return res;
}

int h(int u, int v, int mask) {
    // assert(!(mask >> u & 1));
    // assert(!(mask >> v & 1));
    if (u > v) return h(v, u, mask);
    if (mask == 0) {
        return a[u][v];
    }
    // int uuvv = encode(u, v, mask);
    // if (hh.find(uuvv) != hh.end()) return hh[uuvv];
    if (hh[u][v][mask] != -1) return hh[u][v][mask];
    int res = 0;
    if (a[u][v]) {
        for (int subMask = mask; ; subMask = (subMask - 1) & mask) {    
            addTo(res, mul(f(u, subMask), f(v, mask ^ subMask)));
            if (!subMask) break;
        }
    }
    for (int w : adj[v]) {
        if (w == u) continue;
        if ((mask >> w & 1) == 0) continue;
        mask ^= (1 << w);
        for (int subMask = mask; ; subMask = (subMask - 1) & mask) {
            addTo(res, mul(h(u, w, subMask), f(v, mask ^ subMask)));
            if (!subMask) break;
        }
        mask ^= (1 << w);
    }
    // hh[uuvv] = res;
    hh[u][v][mask] = res;
    // cout << "H " << u << ' ' << v << ' ' << mask << ' ' << res << endl;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    // n = 13;
    // m = 13 * 12 / 2;
    // for (int i = 0; i < n; i++) {
    //     for (int j = i + 1; j < n; j++) {
    //         adj[i].push_back(j);
    //         adj[j].push_back(i);
    //         a[i][j] = a[j][i] = 1;
    //     }
    // }
    for (int i = 0; i < N; i++) {
        memset(ff[i], -1, sizeof ff[i]);
        memset(gg[i], -1, sizeof gg[i]);
        for (int j = 0; j < N; j++) {
            memset(hh[i][j], -1, sizeof hh[i][j]);
        }
    }
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        a[u][v] = a[v][u] = 1;
    }
    cout << f(0, (1 << n) - 2) << '\n';
    return 0;
}