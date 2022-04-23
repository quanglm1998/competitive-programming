#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &u : a) cin >> u.first >> u.second;
    sort(a.begin(), a.end(), [&](pair<int, int> &u, pair<int, int> &v) {
        return u.second < v.second;
    }) ;     
    int res = 0;
    int cur = 0;
    for (auto &u : a) {
        if (u.first >= cur) {
            cur = u.second;
            res++;
        }
    }
    cout <<  res << endl;
    return 0;
}