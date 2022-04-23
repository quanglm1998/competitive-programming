#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void addTo(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void subTo(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mulTo(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

const int N = 400;

int n, m;
int a[N][N];
vector<int> adj[N];
int order[N][N];
int res[N][N];
int used[N];
int go[N];

int check(int u, int v, int x) {
    int res = 0;
    for (int w : adj[x]) {
        if (a[u][w] + 1 == a[u][x] && a[v][w] + 1 == a[v][x]) {
            res++;
        }
    }
    return res;
}

int calc_diff(int u, int v) {
    memset(used, 0, sizeof used);
    memset(go, 0, sizeof go);
    int connected = 0;
    used[u] = used[v] = 1;
    int uPoint = 2;
    int vPoint = 2;
    int res = 1;
    while (uPoint <= n || vPoint <= n) {
        if (a[u][order[u][uPoint]] < a[v][order[v][vPoint]]) {
            int num = 0;
            int x = order[u][uPoint];
            if (go[x]) {
                uPoint++;
                continue;
            }
            if (int foo = check(u, v, x)) {
                uPoint++;
                go[x] = 1;
                mulTo(res, foo);
                continue;
            }
            for (int w : adj[x]) {
                if (a[u][w] + 1 == a[u][x] ) {
                    num++;        
                }
            }
            if (used[x]) {
                if (!connected) connected = 1;
                else {
                    num = 0;
                }
            }
            used[x] = 1;
            uPoint++;
            mulTo(res, num);
        } else {
            int num = 0;
            int x = order[v][vPoint];
            if (go[x]) {
                vPoint++;
                continue;
            }
            if (int foo = check(u, v, x)) {
                vPoint++;
                go[x] = 1;
                mulTo(res, foo);
                continue;
            }

            for (int w : adj[x]) {
                if (a[v][w] + 1 == a[v][x]) {
                    num++;        
                }
            }
            if (used[x]) {
                if (!connected) connected = 1;
                else {
                    num = 0;
                }
            }
            used[x] = 1;
            vPoint++;
            mulTo(res, num);
        }
    }
    return res;
}

int calc_same(int u) {
    int res = 1;
    for (int i = 2; i <= n; i++) {
        int v = order[u][i];
        int num = 0;
        for (int w : adj[v]) {
            if (a[u][w] + 1 == a[u][v]) num++;
        }
        mulTo(res, num);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = (i == j ? 0 : 1e9);
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i][n + 1] = 1e9;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        iota(order[i] + 1, order[i] + n + 2, 1);
        sort(order[i] + 1, order[i] + n + 1, [&](int u, int v) {
            return a[i][u] < a[i][v];
        });
    }
        
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            res[i][j] = res[j][i] = calc_diff(i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        res[i][i] = calc_same(i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << res[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}