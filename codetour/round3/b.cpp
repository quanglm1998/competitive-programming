#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const long long INF = 1e18;

int n, m, xs,ys, xt, yt, k;
vector<int> row[N], col[N];
long long res = INF;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> xs >> ys >> xt >> yt >> k;
    for (int i = 1; i <= n; i++) {
        row[i].push_back(1);
        row[i].push_back(m);
    }
    for (int i = 1; i <= m; i++) {
        col[i].push_back(1);
        col[i].push_back(n);
    }
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        row[x].push_back(y);
        col[y].push_back(x);
    }
    if (xs == xt || ys == yt) {
        cout << abs(xs - xt) + abs(ys - yt) << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        sort(row[i].begin(), row[i].end());
        row[i].resize(unique(row[i].begin(), row[i].end()) - row[i].begin());
    }
    for (int i = 1; i <= m; i++) {
        sort(col[i].begin(), col[i].end());
        col[i].resize(unique(col[i].begin(), col[i].end()) - col[i].begin());
    }

    set<pair<long long, pair<int, int>>> s;
    map<pair<int, int>, long long> minDist;
    set<pair<int, int>> used;
    minDist[{xs, ys}] = 0;

    s.insert({0ll, {xs, ys}});
    while (!s.empty()) {
        auto now = *s.begin();
        s.erase(s.begin());
        int x, y;
        x = now.second.first;
        y = now.second.second;
        long long dist = now.first;
        cout << x << ' ' << y << endl;
        cout << xt << ' ' << yt << endl;
        if (x == xt || y == yt) {
            res = min(res, dist + abs(x - xt) + abs(y - yt));
        }
        if (dist >= res) continue;
        if (used.count({x, y})) continue;
        used.insert({x, y});

        //update res


        // another
        int foo = upper_bound(row[x].begin(), row[x].end(), y) - row[x].begin();
        if (foo < row[x].size()) {
            int yy = row[x][foo];
            if (!minDist.count({x, yy}) || minDist[{x, yy}] > dist + abs(y - yy)) {
                minDist[{x, yy}] = dist + abs(y - yy);
                s.insert({minDist[{x, yy}], {x, yy}});
            }
        }
        foo = lower_bound(row[x].begin(), row[x].end(), y) - row[x].begin() - 1;
        if (foo >= 0) {
            int yy = row[x][foo];
            if (!minDist.count({x, yy}) || minDist[{x, yy}] > dist + abs(y - yy)) {
                minDist[{x, yy}] = dist + abs(y - yy);
                s.insert({minDist[{x, yy}], {x, yy}});
            }
        }

        int bar = upper_bound(col[y].begin(), col[y].end(), x) - col[y].begin();
        if (bar < col[y].size()) {
            int xx = col[y][bar];
            if (!minDist.count({xx, y}) || minDist[{xx, y}] > dist + abs(xx - x)) {
                minDist[{xx, y}] = dist + abs(xx - x);
                s.insert({minDist[{xx, y}], {xx, y}});
            }
        }

        bar = lower_bound(col[y].begin(), col[y].end(), x) - col[y].begin() - 1;
        if (bar >= 0) {
            int xx = col[y][bar];
            if (!minDist.count({xx, y}) || minDist[{xx, y}] > dist + abs(xx - x)) {
                minDist[{xx, y}] = dist + abs(xx - x);
                s.insert({minDist[{xx, y}], {xx, y}});
            }
        }
    }
    cout << (res == INF ? -1 : res) << endl;
    return 0;
}