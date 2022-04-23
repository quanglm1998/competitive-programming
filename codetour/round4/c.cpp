#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
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

int p[N];
vector<int> primes;

void init() {
    for (int i = 2; i < N; i++) {
        if (!p[i]) {
            primes.push_back(i);
            for (int j = i; j < N; j += i) {
                p[j] = i;
            }
        }
    }
}

vector<int> get(int u) {
    vector<int> res;
    for (int p : primes) {
        int val = u;
        int now = 0;
        while (val)  {
            now += val / p;
            val /= p;
        }
        res.push_back(now);
    }
    return res;
}

vector<int> sub(vector<int> &u, vector<int> &v) {
    vector<int> res;
    for (int i = 0; i < u.size(); i++) {
        res.push_back(u[i] - v[i]);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    init();
    int tc;
    cin >> tc;
    while (tc--) {
        int x, y;
        cin >> x >> y;
        vector<int> yy = get(y);
        vector<int> xx = get(x - 1);
        yy = sub(yy, xx);
        int res = 1;
        for (int u : yy) {
            res = mul(res, u + 1);
        }
        cout << res << endl;
    }
    return 0;
}