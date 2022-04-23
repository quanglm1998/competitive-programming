#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        long long x, y, k;
        cin >> x >> y >> k;
        long long need = k * (1 + y) - 1;
        cout << (need - 1) / (x - 1) + 1 + k << endl;
    }
    return 0;
}