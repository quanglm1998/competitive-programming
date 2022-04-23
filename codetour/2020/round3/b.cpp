#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Point {
    int x, y;

    bool operator == (const Point &o) const {
        return x == o.x && y == o.y;
    }

    bool operator != (const Point &o) const {
        return !(*this == o);
    }
};

int get(int x, int y) {
    if (x > y) swap(x, y);
    if (x == 0) return 0;
    return y / x + get(x, y % x);
}

vector<Point> gen(Point u) {
    vector<Point> res;
    res.push_back(u);
    while (1) {
        u = res.back();
        if (u.x < u.y) {
            int nxt = u.y % u.x;
            if (nxt) res.push_back({u.x, u.y % u.x});
            else res.push_back({u.x, u.x});
        } else if (u.x > u.y) {
            int nxt = u.x % u.y;
            if (nxt) res.push_back({u.x % u.y, u.y});
            else res.push_back({u.y, u.y});
        } else break;
    }
    reverse(res.begin(), res.end());
    return res;
}

bool check1(Point now, Point A, Point B, int &res) {
    if (A.y != now.y) swap(A, B);
    if (A.y != now.y) return 0;
    int foo = B.x - now.x;
    if (foo % now.y) return 0;
    int alpha = foo / now.y;
    // cout << alpha << endl;
    int bar1 = A.x - now.x - alpha * now.y;
    if (bar1 < 0 || bar1 % now.y) return 0;
    int bar2 = B.y - now.y;
    if (bar2 < 0 || bar2 % (now.x + alpha * now.y)) return 0;
    res -= 2 * get(now.x + alpha * now.y, now.y);
    return 1;
}
bool check2(Point now, Point A, Point B, int &res) {
    if (B.x != now.x) swap(A, B);
    if (B.x != now.x) return 0;
    int foo = A.y - now.y;
    if (foo % now.x) return 0;
    int beta = foo / now.x;
    int bar1 = B.y - now.y - beta * now.x;
    if (bar1 < 0 || bar1 % now.x) return 0;
    int bar2 = A.x - now.x;
    if (bar2 < 0 || bar2 % (beta * now.x + now.y)) return 0;
    res -= 2 * get(now.x, beta * now.x + now.y);
    return 1;
}


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        Point A, B;
        cin >> A.x >> A.y;
        cin >> B.x >> B.y;
        int res = get(A.x, A.y) + get(B.x, B.y);
        vector<Point> lsA, lsB;
        lsA = gen(A);
        lsB = gen(B);
        int it = 0;
        if (lsA[0] != lsB[0]) {
            cout << -1 << '\n';
            continue;
        }
        int id = 0;
        while (id < lsA.size() && id < lsB.size() && lsA[id] == lsB[id]) id++;
        Point now = lsA[id - 1];
        A = (id == lsA.size() ? now : lsA[id]);
        B = (id == lsB.size() ? now : lsB[id]);
        int found = 0;
        // cout << A.x << ' ' << A.y << endl;
        // cout << B.x << ' ' << B.y << endl;
        // cout << now.x << ' ' << now.y << endl;
        if (check1(now, A, B, res)) {
            found = 1;
        }
        if (!found && check1(now, B, A, res)) {
            found = 1;
        }
        if (!found && check2(now, A, B, res)) {
            found = 1;
        }
        if (!found && check2(now, B, A, res)) {
            found = 1;
        }
        assert(found);
        cout << res << '\n';
    }
    return 0;
}