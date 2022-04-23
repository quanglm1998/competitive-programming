#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, x;
        cin >> n >> x;
        int sum = 0;
        int haveEqual = 0;
        int all = 1;
        for (int i = 1; i <= n; i++) {
            int u;
            cin >> u;
            sum += u;
            haveEqual |= (u == x);
            all &= (u == x);
        }
        if (all) cout << 0 << '\n';
        else if (haveEqual) cout << 1 << '\n';
        else if (sum == x * n) cout << 1 << '\n';
        else cout << 2 << '\n';
    }
    return 0;
}