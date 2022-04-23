#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, k;
vector<pair<int, int>> neg, pos;

long long calc(const vector<pair<int, int>> &a) {
    sort(a.begin(), a.end());
    long long res = 0;
    while (!a.empty()) {
        int cnt = a.back().second / k;
        res += 2ll * cnt * a.back().first;
        cout << cnt << endl;

        a.back().second %= k;
        if (a.back().second == 0) {
            a.pop_back();
            continue;
        }
        res += 2ll * a.back().first;
        int now = k;
        while (!a.empty()) {
            int cur = min(now, a.back().second);
            a.back().second -= cur;
            now -= cur;
            if (a.back().second == 0) {
                a.pop_back();
            } else {
               break; 
            }
        }   
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x, m;
        cin >> x >> m;
        if (x > 0) pos.push_back({x, m});
        else neg.push_back({-x, m});
    }
    long long res = calc(pos) + calc(neg);
    cout << res << endl;
    return 0;
}