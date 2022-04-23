#include <bits/stdc++.h>

using namespace std;

const int N = 4010;
const int INF = 1e9;
const long long INF_LL = 4.1e18;

struct Point {
    int x, y, id;

    bool operator == (const Point &o) const {
        return x == o.x && y == o.y && id == o.id;
    }

    Point operator - (const Point &o) const {
        return {x - o.x, y - o.y, -1};
    }

    long long operator % (const Point &o) const {
        return 1ll * x * o.y - 1ll * y * o.x;
    }
};

int n, m;
Point a[N], b[N];
int l[N], r[N];
vector<Point> ls[N];
long long dp[N][N];
bool can[N][N];

long long ccw(Point u, Point v, Point w) {
    u = v - u;
    v = w - v;
    return u % v;
}

long long get(int u, int v) {
    int uu = u % n;
    int vv = v % n;
    int ll = l[uu];
    int rr = r[vv];
    while (ll > u) ll -= n;
    while (ll < u) ll += n;
    while (rr < v) rr += n;
    while (rr > v) rr -= n;
    if (ll < rr) return INF_LL;
    if (ll >= v || rr <= u) return 0;
    return min(abs(ccw(a[uu], a[vv], a[l[uu]])), abs(ccw(a[uu], a[vv], a[r[vv]])));   
}

bool isConsecutive(int root, int x, int y) {
    root %= n;
    x %= n;
    y %= n;
    return can[root][x];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i].x >> a[i].y;
            a[i].id = n - i - 1;
        }
        reverse(a, a + n);
        for (int i = 0; i < m; i++) {
            cin >> b[i].x >> b[i].y;
            b[i].id = -1;
        }
        for (int i = 0; i < n; i++) {
            fill(can[i], can[i] + n, 0);
        }

        for (int i = 0; i < n; i++) {
            ls[i].clear();
            ls[i].reserve(n + m - 1);
            for (int j = 0; j < n; j++) if (i != j) ls[i].push_back(a[j]);
            for (int j = 0; j < m; j++) ls[i].push_back(b[j]);

            sort(ls[i].begin(), ls[i].end(), [&](const Point &u, const Point &v) {
                return (u - a[i]) % (v - a[i]) < 0ll;
            });

            for (int j = 0; j + 1 < ls[i].size(); j++) {
                if (ls[i][j].id != -1 && ls[i][j + 1].id != -1) {
                    can[i][ls[i][j].id] = 1;
                }
            }

            if (ls[i][0].id == -1) l[i] = INF;
            else {
                int cur = 0;
                while (cur + 1 < ls[i].size() && ls[i][cur + 1].id != -1) cur++;
                l[i] = ls[i][cur].id;
            }
            if (ls[i].back().id == -1) r[i] = -INF;
            else {
                int cur = ls[i].size() - 1;
                while (cur - 1 >= 0 && ls[i][cur - 1].id != -1) cur--;
                r[i] = ls[i][cur].id;
            }
        }

        for (int len = 1; len < n; len++) {
            for (int i = 0; i + len < n * 2; i++) {
                int j = i + len;
                dp[i][j] = get(i, j);
                if (len > 1) {
                    if (isConsecutive(i, j - 1, j)) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1]);
                    }
                    if (isConsecutive(j, i, i + 1)) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][j]);
                    }
                }
            }
        }

        long long res = INF_LL + INF_LL;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dp[i][j] < INF_LL && dp[j][i + n] < INF_LL)
                    res = min(res, dp[i][j] + dp[j][i + n]);
            }
        }
        if (res >= INF_LL + INF_LL) cout << -1 << '\n';
        else {
            cout << res / 2;
            if (res % 2) cout << ".500";
            else cout << ".000";
            cout << '\n';
        }
    }
    return 0;
}