#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int x, y;
        cin >> x >> y;
        int layer = max(x, y);
        long long initValue = 1ll * (layer - 1) * (layer - 1);
        if (layer % 2 == 0) swap(x, y);
        if (x == layer) initValue += y;
        else initValue += 2 * layer - x;
        cout << initValue << '\n';
    }   
    return 0;
}