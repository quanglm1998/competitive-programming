#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            for (int k = 0; k < n; k++) {
                if (i == k || j == k) continue;
                if ((a[i] - a[j]) % a[k] != 0) {
                    cout << "no\n";
                    return 0;
                }
            }
        }
    }
    cout << "yes\n";
    return 0;
}