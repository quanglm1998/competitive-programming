#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        long long minPref = 1e18;
        long long sum = 0;
        long long maxRes = -1e18;
        for (int i = 1; i <= n; i++) {
            int u; cin >> u;
            sum += u;
            if (i < n) maxRes = max(maxRes, sum);
            maxRes = max(maxRes, sum - minPref);
            minPref = min(minPref, sum);
        }
        cout << ((maxRes < sum) ? "YES" : "NO") << '\n';
    }       
    return 0;
}