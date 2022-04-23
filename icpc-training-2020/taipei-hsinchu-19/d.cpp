#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    int first = 1;
    while (cin >> s) {
        if (s == "bubble" || s == "tapioka") continue;
        if (!first) cout << ' ';
        cout << s;
        first = 0;
    }
    if (first) {
        cout << "nothing";
    }
    cout << endl;
    return 0;
}