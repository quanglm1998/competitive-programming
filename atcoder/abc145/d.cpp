#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;
const int N = 2000010;

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

int fac[N];

int binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    return mul(fac[n], inv(mul(fac[k], fac[n - k])));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x, y;
    cin >> x >> y;
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = mul(fac[i - 1], i);
    int res = 0;
    for (int a = 0; a <= x; a++) {
        if ((x - a) & 1) continue;
        int b = (x - a) / 2;
        if (b + 2 * a != y) continue;
        res = add(res, binomial(a + b, a));
    }
    cout << res << endl;
    return 0;
}