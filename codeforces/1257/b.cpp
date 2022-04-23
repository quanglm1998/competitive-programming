#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        long long x, y;
        cin >> x >> y;
        if (x >= y) cout << "YES\n";
        else {
            for (int i = 1; i <= 100; i++) {
                if (x > 1 && x % 2 == 1) x--;
                x = 3 * x / 2;
                if (x >= y) break;
            }
            cout << (x >= y ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}