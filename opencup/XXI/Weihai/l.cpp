#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        const int LIM = 2000000;
        int f = 0;
        for (int i = 2; i <= LIM; i++) {
            if (n % i == 0) {
                int cnt = 0;
                while (n % i == 0) {
                    n /= i;
                    cnt++;
                }
                if (cnt >= 2) {
                    f = 1;
                    break;
                }
            }
        }
        if (n > 1) {
            long long m = sqrt(n);
            while (m * m > n) m--;
            while (m * m < n) m++;
            if (m * m == n) {
                cout << "yes\n";
                continue;
            }
        }
        cout << (f ? "yes" : "no") << '\n';
    }
    return 0;
}