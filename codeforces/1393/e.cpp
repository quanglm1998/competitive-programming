#include <bits/stdc++.h>

using namespace std;

const int N = 1100010;
const int MOD = 1000000007;
const int LOG = 22;

inline int add(int u, int v, int MOD = MOD) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int sub(int u, int v, int MOD = MOD) {
    return (u -= v) < 0 ? u + MOD : u;
}

inline int mul(int u, int v, int MOD = MOD) {
    return (long long)u * v % MOD;
}

inline int power(int u, int v, int MOD = MOD) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u, MOD);
        u = mul(u, u, MOD);
        v >>= 1;
    }
    return res;
}

inline int inv(int u, int MOD = MOD) {
    return power(u, MOD - 2, MOD);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int NUM = 3;
const int MODS[NUM] = {1000000007, 1000000009, 998244353};
const int BASE = 10007;

struct Hash {
    int a[NUM];
    Hash(int u = 0) {
        for (int i = 0; i < NUM; i++) {
            a[i] = u % MODS[i];
        }
    }
    Hash operator + (const Hash &u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = add(a[i], u.a[i], MODS[i]);
        }
        return res;
    }
    Hash operator - (const Hash &u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = sub(a[i], u.a[i], MODS[i]);
        }
        return res;
    }
    Hash operator * (const int u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = mul(a[i], u, MODS[i]);
        }
        return res;
    }
    Hash operator * (const Hash &u) const {
        Hash res(0);
        for (int i = 0; i < NUM; i++) {
            res.a[i] = mul(a[i], u.a[i], MODS[i]);
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


int n;
Hash powerOfBase[N];
vector<Hash> h[N];
vector<int> orders[N];
int len[N];
string a[N];
Hash invBase;

Hash getHash(int u, int pos, int l) {
    if (l < pos) return h[u][l];
    l++;
    Hash res = 0;
    if (pos > 0) res = h[u][pos - 1];
    Hash now = (h[u][l] - h[u][pos]) * invBase;
    return res + now;
}

bool smallerOrEqual(int u, int posU, int v, int posV) {
    int lenU = len[u] - (posU != len[u]);
    int lenV = len[v] - (posV != len[v]);
    int lenMin = min(lenU, lenV);
    int low = -1, high = lenMin;
    while (high - low > 1) {
        int mid = low + high >> 1;
        Hash h1 = getHash(u, posU, mid);
        Hash h2 = getHash(v, posV, mid);
        if (h1 == h2) low = mid;
        else high = mid;
    }
    // cout << getHash(u, posU, 0) << endl;
    // cout << getHash(v, posV, 0) << endl;
    int uu = low + 1 + (posU <= low + 1);
    int vv = low + 1 + (posV <= low + 1);
    if (uu >= len[u]) return 1;
    if (vv >= len[v]) return 0;
    return a[u][uu] < a[v][vv];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    for (int i = 0; i < NUM; i++) {
        invBase.a[i] = inv(BASE, MODS[i]);
    }

    powerOfBase[0] = 1;
    for (int i = 1; i < N; i++) {
        powerOfBase[i] = powerOfBase[i - 1] * BASE;
    }

    cin >> n;

    vector<pair<int, int>> last;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        a[i] = s;
        len[i] = s.size();
        s += (char)('a' - 1);
        vector<int> nxt(len[i]);
        nxt.back() = len[i];
        for (int j = len[i] - 2; j >= 0; j--) {
            if (s[j] == s[j + 1]) nxt[j] = nxt[j + 1];
            else nxt[j] = j + 1;
        }
        orders[i].assign(len[i] + 1, 0);
        int l = 0, r = len[i];
        for (int j = 0; j < len[i]; j++) {
            if (s[j] < s[nxt[j]]) {
                orders[i][r--] = j;
            } else {
                orders[i][l++] = j;
            }
        }
        orders[i][l] = len[i];
        
        h[i].assign(len[i], 0);
        for (int j = 0; j < len[i]; j++) {
            if (j > 0) h[i][j] = h[i][j - 1];
            h[i][j] = h[i][j] + (powerOfBase[j] * (int)s[j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        vector<pair<int, int>> now;
        if (i == 1) {
            for (int j = 0; j <= len[i]; j++) {
                now.push_back({orders[i][j], 1});
            }    
        } else {
            int cur = 0;
            int sum = 0;
            for (int j = 0; j <= len[i]; j++) {
                while (cur < last.size() && smallerOrEqual(i - 1, last[cur].first, i, orders[i][j])) {
                    sum = add(sum, last[cur].second);
                    cur++;
                }
                now.push_back({orders[i][j], sum});
            }
        }
        last.swap(now);
        // cout << "# " << i << endl;
        // for (auto u : last) cout << u.first << ' ' << u.second << endl;
    }

    int res = 0;
    for (auto u : last) res = add(res, u.second);
    cout << res << endl;
    return 0;
}