#include <bits/stdc++.h>

using namespace std;

void solve(vector<pair<int, int>> &a) {
    if (a.size() <= 1) return;
    vector<pair<int, int>> b = a;
    sort(b.begin(), b.end());
    auto pivot = b[b.size() / 2];
    vector<pair<int, int>> bigger, smaller;
    for (auto u : a) {
        if (u >= pivot) {
            cout << 'H';
            bigger.push_back(u);
        } else {
            cout << "HC";
            smaller.push_back(u);
        }
    }
    for (auto &u : smaller) u.first = -u.first;
    solve(smaller);
    for (auto u : bigger) cout << 'C';
    for (auto u : smaller) cout << 'H';
    reverse(bigger.begin(), bigger.end());
    solve(bigger);
    for (auto u : smaller) cout << 'C';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int h;
        cin >> a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < n; i++) cout << 'C';
    solve(a);
    for (int i = 0; i < n; i++) cout << 'H';
    cout << '\n';
    return 0;
}