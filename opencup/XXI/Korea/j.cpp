#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
const string DIR = "RULD";
const int Y[] = {0, 1, 0, -1};
const int X[] = {1, 0, -1, 0};

int n;
char s[N];
pair<int, int> a[N];
pair<pair<int, int>, int> sortedA[N];
map<pair<pair<int, int>, int>, pair<int, int>> cache;

pair<int, int> solve(int x, int y, int start) {
    // cout << x << ' ' << y << ' ' << start << endl;
    pair<int, int> now(x, y);
    if (cache.count({now, start})) return cache[{now, start}];
    if (start > n) return {x, y};
    pair<int, int> need;
    need.first = -now.first + a[start - 1].first;
    need.second = -now.second + a[start - 1].second;
    int pos = lower_bound(sortedA + 1, sortedA + n + 1, make_pair(need, start)) - sortedA;
    pair<int, int> res;
    if (pos > n || a[sortedA[pos].second] != need) {
        res = now;
        res.first += a[n].first - a[start - 1].first;
        res.second += a[n].second - a[start - 1].second;
    } else {
        int dir = DIR.find(s[sortedA[pos].second]);
        res = solve(-X[dir], -Y[dir], sortedA[pos].second + 1);
    }
    cache[{now, start}] = res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    cin >> (s + 1);
    pair<int, int> cur(0, 0);
    a[0] = cur;
    for (int i = 1; i <= n; i++) {
        int dir = DIR.find(s[i]);
        cur.first += X[dir];
        cur.second += Y[dir];
        a[i] = cur;
        sortedA[i] = {cur, i};
        // cout << i << ' ' <<  a[i].first << ' ' << a[i].second << endl;
    }
    sort(sortedA + 1, sortedA + n + 1);
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        pair<int, int> res = solve(x, y, 1);
        cout << res.first << ' ' << res.second << '\n';
    }
    return 0;
}