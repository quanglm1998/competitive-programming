#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    vector<int> cnt(26);   
    for (char u : s) {
        cnt[u - 'A']++;
    }
    int posOdd = -1;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] & 1) {
            if (posOdd == -1) posOdd = i;
            else {
                cout << "NO SOLUTION\n";
                return 0;
            }
        }
    }
    int l = 0, r = s.size() - 1;
    for (int i = 0; i < 26; i++) {
        if (i == posOdd) continue;
        while (cnt[i] > 0) {
            s[l++] = s[r--] = (char)('A' + i);
            cnt[i] -= 2;
        }
    }
    if (posOdd != -1) {
        while (cnt[posOdd] > 0) {
            s[l++] = s[r--] = (char)('A' + posOdd);
            cnt[posOdd] -= 2;
        }
    }
    cout << s << endl;
    return 0;
}