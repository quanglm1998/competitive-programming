#include <bits/stdc++.h>

using namespace std;

const int N = 510;
const long long INF = 1.1e18;

int n, m;
long long dist[N][N];
int id[N][N];
long long d[N];
bool used[N];
int pre[N];

struct Edge {
    int u, v, w;
} e[N * N];

long long getDist(int now, int x, long long delta) {
    return min(dist[e[now].u][x] + delta, dist[e[now].v][x] + e[now].w - delta);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fill(dist[i] + 1, dist[i] + n + 1, INF);
        iota(id[i] + 1, id[i] + n + 1, 1);
        dist[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].w *= 2;
        dist[e[i].u][e[i].v] = dist[e[i].v][e[i].u] = e[i].w;
    }   
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        sort(id[i] + 1, id[i] + n + 1, [&](int u, int v) {
            return dist[i][u] < dist[i][v];
        });
    }
    pair<long long, pair<int, int>> res(INF, {0, 0});
    for (int i = 1; i <= m; i++) {
        int u = e[i].u;
        int v = e[i].v;
        int w = e[i].w;
        vector<int> st;
        for (int j = 1; j <= n; j++) {
            int x = id[v][j];
            while (!st.empty() && dist[u][st.back()] <= dist[u][x]) st.pop_back();
            st.push_back(x);
        }

        res = min(res, {getDist(i, st[0], 0), {i, 0}});
        res = min(res, {getDist(i, st.back(), w), {i, w}});
        for (int j = 0; j + 1 < st.size(); j++) {
            long long delta = (dist[v][st[j]] + w - dist[u][st[j + 1]]) / 2;
            if (delta >= 0 && delta <= w) res = min(res, {getDist(i, st[j], delta), {i, delta}});
        }
    }
    cout << res.first << '\n';
    for (int i = 1; i <= n + 2; i++) {
        fill(dist[i] + 1, dist[i] + n + 2, INF);
        dist[i][i] = 0;
        d[i] = INF;
    }
    d[n + 1] = 0;
    for (int i = 1; i <= m; i++) {
        dist[e[i].u][e[i].v] = dist[e[i].v][e[i].u] = e[i].w;
    }
    dist[e[res.second.first].u][n + 1] = dist[n + 1][e[res.second.first].u] = res.second.second;
    dist[e[res.second.first].v][n + 1] = dist[n + 1][e[res.second.first].v] = e[res.second.first].w - res.second.second;
    
    while (1) {
        int now = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (used[i]) continue;
            if (!now || d[now] > d[i]) now = i;
        }
        if (!now) break;
        used[now] = 1;
        for (int i = 1; i <= n + 1; i++) {
            if (d[i] > d[now] + dist[now][i]) {
                d[i] = d[now] + dist[now][i];
                pre[i] = now;
            }
        }
    }

    cout << e[res.second.first].u << ' ' << e[res.second.first].v << '\n';
    for (int i = 1; i <= n; i++) {
        if (i != e[res.second.first].u && i != e[res.second.first].v) cout << pre[i] << ' ' << i << '\n';
    }
    return 0;   
}