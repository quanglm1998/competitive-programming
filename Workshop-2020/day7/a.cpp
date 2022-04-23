#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 100010;

int n, m, k;
int a[N], b[N];

bool check(int u, int flag = 0) {
    vector<pair<int, int>> ls;
    ls.push_back({0, u - 1});
    for (int i = 1; i <= n; i++) {
        // case 1
        if (a[i] + u <= b[i]) ls.push_back({a[i] + u, b[i]});
        // case 2
        if (a[i] < k) {
            ls.push_back({a[i], min(k - 1, b[i])});
        }
        // case 3
        if (b[i] > m - k) {
            ls.push_back({max(a[i], m - k + 1) + u, b[i] + u});
        }
        // case 4
        if (a[i] <= k && b[i] >= m - k) {
            ls.push_back({0, a[i] - 1});
            ls.push_back({b[i] + 1 + u, m});
        }
    }
    sort(ls.begin(), ls.end());
    // for (auto u : ls) cout << u.first << ' ' << u.second << endl;
    int maxVal = u - 1;
    for (auto val : ls) {
        if (maxVal >= m) return 0;
        if (val.first <= maxVal + 1) maxVal = max(maxVal, val.second);
        else {
            if (flag) cout << maxVal + 1 - u << ' ' << maxVal + 1 << endl;
            return 1;
        }
    }
    return 0;
}

bool checkZero() {
    for (int i = 1; i <= n; i++) {
        if (a[i] <= k && b[i] >= m - k) return 0;
    }
    return 1;
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    if (checkZero()) {
        cout << -1 << ' ' << -1 << endl;
        return 0;
    }
    int low = 0, high = k;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    if (high == k) cout << 0 << ' ' << k << endl;
    else check(high, 1);
    return 0;
}