#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    pair<int, int> res(0, 0);
    long long sum = 0;
    int num0 = 0;
    long long sum0 = 0;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        if (b == 0) {
            num0++;
            sum0 += a;
        } else {
            int now = a - b + 1;
            if (res.second < now) swap(res.second, now);
            if (res.first < res.second) swap(res.second, res.first);
            sum += a;
        }
    }
    if (num0 == 0) {
        cout << min(res.first, res.second + 1) << ' ' << sum << '\n';
    } else if (num0 == 1) {
        cout << res.first + 1 << ' ' << sum + sum0 << '\n';
    } else {
        cout << res.first << ' ' << sum << '\n';
    }
    return 0;
}