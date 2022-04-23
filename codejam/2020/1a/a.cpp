#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n;
string p[N];

vector<string> get(string &u) {
    vector<string> res;
    string cur = "";
    for (char v : u) {
        if (v == '*') {
            if (!cur.empty()) {
                res.push_back(cur);
                cur = "";
            }
        } else cur += v;
    }
    if (!cur.empty()) res.push_back(cur);
    return res;
}

bool join(string &u, string &v) {
    for (int i = 0; i < min(u.size(), v.size()); i++) {
        if (u[i] != v[i]) return 0;
    }
    if (u.size() < v.size()) {
        u = v;
    }
    return 1;
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    string pref = "";
    string suff = "";
    vector<string> s;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        vector<string> u = get(p[i]);
        if (p[i][0] != '*') {
            if (!join(pref, u[0])) {
                cout << '*' << '\n';
                return;
            }
        }
        if (p[i].back() != '*') {
            string now = u.back();
            reverse(now.begin(), now.end());

            if (!join(suff, now)) {
                cout << '*' << '\n';
                return;
            }
        }
        s.insert(s.end(), u.begin(), u.end());
    }
    cout << pref;
    for (auto u : s) cout << u;
    reverse(suff.begin(), suff.end());
    cout << suff << '\n';
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