#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    set<string> res;
    sort(s.begin(), s.end());
    while (1) {
        res.insert(s);
        if (!next_permutation(s.begin(), s.end())) break;
    }
    cout << res.size() << '\n';
    for (auto u : res) cout << u << '\n';
    return 0;
}