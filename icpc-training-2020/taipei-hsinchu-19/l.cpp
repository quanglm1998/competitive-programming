#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point operator + (const Point &o) {
        return Point(x + o.x, y + o.y);
    }

    Point operator - (const Point &o) {
        return Point(x - o.x, y - o.y);
    }

    long long operator % (const Point &o) {
        return 1ll * x * o.y - 1ll * o.x * y;
    }

    bool operator < (const Point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }

    bool operator == (const Point &o) const {
        return x == o.x && y == o.y;
    }
};  

long long ccw(Point u, Point v, Point w) {
    u = v - u;
    v = w - v;
    return u % v;
}

vector<Point> getConvexHull(vector<Point> &a) {
    sort(a.begin(), a.end());
    vector<Point> res;
    res.push_back(a[0]);
    for (int i = 1; i < a.size(); i++) {
        while (res.size() >= 2 && ccw(res[res.size() - 2], res.back(), a[i]) >= 0) res.pop_back();
        res.push_back(a[i]);
    }
    int sz = res.size();
    for (int i = (int)a.size() - 2; i >= 0; i--) {
        while (res.size() >= sz + 1 && ccw(res[res.size() - 2], res.back(), a[i]) >= 0) res.pop_back();
        res.push_back(a[i]);
    }
    res.pop_back();
    return res;
}

long long getArea(Point u, Point v, Point w) {
    return abs(ccw(u, v, w));
}

void output(long long res) {
    cout << res / 2;
    if (res % 2) {
        cout << ".5";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<Point> a;
        map<Point, int> num;
        for (int i = 0; i < n; i++) {
            Point u;
            cin >> u.x >> u.y;
            if (!num.count(u)) a.push_back(u);
            num[u]++;
        }
        a = getConvexHull(a);
        if (a.size() <= 2) {
            output(0);
            continue;
        }
        if (a.size() == 3) {
            int found = 0;
            for (Point &u : a) {
                if (num[u] > 1) {
                    found = 1;
                    break;
                }
            }

            long long area = getArea(a[0], a[1], a[2]);

            if (found) {
                output(area);
            } else {
                long long minArea = 1e18;
                for (auto val : num) {
                    Point u = val.first;
                    if (u == a[0] || u == a[1] || u == a[2]) continue;
                    minArea = min(minArea, getArea(a[0], a[1], u));
                    minArea = min(minArea, getArea(a[1], a[2], u));
                    minArea = min(minArea, getArea(a[0], a[2], u));
                }
                output(area - minArea);
            }
            continue;
        }
        long long res = 0;
        int sz = a.size();
        for (int i = 0; i < sz; i++) {
            int down = i + 1;
            int up = i + 3;
            for (int j = i + 2; j < i + sz - 1; j++) {
                while (down + 1 < j && getArea(a[i], a[j % sz], a[down % sz]) < getArea(a[i], a[j % sz], a[(down + 1) % sz])) down++;
                while (up + 1 < i + sz && getArea(a[i], a[j % sz], a[up % sz]) < getArea(a[i], a[j % sz], a[(up + 1) % sz])) up++;
                res = max(res, getArea(a[i], a[j % sz], a[down % sz]) + getArea(a[i], a[j % sz], a[up % sz]));
            }
        }
        output(res);
    }
    return 0;
}