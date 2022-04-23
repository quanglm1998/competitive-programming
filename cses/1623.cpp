#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    long long sum = 0;
    for (int &u : a) {
        cin >> u;
        sum += u;
    }
    long long res = sum;
    for (int i = 0; i < (1 << n); i++) {
        long long now = 0;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) now += a[j];
        }
        res = min(res, abs(sum - now * 2));
    }
    cout << res << endl;
    return 0;
}