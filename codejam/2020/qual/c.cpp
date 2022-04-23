#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n;
int res[N];

struct Data {
    int l, r, id;
} a[N];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }
    sort(a + 1, a + n + 1, [&](const Data &u, const Data &v) {
        return make_pair(u.l, u.r) < make_pair(v.l, v.r);
    });
    pair<int, int>cur(0, 0);
    for (int i = 1; i <= n; i++) {
        if (a[i].l >= cur.first) {
            res[a[i].id] = 0;
            cur.first = a[i].r;
        } else if (a[i].l >= cur.second) {
            res[a[i].id] = 1;
            cur.second = a[i].r;
        } else {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (res[i] ? 'C' : 'J');
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