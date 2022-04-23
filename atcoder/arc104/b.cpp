#include <bits/stdc++.h>

using namespace std;

const int N = 5010;

int n;
string s;
map<pair<int, int>, int> m;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> s;
    pair<int, int> cur(0, 0);
    m[cur] = 1;
    int res = 0;
    for (char u : s) {
        if (u == 'A') cur.first++;
        else if (u == 'T') cur.first--;
        else if (u == 'C') cur.second++;
        else cur.second--;
        res += m[cur];
        m[cur]++;
    }
    cout << res << '\n';
    return 0;
}