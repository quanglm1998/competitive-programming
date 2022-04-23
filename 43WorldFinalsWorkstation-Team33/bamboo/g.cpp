#include <bits/stdc++.h>

using namespace std;

const int N = 2000010;
const int LOG = 22;
const int MOD1 = 1000000007;
const int MOD2 = 1000000009;
const int BASE = 1000000003;

inline int add(int u, int v, int MOD) {
    return (u + v) % MOD;
}

inline int sub(int u, int v, int MOD) {
    return (u - v + MOD) % MOD;
}

inline int mul(int u, int v, int MOD) {
    return (long long)u * v % MOD;
}

struct Hash {
    int h1, h2;
    Hash(int h1 = 0, int h2 = 0) : h1(h1), h2(h2) {}
    Hash operator + (const Hash &u) const {
        return {add(h1, u.h1, MOD1), add(h2, u.h2, MOD2)};
    }
    Hash operator - (const Hash &u) const {
        return {sub(h1, u.h1, MOD1), sub(h2, u.h2, MOD2)};
    }
    Hash operator * (const Hash &u) const {
        return {mul(h1, u.h1, MOD1), mul(h2, u.h2, MOD2)};
    }
    bool operator == (const Hash &u) const {
        return h1 == u.h1 && h2 == u.h2;
    }
};

int n, k;
vector<int> adj[N];
char a[N];
int query[N];
int lv[N], par[LOG][N];
bool used[N];
int cur;
int sa[N], pos[N], tmp[N];
int len;
int cnt[N];
int isReal[N];
Hash h[N];
Hash p[N];
int lcp[LOG][N];

void dfs(int u, int p) {
    used[u] = 1;
    lv[u] = lv[p] + 1;
    h[u] = h[p] * Hash(BASE, BASE);
    h[u] = h[u] + Hash(a[u], a[u]);
    par[0][u] = p;
    for (int i = 1; i < LOG; i++) par[i][u] = par[i - 1][par[i - 1][u]];
    for (int v : adj[u]) {
        dfs(v, u);
    }
}

inline bool cmp(int u, int v) {
    if (pos[u] != pos[v]) return pos[u] < pos[v];
    int uu = par[len][u];
    int vv = par[len][v];
    if (uu > 0 && vv > 0) return pos[uu] < pos[vv];
    if (lv[u] != lv[v]) return lv[u] < lv[v];
    return u > v;
}

void radix(int delta) {
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= cur; i++) {
        cnt[par[delta][i] != 0 ? pos[par[delta][i]] : 0]++;
    }
    for (int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= cur; i++) {
        int id = sa[i];
        tmp[cnt[par[delta][id] != 0 ? pos[par[delta][id]] : 0]--] = id;
    }
    for (int i = 1; i <= cur; i++) sa[i] = tmp[i];
}

Hash getHash(int u, int v) {
    return h[u] - (h[v] * p[lv[u] - lv[v]]);
}

int get(int u, int v) {
    int res = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        int uu = par[i][u];
        int vv = par[i][v];
        if (uu == 0 || vv == 0) continue;
        Hash hu = getHash(u, uu);
        Hash hv = getHash(v, vv);
        if (hu == hv) {
            res |= (1 << i);
            u = uu;
            v = vv;
        }
    }
    return res;
}

int sum[N];
int lg2[N];

int getRMQ(int l, int r) {
    int lg = log2(r - l + 1);
    return min(lcp[lg][l], lcp[lg][r - (1 << lg) + 1]);
}

void buildSA() {
    for (int i = 1; i <= cur; i++) {
        sa[i] = i;
        pos[i] = a[i];
    }
    for (len = 1; len <= 20; len++) {
//        radix(len);
//        radix(0);
//        cout << len << endl;
        sort(sa + 1, sa + cur + 1, cmp);
//        cout << "done" << endl;
        tmp[1] = 1;
        for (int i = 2; i <= cur; i++) {
            tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
        }
        for (int i = 1; i <= cur; i++) {
            pos[sa[i]] = tmp[i];
        }
//        if (tmp[cur] == cur) break;
    }
    for (int i = 1; i < cur; i++) {
        lcp[0][i] = get(sa[i], sa[i + 1]);
    }
//    for (int i = 1; i < cur; i++) cout << lcp[0][i] << ' ';
//    cout << en
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j + (1 << i) - 1 <= cur; j++) {
            lcp[i][j] = min(lcp[i - 1][j], lcp[i - 1][j + (1 << (i - 1))]);
        }
    }
    for (int i = 1; i <= cur; i++) {
        sum[i] = sum[i - 1] + isReal[sa[i]];
    }
}

int sz[N];

int  getL(int now, int sz) {
    int low = 0, high = now;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (getRMQ(mid, now - 1) >= sz) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return high;
}


int  getR(int now, int sz) {
    int low = now, high = cur + 1;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (getRMQ(now, mid - 1) >= sz) {
            low = mid;
        } else {
            high = mid;
        }
    }
    return low;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> a[i] >> u;
        if (u) adj[u].push_back(i);
        isReal[i] = 1;
    }

    p[0] = {1, 1};
    for (int i = 1; i < N; i++) p[i] = p[i - 1] * Hash(BASE, BASE);
    lg2[1] = 0;
    for (int i = 1; i < N; i++) lg2[i] = lg2[i >> 1] + 1;
    cur = n;
    for (int i = 1; i <= k; i++) {
        string s;
        cin >> s;
        sz[i] = s.size();
        reverse(s.begin(), s.end());
        a[++cur] = s[0];
        for (int i = 1; i < s.size(); i++) {
            a[++cur] = s[i];
            adj[cur - 1].push_back(cur);
        }
        query[i] = cur;
    }
//    for (int i = 1; i <= cur; i++) cout << a[i] << ' ';
//    cout << endl;
    for (int i = 1; i <= cur; i++) {
        if (!used[i]) dfs(i, 0);
    }
    buildSA();
    for (int i = 1; i <= k; i++) {
        int now = pos[query[i]];
        int l = getL(now, sz[i]);
        int r = getR(now, sz[i]);
        cout << l << ' ' << r << endl;
        cout << sum[r] - sum[l - 1] << endl;
    }
    return 0;
}