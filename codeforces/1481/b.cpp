#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int &u : a) {
            cin >> u;
        }
        int res = 0;
        for (int i = 1; i <= k; i++) {
            int pos = 0;
            while (pos < n && (pos == n - 1 || a[pos] >= a[pos + 1])) {
                pos++;
            }
            if (pos >= n) {
                res = -1;
                break;
            }
            a[pos]++;
            res = pos + 1;
        }
        cout << res << '\n';
    }
    return 0;
}