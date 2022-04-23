#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MOD[] = {1000000007, 1000000009, rng() % (int)1e6 + 1};
const int NUM = 1;
const int BASE = 10007;

inline int add(int u, int v, int MOD) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int sub(int u, int v, int MOD) {
    return (u -= v) < 0 ? u + MOD : u;
}

inline int mul(int u, int v, int MOD) {
    return (long long)u * v % MOD;
}

inline int power(int u, int v, int MOD) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u, MOD);
        u = mul(u, u, MOD);
        v >>= 1;
    }
    return res;
}

inline int inv(int u, int MOD) {
    return power(u, MOD - 2, MOD);
}

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
};

const int N = 510;
const int L = 1000010;

string a;
string s;
int m;
string l[L];
Hash h[N + L + N];
Hash p[N + L + N];
Hash val[L];
int dp[N];

int can[N][N];

Hash getHash(int l, int r) {
    return h[r] - (h[l] * p[r - l]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> a;

    s = '0';

    cin >> m;
    int maxLen = 0;
    for (int i = 1; i <= m; i++) {
        cin >> l[i];
        maxLen = max(maxLen, (int)l[i].size());
    }
    while (s.size() <= maxLen + a.size() + 1) s += a;
    vector<int> t(s.size());
    t[1] = 0;
    int curT = 0;
    for (int i = 2; i < s.size(); i++) {
        while (curT && s[curT + 1] != s[i]) {
            curT = t[curT];
        }
        
        curT += s[curT + 1] == s[i];
        t[i] = curT;
    }
    int n = s.size() - t.back() - 1;
    h[0] = 0;
    p[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        h[i] = (h[i - 1] * BASE) + s[i];
        p[i] = p[i - 1] * BASE;
    }

    for (int i = 1; i <= m; i++) {
        val[i] = 0;
        for (int j = 0; j < l[i].size(); j++) {
            val[i] = (val[i] * BASE) + l[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) can[i][j] = n + 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            if (getHash(i, i + l[j].size()) == val[j]) {
                can[i][(i + l[j].size()) % n] = 1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                can[i][j] = min(can[i][j], can[i][k] + can[k][j]);
            }
        }
    }

    int res= n + 1;
    for (int i = 0; i < n; i++) res = min(res, can[i][i]);
        if (res < n + 1) cout << res << endl;
    else cout << -1 << endl;
    return 0;   
}