#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    long long res = a[n];
    for (int i = n; i; i--) {
        for (int j = i - 1; j >= 1 && 1ll * a[j] * a[i] > res; j--) {
            res = max(res, 1ll * a[j] * a[i] / __gcd(a[i], a[j]));
            if (1.0 * clock() / CLOCKS_PER_SEC > 0.95) {
                cout << res << endl;
                exit(0);
            }
        }
    }
    cout << res << endl;
    return 0;
}