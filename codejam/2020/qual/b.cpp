#include <bits/stdc++.h>

using namespace std;

string s;

string calc(int l, int r, int depth) {
    if (l > r) return "";
    char minChar = *min_element(s.begin() + l, s.begin() + r + 1);
    int minVal = minChar - '0';
    string res = "";
    for (int i = 1; i <= minVal - depth; i++) res += '(';
    for (int i = l; i <= r; i++) {
        if (s[i] == minChar) {
            res += s[i];
            continue;
        }
        int j = i;
        while (j <= r && s[j] > minChar) j++;
        res += calc(i, j - 1, minVal);
        i = j - 1;
    }
    for (int i = 1; i <= minVal - depth; i++) res += ')';
            return res;
}       

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> s;
    cout << calc(0, s.size() - 1, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}