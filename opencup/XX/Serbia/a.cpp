#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k, x;
    cin >> n >> k >> x;
    int curVal = 999999;
    vector<int> res(n + 1, 1);
    for (int i = n; i >= 1; i--) {
        res[i] = curVal;
        if (k >= i - 1) {
            k -= i - 1;
            curVal -= x;
        } else {
            for (int j = 1; j <= k; j++) res[j] = curVal - x;
            for (int j = k + 1; j < i; j++) res[j] = curVal - 1;
            break;
        }
    }

    for (int i = 1; i <= n; i++) cout << res[i] << ' ';
        cout << '\n';
    return 0;
}