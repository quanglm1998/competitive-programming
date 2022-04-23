#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 20;
const int INF = 1e9;
const int MOD = 1e9 + 7;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void addTo(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void subTo(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mulTo(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

struct Data {
    int maxVal, sum, num;
};

int n, m;
int a[N];
Data dp[LOG][N];
int p2[N];

Data solve(int l, int lg) {
    if (lg > m) {
        return {-INF, 0, 0};
    }
    if (l > n) {
        return {0, 0, p2[m - lg + 1]};
    }
    if ((1 << lg - 1) > n) {
        int maxVal = a[l] >= lg;
        int sum = 0;
        if (a[l] >= lg) {
            sum = p2[m - a[l]];
        }
        int num = sub(p2[m - lg + 1], 1);
        return {maxVal, sum, num};
    }
    if (dp[lg][l].maxVal != -1) return dp[lg][l];
    
    // first to LG
    int now = 0;
    for (int i = l; i <= n; i += (1 << lg)) {
        now += a[i] == lg;
    }
    Data p1 = solve(l + (1 << lg - 1), lg + 1);
    p1.maxVal += now;
    addTo(p1.sum, mul(p1.num, now));

    // first not to LG
    now = 0;
    for (int i = l + (1 << lg - 1); i <= n; i += (1 << lg)) {
        now += a[i] == lg;
    }
    Data p2 = solve(l, lg + 1);
    p2.maxVal += now;
    addTo(p2.sum, mul(p2.num, now));

    Data &res = dp[lg][l];
    res.maxVal = max(p1.maxVal, p2.maxVal);
    res.sum = add(p1.sum, p2.sum);
    res.num = add(p1.num, p2.num);
    // cout << "solve " << l << ' ' << lg << endl;
    // cout << res.maxVal << ' ' << res.sum << ' ' << res.num << endl;
    // cout << p1.maxVal << ' ' << p1.sum << ' ' << p1.num << endl;
    // cout << p2.maxVal << ' ' << p2.sum << ' ' << p2.num << endl;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    p2[0] = 1;
    for (int i = 1; i < N; i++) p2[i] = mul(p2[i - 1], 2);
    while (cin >> n >> m) {
        // init
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < LOG; j++) {
                dp[j][i] = {-1, -1, -1};
            }
        }

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        } 

        Data foo = solve(1, 1);

        int now = sub(p2[m], 1);
        subTo(now, n);
        addTo(now, 1);
        mulTo(now, n);
        subTo(now, foo.sum);
        cout << n - foo.maxVal << ' ' << now << '\n';
    }
    return 0;
}