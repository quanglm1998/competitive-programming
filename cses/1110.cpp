#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    s += s;
    int l = 0;
    int last = 0;
    int res = 0;
    while (l < n) {
        res = l;
        int r = l + 1, k = l;
        while (r < s.size() && s[r] >= s[k]) {
            if (s[r] == s[k]) k++;
            else k = l;
            r++;
        }
        while (l <= k) l += r - k;
    }
    for (int i = 0; i < n; i++) cout << s[res + i];
        cout << endl;
    return 0;
}