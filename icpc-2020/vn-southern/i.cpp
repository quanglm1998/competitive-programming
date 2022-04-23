#include <bits/stdc++.h>

using namespace std;

// make sure that BASE > maxValue
const int BASE = 10007;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int NUM = 3;
const int MOD[NUM] = {1000000007, 1000000009, 998224353};

inline int add(int u, int v, int MOD) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v, int MOD) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v, int MOD) {return (long long)u * v % MOD;}
inline int power(int u, int v, int MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, MOD)) if (v & 1) res = mul(res, u, MOD); return res;}
inline int inv(int u, int MOD) {return power(u, MOD - 2, MOD);}
inline void addTo(int &u, int v, int MOD) {u = add(u, v, MOD);}
inline void subTo(int &u, int v, int MOD) {u = sub(u, v, MOD);}
inline void mulTo(int &u, int v, int MOD) {u = mul(u, v, MOD);}

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
    void debug() {
        for (int i = 0; i < NUM; i++) cout << a[i] << ' ';
            cout << endl;
    }
};

const int S = 200010;
const int P = 210; 

int n, m;
char p[P];
char s[S];
Hash hp[P], hs[S], powP[S];

int len[P];
int curPos[P];
vector<pair<int, Hash>> ls;
int needFirst, needLast;

Hash getHash(Hash *a, int l, int r) {
    return a[r] - (a[l - 1] * powP[r - l + 1]);
}

bool check(int id, int pos) {
    int u = ls[id].first;
    if (pos + len[id] - 1 > m * 2) return 0;
    Hash now = getHash(hs, pos, pos + len[id] - 1);
    return now == ls[id].second;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> (p + 1);
    cin >> (s + 1);
    n = strlen(p + 1);
    m = strlen(s + 1);

    for (int i = 1; i <= m; i++) {
        s[i + m] = s[i];
    }

    powP[0] = 1;
    for (int i = 1; i <= m * 2; i++) {
        powP[i] = powP[i - 1] * BASE;
    }
    hs[0] = 0;
    for (int i = 1; i <= m * 2; i++) {
        hs[i] = (hs[i - 1] * BASE) + s[i];
    }

    int pos = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] == '*') {
            pos = i;
            break;
        }
    }

    if (pos == 0) {
        if (n != m) {
            cout << 0 << endl;
            return 0;
        }
        int res = 0;
        for (int i = 0; i < n; i++) {   
            int cur = 1;
            while (cur <= n && p[cur] == s[cur]) cur++;
            res += (cur == n + 1);
            rotate(p + 1, p + 2, p + n + 1);
        }
        cout << res << '\n';
        return 0;
    }

    hp[0] = 0;
    for (int i = 1; i <= n; i++) {
        hp[i] = (hp[i - 1] * BASE) + p[i];
    }
    
    p[0] = '*';
    needFirst = needLast = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] != '*' && p[i - 1] == '*') {
            int cur = i;
            while (cur + 1 <= n && p[cur + 1] != '*') cur++;
            len[ls.size()] = cur - i + 1;
            ls.push_back({i, getHash(hp, i, cur)});
            if (i == 1) needFirst = 1;
            if (cur == n) needLast = 1;
        }
    }   
    for (int i = 0; i < ls.size(); i++) {
        curPos[i] = 1;
    }
    int res = 0;
    for (int start = 1; start <= m; start++) {
        int now = start;
        for (int i = 0; i < ls.size(); i++) {
            while (curPos[i] <= m * 2 && (curPos[i] < now || !check(i, curPos[i]))) {
                curPos[i]++;
            }
            now = curPos[i] + len[i];
        }
        if (now > start + m) continue;
        int can = 1;
        if (needFirst) can &= (curPos[0] == start);
        if (needLast) can &= check(ls.size() - 1, start + m - 1 - len[ls.size() - 1] + 1);
        res += can;
    }
    cout << res << endl;
    return 0;
}