#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        bool haveOdd = 0, haveEven = 0;
        string s;
        cin >> s;
        s = "Q" + s;
        for (int i = 1; i <= n; i++) {
            int u = (s[i] - '0');
            if (i % 2 == u % 2) {
                if (i % 2) haveOdd = 1;
                else haveEven = 1;
            }
        }
        int res = 1;
        if (n % 2 && !haveOdd) {
            res = 2;
        }
        if (n % 2 == 0 && haveEven) res = 2;
        cout << res << '\n';
    }
    return 0;
}