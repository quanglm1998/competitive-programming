#include <bits/stdc++.h>
using namespace std;

#define all(s) s.begin(), s.end()
#define pb push_back
#define ii pair<int, int>
#define x first
#define y second
#define bit(x, y) ((x >> y) & 1)

const int MOD = 1000000007;
const int N = 1000005;

int p2[N];

void solve() {
    string s, t;
    cin >> s >> t; 
    if (s.size() > t.size()) swap(s, t);
    else if (s > t) swap(s, t);
    vector<int> a(s.size(), 0);
    vector<int> b(t.size(), 0);
    int cura = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '1') {
            a[s.size() - 1 - i] = (cura + 1) % MOD;
        } else {
            a[s.size() - 1 - i] = cura;
        }
        cura = (2 * cura + (s[i] == '1')) % MOD;
    }
    int curb = 0;
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == '1') {
            b[t.size() - 1 - i] = (curb + 1) % MOD;
        } else {
            b[t.size() - 1 - i] = curb;
        }
        curb = (2 * curb + (t[i] == '1')) % MOD;
    }
    int lose, win, draw;
    lose = win = draw = 0;
    for (int i = 0; i < min(s.size(), t.size()); i += 2) {
        lose += 1LL * a[i] * b[i] % MOD;
        lose %= MOD;
    } 
    vector<int> suffa = a;
    vector<int> prefa = a;
    for (int i = (int) suffa.size() - 2; i >= 0; i--) {
        suffa[i] = (suffa[i] + suffa[i + 1]) % MOD;
    }
    suffa.pb(0);
    for (int i = 0; i < prefa.size(); i++) {
        if (i % 2 == 0) prefa[i] = 0;
        if (i != 0) prefa[i] = (prefa[i - 1] + prefa[i]) % MOD;
    }
    for (int i = 1; i < t.size(); i++) {
        int foo = 0;
        int id = min(i, (int) s.size() - 1);
        if (i % 2 == 0) {
            foo = prefa[id];
        } else {
            foo = prefa[id] + suffa[id + 1];
        }
        win = (win + 1LL * foo * b[i]) % MOD;
    }
    draw = 1LL * cura * curb % MOD;
    draw = (1LL * draw - win - lose) % MOD;
    if (draw < 0) draw += MOD;
    cout << win << ' ' << draw << ' ' << lose << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); 
    cout.tie(0);
    int ntest;
    cin >> ntest;
    while (ntest--) {
        solve();
    }
    return 0;
}