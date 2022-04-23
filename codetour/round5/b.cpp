#include <bits/stdc++.h>

using namespace std;

#define int long long

#define EPS 1e-6

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point() { x = y = 0.0; }
    Point(double x, double y) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }

    double operator % (const Point& a) const { return x*a.y - y*a.x; }
};

typedef vector< Point > Polygon;

#define ccw(a, b, c) ((double)(b.x-a.x)*(double)(c.y-a.y)-(double)(b.y-a.y)*(c.x-a.x))

bool inConvex(vector<Point>& l, Point p){
    int a = 1, b = l.size()-1, c;
    if (ccw(l[0], l[a], l[b]) > 0) swap(a,b);
    if (ccw(l[0], l[a], p) >= 0 || ccw(l[0], l[b], p) <= 0) return false;
    while(abs(a-b) > 1) {
        c = (a+b)/2;
        if (ccw(l[0], l[c], p) > 0) b = c; else a = c;
    }
    return ccw(l[a], l[b], p) < 0;
}

bool intersect(Point a, Point b, Point c, Point d, Point &r) {
    double D =  (b - a) % (d - c);
    if (cmp(D, 0) == 0) return false;
    double t =  ((c - a) % (d - c)) / D;
    double s = -((a - c) % (b - a)) / D;
    r = a + (b - a) * t;
    return cmp(t, 0) >= 0 && cmp(t, 1) <= 0 && cmp(s, 0) >= 0 && cmp(s, 1) <= 0;
}

Polygon convexIntersect(Polygon P, Polygon Q) {
    const int n = P.size(), m = Q.size();
    int a = 0, b = 0, aa = 0, ba = 0;
    enum { Pin, Qin, Unknown } in = Unknown;
    Polygon R;
    do {
        int a1 = (a+n-1) % n, b1 = (b+m-1) % m;
        double C = (P[a] - P[a1]) % (Q[b] - Q[b1]);
        double A = (P[a1] - Q[b]) % (P[a] - Q[b]);
        double B = (Q[b1] - P[a]) % (Q[b] - P[a]);
        Point r;
        if (intersect(P[a1], P[a], Q[b1], Q[b], r)) {
            if (in == Unknown) aa = ba = 0;
            R.push_back( r );
            in = B > 0 ? Pin : A > 0 ? Qin : in;
        }
        if (C == 0 && B == 0 && A == 0) {
            if (in == Pin) { b = (b + 1) % m; ++ba; }
            else            { a = (a + 1) % m; ++aa; }
        } else if (C >= 0) {
            if (A > 0) { if (in == Pin) R.push_back(P[a]); a = (a+1)%n; ++aa; }
            else       { if (in == Qin) R.push_back(Q[b]); b = (b+1)%m; ++ba; }
        } else {
            if (B > 0) { if (in == Qin) R.push_back(Q[b]); b = (b+1)%m; ++ba; }
            else       { if (in == Pin) R.push_back(P[a]); a = (a+1)%n; ++aa; }
        }
    } while ( (aa < n || ba < m) && aa < 2*n && ba < 2*m );
    if (in == Unknown) {
        if (inConvex(Q, P[0])) return P;
        if (inConvex(P, Q[0])) return Q;
    }
    return R;
}

double area(Polygon p) {
    double area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return abs(area) / 2.0;
}

const int N = 100;

int n;
Polygon a[N];

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        a[i].resize(m);
        for (auto &u : a[i]) cin >> u.x >> u.y;
        reverse(a[i].begin(), a[i].end());
    }
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k;
            cin >> k;
            vector<int> ls(k);
            for (int &u : ls) {
                cin >> u; 
                u--;
            }
            Polygon res = a[ls[0]];
            for (int i = 1; i < ls.size(); i++) {
                res = convexIntersect(res, a[ls[i]]);
            }
            double now = area(res);
            cout << fixed << setprecision(10) << now << '\n';
        } else {
            int x;
            cin >> x;
            x--;
            double res = 0;
            for (int mask = 0; mask < (1 << n); mask++) {
                if (mask >> x & 1) continue;
                int num = __builtin_popcount(mask);
                Polygon cur = a[x];
                for (int i = 0; i < n; i++) {
                    if (mask >> i & 1) {
                        cur = convexIntersect(cur, a[i]);
                    }
                }
                if (num % 2 == 0) {
                    res += area(cur);
                } else res -= area(cur);
            }
            cout << fixed << setprecision(10) << res << '\n';
        }
    }
    return 0;
}