#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        long long n;
        cin >> n;
        int num = 1;
        long long tot = 0;
        while (tot + (1ll << num) * ((1ll << num) - 1) / 2 <= n) {
            tot += (1ll << num) * ((1ll << num) - 1) / 2;
            num++;
        }
        cout << num - 1 << endl;
    }
    return 0;
}