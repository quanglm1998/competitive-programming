#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    long long x;
    cin >> x;   
    long long res = x + 1;
    pair<long long, long long> ans;
    for (int i = 1; 1ll * i * i <= x; i++) {
        if (x % i) continue;
        long long foo = x / i;
        if (__gcd(foo, 1ll * i) > 1) continue;
        if (max(foo, 1ll * i) < res) {
            res = max(foo, 1ll * i);
            ans = {i, foo};
        }
    }
    cout << ans.first << ' ' << ans.second << endl;
    return 0;
}