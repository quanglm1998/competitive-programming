#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int a[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int neg = 0;
        for (int i = 1; i <= n; i++) {
            int u;
            cin >> u;
            a[i] = u - a[i];
            neg |= (a[i] < 0);
        }
        if (neg) {
            cout << "NO\n";
            continue;
        }
        int l = 1, r = n;
        while (l <= n && a[l] == 0) l++;
        while (r >= 1 && a[r] == 0) r--;
        if (l == n + 1) {
            cout << "YES" << '\n';
            continue;
        }
        int found = 0;
        for (int i = l; i <= r; i++) {
            if (a[l] != a[i]) found = 1;
        }
        cout << (found ? "NO" : "YES") << '\n';
    }
    return 0;
}