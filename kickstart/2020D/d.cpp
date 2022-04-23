#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 20;

int n, q;
int a[N];

struct ST {
    int n;
    vector<int> t;

    ST(int n = 0) : n(n) {
        t.assign((n + 1) << 2 | 10, 0);
    }

    void init(int node, int l, int r) {
        if (l == r) {
            t[node] = l;
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        if (a[t[node << 1]] > a[t[node << 1 | 1]]) t[node] = t[node << 1];
        else t[node] = t[node << 1 | 1];
    }

    int get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return -1;
        if (x <= l && r <= y) return t[node];
        int m = l + r >> 1;
        int p1 = get(node << 1, l, m, x, y);
        int p2 = get(node << 1 | 1, m + 1, r, x, y);
        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        if (a[p1] > a[p2]) return p1;
        return p2;
    }
} t;

pair<int, int> get(int s, int k) {
    s--;
    if (k == 1) return {s, s};
    int low = -1;
    int high = s + 1;
    while (high - low > 1) {
        int mid = low + high >> 1;
        int rMid = mid + k - 1;
        if (rMid < s) low = mid + 1;
        else if (rMid >= n) high = mid;
        else {
            int pos = t.get(1, 0, n, mid + 1, rMid);
            if (pos <= s) {
                if (a[pos] < a[rMid + 1]) {
                    return {mid, rMid};
                } else {
                    low = mid + 1;
                }
            } else {
                if (a[pos] < a[mid]) {
                    return {mid, rMid};
                } else {
                    high = mid;
                }
            }
        }
    }
    return {low, low + k - 1};
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n >> q;
    a[0] = a[n] = 1e9;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    t = ST(n);
    t.init(1, 0, n);
    while (q--) {
        int s, k;
        cin >> s >> k;
        if (k == 1) cout << s << ' ';
        else {
            pair<int, int> foo = get(s, k);
            pair<int, int> bar = get(s, k - 1);
            // cout << foo.first << ' ' << foo.second << endl;
            // cout << bar.first << ' ' << bar.second << endl;
            if (foo.first == bar.first) cout << foo.second + 1 << ' ';
            else cout << foo.first + 1 << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}