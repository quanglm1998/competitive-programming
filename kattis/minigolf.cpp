#include <bits/stdc++.h>

using namespace std;

const int N = 510;
const int H = 55;
const int INF = 2e9;

int n, h;
int a[N][H];
long long sum[N][H];
int d[N][N], r[N], res[N], cur[N];

struct Line {
    long long a, b, l, r;
    bool inside(int x) const {
        return x >= l && x < r;
    }
    bool intersect(const Line &u, int &x) const {
        long long aa = a - u.a;
        long long bb = u.b - b;
        if (aa == 0) return 0;
        x = bb / aa;
        if (!inside(x) || !u.inside(x)) return 0;
        return 1;
    }
    long long eval(long long x) {
        return a * x + b;
    }
};

struct Event {
    long long x;
    int u, v;
};

vector<Line> l[N];
vector<Event> events;

void addEvent(int u, int v) {
    for (int curU = 0, curV = 0; curU < l[u].size() && curV < l[v].size();) {
        int x;
        if (l[u][curU].intersect(l[v][curV], x)) {
            events.push_back({x - 1, u, v});
            events.push_back({x, u, v});
            events.push_back({x + 1, u, v});
        } else events.push_back({max(l[u][curU].l, l[v][curV].l), u, v});
        if (l[u][curU].r <= l[v][curV].r) curU++;
        else curV++;
    }
}

void update(int u, int v, int delta) {
    if (d[u][v] == 0) {
        r[u] += delta;
        r[v] += delta;
    } else if (d[u][v] < 0) {
        r[v] += delta;
    } else r[u] += delta;
}

long long getVal(int u, long long x) {
    while (cur[u] + 1 < l[u].size() && l[u][cur[u]].r <= x) cur[u]++;
    return l[u][cur[u]].eval(x);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> h;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= h; j++) cin >> a[i][j];
        sort(a[i] + 1, a[i] + h + 1);
        for (int j = 1; j <= h; j++) sum[i][j] = sum[i][j - 1] + a[i][j];
        for (int j = 1; j <= h; j++) {
            if (a[i][j - 1] < a[i][j]) l[i].push_back({h - j + 1, sum[i][j - 1], a[i][j - 1], a[i][j]});
        }
        l[i].push_back({0, sum[i][h], a[i][h], INF});
    }
    for (int i = 1; i <= n; i++) {
        r[i] = res[i] = n;
        for (int j = i + 1; j <= n; j++) {
            d[i][j] = d[j][i] = 0;
            addEvent(i, j);
        }
    }
    sort(events.begin(), events.end(), [&](Event &u, Event &v) { return u.x < v.x; });
    for (int l = 0, rr = 0; l < events.size(); l = rr) {
        vector<int> affected;
        while (rr < events.size() && l == rr) {
            long long x = events[rr].x;
            int u = events[rr].u, v = events[rr].v;
            update(u, v, -1);
            long long uu = getVal(u, x);
            long long vv = getVal(v, x);
            d[u][v] = uu == vv ? 0 : uu < vv ? -1 : 1;
            d[v][u] = -d[u][v];
            update(u, v, 1);
            rr++;
            affected.push_back(u); affected.push_back(v);
        }
        for (int u : affected) res[u] = min(res[u], r[u]);
    }
    for (int i = 1; i <= n; i++) cout << res[i] << '\n';
    return 0;
}