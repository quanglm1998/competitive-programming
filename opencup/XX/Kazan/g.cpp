#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
const int MOD = 998244353;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

int n;
char s[N];
int fac[N], invFac[N];
vector<int> ls[N];
int cnt[N];

int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return mul(fac[n], mul(invFac[k], invFac[n - k]));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = mul(fac[i - 1], i);
    invFac[N - 1] = inv(fac[N - 1]);
    for (int i = N - 2; i >= 0; i--) invFac[i] = mul(invFac[i + 1], i + 1);

    cin >> (s + 1);
    n = strlen(s + 1);
    for (int l = 1, r = 1; l <= n; l = r) {
        while (r <= n && s[l] == s[r]) r++;
        addTo(cnt[r - l], comb(n - r + l, l - 1));
        if (l > 1) ls[r - l].push_back(l - 2);
        if (r <= n) ls[r - l].push_back(n - r);
    }  
    int res = 0;
    int cur = 0;
    int needSub = 0;
    vector<int> subs;
    for (int i = n; i; i--) {
        if (i == n) cur = 1;
        else cur = sub(mul(cur, 2), needSub);   
        addTo(res, cur);
        addTo(needSub, cnt[i]);
        for (int u : subs) addTo(needSub, comb(n - i - 1, u));
        for (int u : ls[i]) subs.push_back(u);
    }
    cout << res << endl;
    return 0;   
}