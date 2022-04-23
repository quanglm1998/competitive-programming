#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    long long low = 0, high = 1e18;
    while (high - low > 1) {
        long long mid = low + high >> 1;
        long long tot = 0;
        for (int u : a) {
            tot += mid / u;
            tot = min(tot, 1ll * t);
        }
        if (tot >= t) high = mid;
        else low = mid;
    }   
    cout << high << endl;
    return 0;
}