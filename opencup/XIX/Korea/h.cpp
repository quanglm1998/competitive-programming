#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    long long res = 0;
    for (int i = 1; i < 1000; i++) {
        for (int j = 1; j < 1000; j++) {
            if (__gcd(i, j) == 1 && i + j < 1000) {
                long long l = max((a - 1) / i + 1, (c - 1) / j + 1);
                long long r = min(b / i, d / j);
                if (l <= r) res += r - l + 1;
            }
        }
    }
    cout << res << '\n';
    return 0;
}