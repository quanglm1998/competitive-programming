#include <bits/stdc++.h>

using namespace std;



void solve(int test) {
    cout << "Case #" << test << ": ";
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int res = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i; i--) {
        if (a[i] == 1 && i >= k) {
            int found = 0;
            for (int j = 1; j < k; j++) {
                if (a[i - j] != a[i - j + 1] + 1) found = 1;
            }
            res += !found;
        }
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