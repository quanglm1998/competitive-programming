#include <bits/stdc++.h>

using namespace std;

int getCeil(int a, int b) {
    return (a - 1) / b + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        int a, b, k;
        cin >> a >> b >> k;
        int c = __gcd(a, b);
        a /= c;
        b /= c;
        if (a == b) {
            cout << "OBEY\n";
        } else {
            if (a < b) swap(a, b);
            if (getCeil(a - 1, b) < k) {
                cout << "OBEY\n";
            } else {
                cout << "REBEL\n";
            }
        }
    }
    return 0;
}