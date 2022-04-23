#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point() { x = y = 0.0; }
    Point(long long x, long long y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    long long operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product
};

int ccw(Point u, Point v, Point w) {
    u = v - u;
    v = w - v;
    long long now = u % v;
    if (now == 0) return now;
    if (now > 0) return 1;
    return -1;
}

const int N = 10010;

int n, m, k;
Point a[N];

int check(Point s, Point t, Point u) {
    int res = 0;
    res |= ccw(s, t, u) * ccw(s, t, {u.x, u.y + 1}) < 0;
    res |= ccw(s, t, u) * ccw(s, t, {u.x + 1, u.y}) < 0;
    res |= ccw(s, t, {u.x + 1, u.y}) * ccw(s, t, {u.x + 1, u.y + 1}) < 0;
    res |= ccw(s, t, {u.x, u.y + 1}) * ccw(s, t, {u.x + 1, u.y + 1}) < 0;
    res |= ccw(s, t, {u.x, u.y}) * ccw(s, t, {u.x + 1, u.y + 1}) < 0;
    res |= ccw(s, t, {u.x + 1, u.y}) * ccw(s, t, {u.x, u.y + 1}) < 0;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> m >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i].x >> a[i].y;
    }   
    int q;
    cin >> q;
    while (q--) {
        int x, xx;
        cin >> x >> xx;
        int res = 0;
        Point s(x, 0), ss(xx, m);
        for (int i = 1; i <= k; i++) {
            res += check(s, ss, a[i]);
        }
        cout << res << '\n';
    }
    return 0;
}