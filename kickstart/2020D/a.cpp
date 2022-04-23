#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int maxVal = -1;
int res = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > maxVal && (i == n || a[i] > a[i + 1])) {
            res++;
        }
        maxVal = max(maxVal, a[i]);
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}