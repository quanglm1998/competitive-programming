#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int a, b;
        cin >> a >> b;
        if (a < b) swap(a, b);
        int diff = a - b;
        a -= diff * 2;
        b -= diff;
        if (a < 0 || b < 0) {
            cout << "NO\n";
            continue;
        }
        if (a % 3 == 0) cout << "YES\n";
        else cout << "NO\n";
    }   
    return 0;
}