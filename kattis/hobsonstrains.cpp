#include <bits/stdc++.h>

using namespace std;

const int N = 500010;
const int LOG = 21;

int n, k;
int nxt[LOG][N];
int res[N];
vector<int> circle[N];
int numCircle;
int used[N];
int inCircle[N];
int num[N];
vector<int> ranges[N];
int deg[N];

void init(int root) {
    vector<int> ls;
    ls.push_back(root);
    num[root] = 0;
    for (int i = 0; i < ls.size(); i++) {
        int u = ls[i];
        int v = nxt[0][u];
        if (used[v]) break;
        if (num[v] != -1) {
            numCircle++;
            for (int j = num[v]; j < ls.size(); j++) {
                circle[numCircle].push_back(ls[j]);
                inCircle[ls[j]] = 1;
            }
            break;
        }
        num[v] = ls.size();
        ls.push_back(v);
    }
    for (int u : ls) used[u] = 1;
}

int getNext(int u, int k) {
    for (int i = LOG - 1; i >= 0; i--) if (k >> i & 1) u = nxt[i][u];
        return u;
}

void add(int u) {
    int len = 0, v = u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (!inCircle[nxt[i][v]]) {
            len |= (1 << i);
            v = nxt[i][v];
        }
    }
    len = k - len - 1;
    v = nxt[0][v];
    ranges[v].push_back(len);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> nxt[0][i];
        deg[nxt[0][i]]++;
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }   
    memset(num, -1, sizeof num);
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        init(i);
    }
    for (int i = 1; i <= n; i++) {
        if (inCircle[i]) {
            ranges[i].push_back(k);
            continue;
        }
        res[i]++;
        int v = getNext(i, k);
        if (inCircle[v]) {
            add(i);
        } else if (!inCircle[nxt[0][v]]) res[nxt[0][v]]--;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int v = nxt[0][u];
        if (inCircle[v]) continue;
        res[v] += res[u];
        if (--deg[v] == 0) q.push(v);
    }
    for (int i = 1; i <= numCircle; i++) {
        vector<int> sum(circle[i].size(), 0);
        for (int j = 0; j < circle[i].size(); j++) {
            int u = circle[i][j];
            for (int len : ranges[u]) {
                if (len >= circle[i].size()) {
                    sum[0]++;
                    continue;
                }
                if (j + len < circle[i].size()) {
                    sum[j]++;
                    if (j + len + 1 < circle[i].size()) sum[j + len + 1]--;
                } else {
                    sum[j]++;
                    sum[0]++;
                    sum[j + len + 1 - circle[i].size()]--;
                }
            }
        }
        for (int j = 1; j < sum.size(); j++) sum[j] += sum[j - 1];
        for (int j = 0; j < sum.size(); j++) {
            res[circle[i][j]] = sum[j];
        }
    }
    for (int i = 1; i <= n; i++) cout << res[i] << '\n';
    return 0;
}