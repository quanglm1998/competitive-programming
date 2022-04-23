#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        int c, sum;
        cin >> c >> sum;
        int a = sum / c;
        int b = sum % c;
        long long res = 0;
        for (int i = 0; i < c; i++) {
            int now = a + (i < b);
            res += 1ll * now * now;
        }
        cout << res << '\n';
    }
    return 0;
}