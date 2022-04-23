#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}
 
inline int sub(int u, int v) {
    return (u -= v) < 0 ? u + MOD : u;
}
 
inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}
 
inline int power(int u, int v) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u);
        u = mul(u, u);
        v >>= 1;
    }
    return res;
}
 
inline int inv(int u) {
    return power(u, MOD - 2);
}

const int NUM = 6;
int n, k;
vector<int> a[NUM];
map<int, vector<pair<int, int>>> m;

bool check(int x, int y, int z) {
    if (x > 0 && (x == y) || (x == z)) return 0;
    if (y > 0 && y == z) return 0;
    return 1;
}

const int N = NUM * 4;

struct Matrix {
    int a[N][N];
    Matrix(int dia = 0) {
        memset(a, 0, sizeof a);
        for (int i = 0; i < N; i++) a[i][i] = dia;
    }
    int* operator [](int u) {
        return a[u];
    }
};  

Matrix mul(const Matrix &u, const Matrix &v) {
    Matrix res;
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res.a[i][j] = add(res.a[i][j], mul(u.a[i][k], v.a[k][j]));
            }
        }
    }
    return res;
}

Matrix power(Matrix u, int v) {
    Matrix res(1);
    while (v) {
        if (v & 1) res = mul(res, u);
        u = mul(u, u);
        v >>= 1;
    }
    return res;
}

bool ok(int id, int x, int y, int z) {
    if (x && a[id][0] != x) return 0;
    if (y && a[id][1] != y) return 0;
    if (z && a[id][2] != z) return 0;
    return 1;
}

bool can(int flag, int u, int v) {
    if (flag & 1) {
        if (a[v][2] == a[u][1]) return 0;
    }
    if (flag & 2) {
        if (a[v][0] == a[u][1]) return 0;
    }
    return 1;
}

int get(int u, int v) {
    int res = 0;
    if (a[u][0] == a[v][1]) res |= 1;
    if (a[u][2] == a[v][1]) res |= 2;
    return res;
}

int calc(int x, int y, int z) {
    Matrix b;
    for (int i = 0; i < N; i++) {
        int flag = i / 4;
        int id = i % NUM;
        if (!ok(id, x, y, z)) continue;
        for (int j = 0; j < NUM; j++) {
            if (!ok(j, x, y, z)) continue;
            // if (!can(flag, id, j)) continue;
            int f = get(id, j);
            b[i][f * NUM + j]++;
        }
    }
    Matrix a;
    for (int i = 0; i < NUM; i++) {
        if (!ok(i, x, y, z)) continue;
        a[0][i] = 1;
    }
    int last = 1;
    for (auto u : m) {
        if (last < u.first) {
            a = mul(a, power(b, u.first - last));
            last = u.first;
        }
        for (int i = 0; i < N; i++) {
            int id = i % NUM;
            int xx, yy, zz;
            xx = yy = zz = 0;
            for (auto v : u.second) {
                if (v.first == 1) xx = v.second;
                if (v.first == 2) yy = v.second;
                if (v.first == 3) zz = v.second;
                if (!ok(id, xx, yy, zz)) a[0][i] = 0;
            }
        }
        // for (int i = 0; i < N; i++) cout << a[0][i] << ' ';
        //     cout << endl;
    }
    int res = 0;
    for (int i = 0; i < N; i++) {
        res = add(res, a[0][i]);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;    
    vector<int> now(3);
    for (int i = 0; i < 3; i++) now[i] = i + 1;
    int cnt = 0;
    while (1) {
        a[cnt++] = now;
        if (!next_permutation(now.begin(), now.end())) break;
    }
    for (int i = 1; i <= k; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        m[x].push_back({y, c});
    }
    if (!m.count(1)) m[1] = vector<pair<int, int>>();
    if (!m.count(n)) m[n] = vector<pair<int, int>>();
    int res = 0;
    // cout << calc(1, 0, 0) << endl;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            for (int x = 0; x <= 3; x++) {
                if (check(i, j, x)) {
                    int foo = calc(i, j, x);
                    int cnt = 0;
                    cnt += !!i;
                    cnt += !!j;
                    cnt += !!x;
                    if (cnt & 1) res = sub(res, foo);
                    else res = add(res, foo);
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}