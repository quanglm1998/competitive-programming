#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int a[N];
int res[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if (n <= 2) {
        cout << 0 << endl;
        for (int i = 1; i <= n; i++) {
            cout << a[i] << ' ';
        }
        cout << endl;
        return 0;
    }
    sort(a + 1, a + n + 1);
    int mid = (n - 1) / 2;
    int l = 2, r = n - 1;
    if (r % 2) r--;
    for (int i = 1; i <= mid; i++) {
        if (i % 2) {
            res[l] = a[i];
            l += 2;
        } else {
            res[r] = a[i];
            r -= 2;
        }
    }
    l = 1, r = n;
    if (r % 2 == 0) r--;
    int start = n % 2 ? mid + 1 : mid + 2;
    for (int i = start; i <= n; i++) {
        if ((i - start + 1) % 2) {
            res[l] = a[i];
            l += 2;
        } else {
            res[r] = a[i];
            r -= 2;
        }
    }
    if (n % 2 == 0) {
        res[n] = a[mid + 1];
    }

    int tot = 0;
    for (int i = 2; i < n; i++) {
        tot += (res[i] < res[i - 1]) && (res[i] < res[i + 1]);
    }
    cout << tot << endl;
    for (int i  = 1; i <= n; i++) cout << res[i] << ' ';
        cout << endl;
    return 0;
}