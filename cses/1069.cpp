#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    int cur = 1;
    int res = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            cur++;
        } else {
            cur = 1;
        }
        res = max(res, cur);
    }   
    cout << res << endl;
    return 0;
}