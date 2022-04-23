#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int k, l;
        cin >> k >> l;
        if (l >= 2000) {
            cout << -1 << '\n';
            continue;
        }
        int n = 1999;
        cout << n << '\n';
        cout << -1 << ' ';
        k += n;
        const int MAX = 1e6;
        for (int i = 2; i <= n; i++) {
            int cur = min(MAX, k);
            cout << cur << ' ';
            k -= cur;
        }   
        cout << '\n';
    }
    return 0;
}