#include <bits/stdc++.h>

using namespace std;

const int N = 2000010;
const int CHAR = 26;

struct AC {
    int cnt;
    int nxt[CHAR][N];
    int tot[N];
    int suf[N];
    vector<int> events[N];
    int res[N];
    AC() {
        cnt = 0;
        memset(nxt, -1, sizeof nxt);
        memset(tot, 0, sizeof tot);
        memset(suf, 0, sizeof suf);
    }
    int add(int cur, char u) {
        if (nxt[u - 'A'][cur] != -1) return nxt[u - 'A'][cur];
        nxt[u - 'A'][cur] = ++cnt;
        return cnt;
    }
    void build() {
        vector<int> q;
        q.push_back(0);
        for (int i = 0; i < q.size(); i++) {
            int u = q[i];
            for (int i = 0; i < CHAR; i++) {
                int v = u == 0 ? 0 : nxt[i][suf[u]];
                if (nxt[i][u] == -1) nxt[i][u] = v;
                else {
                    suf[nxt[i][u]] = v;
                    q.push_back(nxt[i][u]);
                }
            }
        }
        for (int i = (int)q.size() - 1; i >= 0; i--) {
            int u = q[i];
            if (u) tot[suf[u]] += tot[u];
            for (int v : events[u]) res[v] = tot[u];
        }
    }
} ac;
 
int n, k;
int posInAC[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    posInAC[0] = 0;
    for (int i = 1; i <= n; i++) {
        char u;
        int id;
        cin >> u >> id;
        posInAC[i] = ac.add(posInAC[id], u);
        ac.tot[posInAC[i]]++;
    }
    for (int i = 1; i <= k; i++) {
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        int last = 0;
        for (char u : s) {
            last = ac.add(last, u);
        }
        ac.events[last].push_back(i);
    }
    ac.build();
    for (int i = 1; i <= k; i++) {
        cout << ac.res[i] << '\n';
    }
    return 0;
}