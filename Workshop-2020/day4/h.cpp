#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int LOG = 20;

struct SuffixArray {
    int n;
    char *s;
    int sa[N], tmp[N], pos[N];
    int len, cnt[N], lcp[N];
    int lg2[N];

    SuffixArray(char *t) {
        s = t;
        n = strlen(s + 1);
        lg2[1] = 0;
        for (int i = 2; i <= n; i++) {
            lg2[i] = lg2[i >> 1] + 1;
        }
        buildSA();
    }   

    bool cmp(int u, int v) {
        if (pos[u] != pos[v]) return pos[u] < pos[v];
        return u + len <= n && v + len <= n ? pos[u + len] < pos[v + len] : u > v;
    }

    void radix(int delta) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; i++) {
            cnt[i + delta <= n ? pos[i + delta] : 0]++;
        }
        for (int i = 1; i < N; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n; i; i--) {
            int id = sa[i];
            tmp[cnt[id + delta <= n ? pos[id + delta] : 0]--] = id;
        }
        for (int i = 1; i <= n; i++) {
            sa[i] = tmp[i];
        }
    }

    pair<int, int> minVal[LOG][N];

    pair<int, int> rmq(int l, int r) {
        int lg = lg2[r - l + 1];
        return min(minVal[lg][l], minVal[lg][r - (1 << lg) + 1]);
    }

    void buildSA() {
        for (int i = 1; i <= n; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        len = 1;
        while (1) {
            radix(len);
            radix(0);
            tmp[1] = 1;
            for (int i = 2; i <= n; i++) {
                tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
            }
            for (int i = 1; i <= n; i++) {
                pos[sa[i]] = tmp[i];
            }
            if (tmp[n] == n) break;
            len <<= 1;
        }
        len = 0;
        for (int i = 1; i <= n; i++) {
            if (pos[i] == n) continue;
            int j = sa[pos[i] + 1];
            while (s[i + len] == s[j + len]) len++;
            lcp[pos[i]] = len;
            if (len) len--;
        }
        for (int i = 1; i < n; i++) {
            minVal[0][i] = {lcp[i], i};
        }
        for (int i = 1; i < LOG; i++) {
            for (int j = 1; j + (1 << i) - 1 < n; j++) {
                minVal[i][j] = min(minVal[i - 1][j], minVal[i - 1][j + (1 << i - 1)]);
            }
        }
        // for (int i = 1; i <= n; i++) {
        //     cout << lcp[i] << ' ';
        //     for (int j = sa[i]; j <= n; j++) {
        //         cout << s[j];
        //     }
        //     cout << endl;
        // }
    }

    struct Data {
        int res;
        pair<int, int> p1;
        pair<int, int> p2;

        Data() {
            res = N * 10;
            p1 = p2 = {N, -N};
        }
    };

    void update(pair<int, int> &u, int x) {
        u.first = min(u.first, x);
        u.second = max(u.second, x);
    }

    void unite(pair<int, int> &u, pair<int, int> v) {
        u.first = min(u.first, v.first);
        u.second = max(u.second, v.second);
    }

    Data unite(Data &x, Data &y, int u) {
        Data res;
        res.res = min(x.res, y.res);
        res.res = min(res.res, n - 1 - 2 * u + x.p1.first - y.p2.second);
        res.res = min(res.res, n - 1 - 2 * u + x.p2.first - y.p1.second);
        res.res = min(res.res, n - 1 - 2 * u + y.p1.first - x.p2.second);
        res.res = min(res.res, n - 1 - 2 * u + y.p2.first - x.p1.second);
        unite(res.p1, x.p1);
        unite(res.p1, y.p1);
        unite(res.p2, x.p2);
        unite(res.p2, y.p2);
        
        return res;
    }

    Data solve(int l, int r) {
        if (l == r) {
            Data res;
            if (sa[l] <= n / 2) update(res.p1, sa[l]);
            else update(res.p2, sa[l] - n / 2 - 1);
        //     cout << "# " << l << ' ' << r << ' ' << -1 << endl;
        // cout << res.res << endl;
        // cout << res.p1.first << ' ' << res.p1.second << endl;
        // cout << res.p2.first << ' ' << res.p2.second << endl;
            return res;
        }
        auto [u, m] = rmq(l, r - 1);
        Data x = solve(l, m);
        Data y = solve(m + 1, r);
        Data res = unite(x, y, u);
        // cout << "# " << l << ' ' << r << ' ' << m << endl;
        // cout << res.res << endl;
        // cout << res.p1.first << ' ' << res.p1.second << endl;
        // cout << res.p2.first << ' ' << res.p2.second << endl;
        return res;
    }

    int solve() {
        Data now = solve(1, n);
        return now.res; 
    }
};

int n;
char s[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> (s + 1);
    n = strlen(s + 1);
    s[n + 1] = '#';
    cin >> (s + n + 2);
    SuffixArray sa(s);
    int res = sa.solve();
    cout << res << '\n';
    return 0;
}