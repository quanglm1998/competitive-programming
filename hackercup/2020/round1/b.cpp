#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1000010;

int n, m, k, s;
int p[N], q[N];

bool check(int len) {
    int cur = 1;
    for (int i = 1; i <= n && cur <= m; i++) {
        if (p[i] > q[cur]) {
            if (len < p[i] - q[cur]) return 0;
            int dist = p[i] - q[cur];
            int last = q[cur];
            while (cur <= m && (len >= q[cur] - last + min(dist, q[cur] - p[i]) || q[cur] <= p[i])) {
                cur++;
            }
        } else {
            while (cur <= m && len >= q[cur] - p[i]) cur++;
        }
    }

    return cur > m;
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n >> m >> k >> s;
    for (int i = 1; i <= k; i++) {
        cin >> p[i];
    }
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        p[i] = (1ll * a * p[i - 2] + 1ll * b * p[i - 1] + c) % d + 1;
    }
    for (int i = 1; i <= k; i++) {
        cin >> q[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= m; i++) {
        q[i] = (1ll * a * q[i - 2] + 1ll * b * q[i - 1] + c) % d + 1;
    }
    sort(p + 1, p + n + 1);
    sort(q + 1, q + m + 1);

    // for (int i = 1; i <= n; i++) {
    //     cout << p[i] << ' ';
    // }
    // cout << endl;

    // for (int i = 1; i <= m; i++) {
    //     cout << q[i] << ' ';
    // }
    // cout << endl;

    // check(68);

    int low = -1, high = 2e9;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}