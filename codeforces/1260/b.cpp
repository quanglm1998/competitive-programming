#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int x, y;
        cin >> x >> y;
        if (x < y) swap(x, y);
        if ((x + y) % 3) {
            cout << "NO\n";
            continue;
        }
        int sum = (x + y) / 3;
        int sub = x - y;
        if ((sum + sub) % 2) {
            cout << "NO\n";
            continue;
        }
        if (sum < sub) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
    return 0;
}