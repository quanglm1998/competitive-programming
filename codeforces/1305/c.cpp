#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    // cin >> n >> m;
    n = 200000, m = 1000;
    cout << n << ' ' << m << endl;
    for (int i = 0; i < n; i++) {
        a[i] = min(i, m - 1);
        cout << a[i] << ' ';
    }
    cout << endl;
    return 0;
    long long res = 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            res = (res * abs(a[i] - a[j])) % m;
        }
    }
    cout << res << endl;
    return 0;
}