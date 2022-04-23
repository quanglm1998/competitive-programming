#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int lg[N];

struct SuffixArray {
    static const int N = 100010;
    static const int LOG = 20;

    int n;
    char *s;
    int sa[N], tmp[N], pos[N];
    int len, cnt[N], lcp[N];
    int rmq[LOG][N];

    SuffixArray() {
    }

    void init(char *t, int n) {
        s = t;
        this->n = n;
        buildSA();
    }

    bool cmp(int u, int v) {
        if (pos[u] != pos[v]) {
            return pos[u] < pos[v];
        }
        return (u + len <= n && v + len <= n) ? pos[u + len] < pos[v + len] : u > v;
    }

    // void radix(int delta) {
    //     memset(cnt, 0, sizeof cnt);
    //     for (int i = 1; i <= n; i++) {
    //         cnt[i + delta <= n ? pos[i + delta] : 0]++;
    //     }
    //     for (int i = 1; i < N; i++) {
    //         cnt[i] += cnt[i - 1];
    //     }
    //     for (int i = n; i > 0; i--) {
    //         int id = sa[i];
    //         tmp[cnt[id + delta <= n ? pos[id + delta] : 0]--] = id;
    //     }
    //     for (int i = 1; i <= n; i++) {
    //         sa[i] = tmp[i];
    //     }
    // }

    void buildSA() {
        for (int i = 1; i <= n; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        len = 1;
        while (1) {
            // radix(len);
            // radix(0);
            sort(sa + 1, sa + n + 1, [&](int u, int v) {
                if (pos[u] != pos[v]) {
                    return pos[u] < pos[v];
                }
                return (u + len <= n && v + len <= n) ? pos[u + len] < pos[v + len] : u > v;
            });
            tmp[1] = 1;
            for (int i = 2; i <= n; i++) {
                tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
            }
            for (int i = 1; i <= n; i++) {
                pos[sa[i]] = tmp[i];
            }
            if (tmp[n] == n) {
                break;
            }
            len <<= 1;
        }

        len = 0;
        for (int i = 1; i <= n; i++) {
            if (pos[i] == n) {
                continue;
            }
            int j = sa[pos[i] + 1];
            while (s[i + len] == s[j + len]) {
                len++;
            }
            lcp[pos[i]] = len;
            if (len) {
                len--;
            }
        }

        for (int i = 1; i < n; i++) {
            rmq[0][i] = lcp[i];
        }
        for (int i = 1; i < LOG; i++) {
            for (int j = 1; j + (1 << i) - 1 < n; j++) {
                rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << i - 1)]);
            }
        }
    }

    int getMin(int l, int r) {
        r--;
        int lg2 = lg[r - l + 1];
        return min(rmq[lg2][l], rmq[lg2][r - (1 << lg2) + 1]);
    }
} sa;

int n;
char s[N];
int res[N];

bool isSmaller(int u, int v, int w) {
    int posU = sa.pos[u];
    int posV = sa.pos[v];
    if (posU > posV) return 0;
    int lcp = sa.getMin(posU, posV);
    if (lcp < w - v + 1) return 1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;

    lg[1] = 0;
    for (int i = 1; i < N; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    while (tc--) {
        cin >> n;   
        cin >> (s + 1);
        sa.init(s, n);
        vector<pair<int, int>> st;
        for (int i = n; i >= 1; i--) {
            int cur = i;
            while (!st.empty() && isSmaller(i, st.back().first, st.back().second)) {
                cur = st.back().second;
                st.pop_back();
            }  
            res[i] = cur - i + 1;
            st.push_back({i, cur});
        }
        for (int i = 1; i <= n; i++) cout << res[i] << ' ';
            cout << '\n';
    }   
    return 0;
}