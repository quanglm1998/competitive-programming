#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    if (n & 1) {
        cout << "No" << endl;
        return 0;
    }
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[i + n / 2]) return (cout << "No" << endl, 0);
    }
    cout << "Yes" << endl;
    return 0;
}