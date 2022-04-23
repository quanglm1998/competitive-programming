#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1000010;

int n, k;
int s[N], x[N], y[N];

void solve(int test) {
    cout << "Case #" << test << ": ";

    cin >> n >> k;
    int a, b, c, d;
    
    for (int i = 1; i <= k; i++) {
        cin >> s[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        s[i] = (a * s[i - 2] + b * s[i - 1] + c) % d;
    }

    for (int i = 1; i <= k; i++) {
        cin >> x[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        x[i] = (a * x[i - 2] + b * x[i - 1] + c) % d;
    }

    for (int i = 1; i <= k; i++) {
        cin >> y[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        y[i] = (a * y[i - 2] + b * y[i - 1] + c) % d;
    }

    long long sumLow = 0ll;
    long long sumHigh = 0ll;
    long long canLow = 0;
    long long canHigh = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] < x[i]) {
            sumLow += x[i] - s[i];
            canLow += y[i];
        } else if (s[i] > x[i] + y[i]) {
            sumHigh += s[i] - x[i] - y[i];
            canHigh += y[i];
        } else {
            canHigh += s[i] - x[i];
            canLow += x[i] + y[i] - s[i];
        }
    }

    long long res = 0;
    res += min(sumLow, sumHigh);
    sumLow -= res;
    sumHigh -= res;
    if (sumLow == 0 && sumHigh == 0)  {
        cout << res << '\n';
        return;
    }
    if (sumLow == 0) {
        if (sumHigh > canLow) {
            cout << -1 << '\n';
            return;
        } else {
            res += sumHigh;
        }
    } else {
        if (sumLow > canHigh) {
            cout << -1 << '\n';
            return;
        } else {
            res += sumLow;
        }
    }
    cout << res << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}