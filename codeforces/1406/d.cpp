#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 100010;

int n;
int a[N];
int diff[N];
int down = 0;

int getCeil(int u) {
    if (u > 0) return (u - 1) / 2 + 1;
    return -((-u) / 2);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        diff[i] = a[i + 1] - a[i];
        if (diff[i] < 0) down -= diff[i];
    }
    cout << getCeil(down + a[n]) << '\n';
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        int x;
        cin >> l >> r >> x;
        if (l > 1) {
            if (diff[l - 1] < 0) down += diff[l - 1];
            diff[l - 1] += x;
            if (diff[l - 1] < 0) down -= diff[l - 1];
        }
        if (r < n) {
            if (diff[r] < 0) down += diff[r];
            diff[r] -= x;
            if (diff[r] < 0) down -= diff[r];
        }

        if (r == n) a[n] += x;
        cout << getCeil(down + a[n]) << '\n';
    }
    return 0;
}