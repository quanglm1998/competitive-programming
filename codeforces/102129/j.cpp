#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;
const int N = 3010;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

int n, m;
char s[N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        cin >> (a[i] + 1);
    }
    
    return 0;
}