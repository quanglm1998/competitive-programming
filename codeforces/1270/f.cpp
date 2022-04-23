#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int sum[N];

struct SuffixAutomaton {
    static const int N = 200100;
    static const int CHARACTER = 2;
    int suf[N * 2], nxt[N * 2][CHARACTER], cnt, last, len[N * 2];
    vector<int> adj[N * 2];
    int ter[N * 2];
    int ending[N * 2];

    SuffixAutomaton() {
        memset(suf, -1, sizeof suf);
        memset(nxt, -1, sizeof nxt);
        memset(len, 0, sizeof len);
        last = cnt = 0;
    }

    int getNode(int last, int u) {
        int q = nxt[last][u];
        if (len[last] + 1 == len[q]) {
            return q;
        }
        int clone = ++cnt;
        len[clone] = len[last] + 1;
        for (int i = 0; i < CHARACTER; i++) {
            nxt[clone][i] = nxt[q][i];
        }
        while (last != -1 && nxt[last][u] == q) {
            nxt[last][u] = clone;
            last = suf[last];
        }
        suf[clone] = suf[q];
        return suf[q] = clone;
    }

    void add(int u, int pos) {
        if (nxt[last][u] == -1) {
            int newNode = ++cnt;
            ending[newNode] = pos;
            ter[newNode] = 1;
            len[newNode] = len[last] + 1;
            while (last != -1 && nxt[last][u] == -1) {
                nxt[last][u] = newNode;
                last = suf[last];
            }
            if (last == -1) {
                suf[newNode] = 0;
                last = newNode;
                return;
            }
            suf[newNode] = getNode(last, u);
            last = newNode;
        } else {
            last = getNode(last, u);
        }
    }

    long long dp[N * 2];

    void dfs(int u) {
        for (int v : adj[u]) {
            dfs(v);
            ter[u] += ter[v];
            ending[u] = max(ending[u], ending[v]);
        }
        if (u == 0) return;
        for (int l = len[u]; l > len[suf[u]]; l--) {
            int rr = ending[u];
            int ll = ending[u] - l;
            assert(ll >= 0);
            if (sum[rr] != sum[ll] && l % (sum[rr] - sum[ll]) == 0) dp[u]++;
        }
    }

    long long calc() {
        for (int i = 0; i <= cnt; i++) {
            if (suf[i] != -1) {
                adj[suf[i]].push_back(i);
            }
        }
        dfs(0);
        long long res = 0;
        for (int i = 1; i <= cnt; i++) {
            res += dp[i] * ter[i];
        }
        return res;
    }
} sa;

int n;
char s[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        sa.add(s[i] - '0', i);
        sum[i] = sum[i - 1] + (s[i] == '1');
    }
    cout << sa.calc() << endl;
    return 0;
}