#include <bits/stdc++.h>

using namespace std;

bool isAlpha(char u) {
    return (u >= 'a' && u <= 'z') || (u >= 'A' && u <= 'Z');
}

const int N = 2000010;

#include <bits/stdc++.h>

using namespace std;

struct SuffixArray {
    int n;
    char *s;
    int sa[N], tmp[N], pos[N];
    int len, cnt[N], lcp[N];

    SuffixArray(char *t) {
        s = t;
        n = strlen(s + 1);
        buildSA();
    }

    bool cmp(int u, int v) {
        if (pos[u] != pos[v]) {
            return pos[u] < pos[v];
        }
        return (u + len <= n && v + len <= n) ? pos[u + len] < pos[v + len] : u > v;
    }

    void radix(int delta) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; i++) {
            cnt[i + delta <= n ? pos[i + delta] : 0]++;
        }
        for (int i = 1; i < N; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n; i > 0; i--) {
            int id = sa[i];
            tmp[cnt[id + delta <= n ? pos[id + delta] : 0]--] = id;
        }
        for (int i = 1; i <= n; i++) {
            sa[i] = tmp[i];
        }
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
    }
};

int tt[N];
char ss[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    string s, t;
    cin >> n;
    s = t = "";
    getline(cin, s);
    while (s.size() < n) {
        string foo;
        getline(cin, foo);
        s += foo;
    }
    while (t.size() < n) {
        string foo;
        getline(cin, foo);
        t += foo;
    }
    string foo = "Q";
    for (int i = 0; i < n; i++) {
        if (isAlpha(s[i])) {
            int now = (t[i] - s[i] + 26 + 25) % 26;
            foo += (char)(now + 'a');
        }
    }
    n = foo.size() - 1;
    tt[1] = 0;
    int cur = 0;
    for (int i = 2; i <= n; i++) {
        while (cur && foo[i] != foo[cur + 1]) cur = tt[cur];
        cur += foo[i] == foo[cur + 1];
        tt[i] = cur;
    }
    foo.resize(n - tt[n] + 1);
    for (int i = 1; i < foo.size(); i++) {
        ss[i] = foo[i];
    }
    n = strlen(ss + 1);
    for (int i = 1; i <= n; i++) {
        ss[i + n] = ss[i];
    }
    int res = 1;
    int l = 1;
    while (l <= n) {
        res = l;
        int r = l + 1;
        int k = l;
        while (r <= n * 2 && ss[r] >= ss[k]) {
            if (ss[r] == ss[k]) k++;
            else k = l;
            r++;
        }
        while (l <= k) l += r - k;
    }
    for (int i = 0; i < n; i++) cout << ss[res + i];
        cout << endl;
    return 0;   
}